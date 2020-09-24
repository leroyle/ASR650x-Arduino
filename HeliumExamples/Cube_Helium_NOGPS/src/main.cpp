
#include "LoRaWan_APP.h"
#include "Arduino.h"
#include "cubecell_SSD1306Wire.h"

/*
 * set LoraWan_RGB to Active,the RGB active in loraWan
 * RGB red means sending;
 * RGB purple means joined done;
 * RGB blue means RxWindow1;
 * RGB yellow means RxWindow2;
 * RGB green means received done;
 */

uint32_t delayTime = 10000; //60000;
uint32_t lastTime = 0;
bool sendIt = false;

// Robs Keys


/* OTAA para*/
uint8_t devEui[] = { 0x2D, 0x0F, 0x60, 0x6B, 0x10, 0xB9, 0x3F, 0x6F };
uint8_t appEui[] = { 0x67, 0x84, 0x53, 0xFD, 0x56, 0x07, 0x9A, 0x3F };
uint8_t appKey[] = { 0xEE, 0x8C, 0xCF, 0xF0, 0x42, 0x67, 0x34, 0xE1, 0x31, 0x29, 0xD5, 0x01, 0x1D, 0xD9, 0x75, 0x58 };


/* ABP para*/
uint8_t nwkSKey[] = { 0x15, 0xb1, 0xd0, 0xef, 0xa4, 0x63, 0xdf, 0xbe, 0x3d, 0x11, 0x18, 0x1e, 0x1e, 0xc7, 0xda,0x85 };
uint8_t appSKey[] = { 0xd7, 0x2c, 0x78, 0x75, 0x8c, 0xdc, 0xca, 0xbf, 0x55, 0xee, 0x4a, 0x77, 0x8d, 0x16, 0xef,0x67 };
uint32_t devAddr =  ( uint32_t )0x007e6ae1;

/*LoraWan channelsmask, default channels 0-7*/ 
uint16_t userChannelsMask[6]={ 0xFF00,0x0000,0x0000,0x0000,0x0000,0x0000 };

/*LoraWan region, select in arduino IDE tools or platformio.ini*/
LoRaMacRegion_t loraWanRegion = ACTIVE_REGION;

/*LoraWan Class, Class A and Class C are supported*/
DeviceClass_t  loraWanClass = LORAWAN_CLASS;

/*the application data transmission duty cycle.  value in [ms].*/
uint32_t appTxDutyCycle = 20000;

/*OTAA or ABP*/
bool overTheAirActivation = LORAWAN_NETMODE;

/*ADR enable*/
bool loraWanAdr = LORAWAN_ADR;

/* set LORAWAN_Net_Reserve ON, the node could save the network info to flash, when node reset not need to join again */
bool keepNet = LORAWAN_NET_RESERVE;

/* Indicates if the node is sending confirmed or unconfirmed messages */
bool isTxConfirmed = LORAWAN_UPLINKMODE;

/* Application port */
uint8_t appPort = 2;
/*!
* Number of trials to transmit the frame, if the LoRaMAC layer did not
* receive an acknowledgment. The MAC performs a datarate adaptation,
* according to the LoRaWAN Specification V1.0.2, chapter 18.4, according
* to the following table:
*
* Transmission nb | Data Rate
* ----------------|-----------
* 1 (first)       | DR
* 2               | DR
* 3               | max(DR-1,0)
* 4               | max(DR-1,0)
* 5               | max(DR-2,0)
* 6               | max(DR-2,0)
* 7               | max(DR-3,0)
* 8               | max(DR-3,0)
*
* Note, that if NbTrials is set to 1 or 2, the MAC will not decrease
* the datarate, in case the LoRaMAC layer did not receive an acknowledgment
*/
uint8_t confirmedNbTrials = 4;

// access to the display as initialized by the LoRaWan object
extern SSD1306Wire  display;
void displayCustomString( char * custString);
uint16_t sendCount = 0;

/* Prepares the payload of the frame */
static void prepareTxFrame( uint8_t port )
{
  /*appData size is LORAWAN_APP_DATA_MAX_SIZE which is defined in "commissioning.h".
  *appDataSize max value is LORAWAN_APP_DATA_MAX_SIZE.
  *if enabled AT, don't modify LORAWAN_APP_DATA_MAX_SIZE, it may cause system hanging or failure.
  *if disabled AT, LORAWAN_APP_DATA_MAX_SIZE can be modified, the max value is reference to lorawan region and SF.
  *for example, if use REGION_CN470, 
  *the max value for different DR can be found in MaxPayloadOfDatarateCN470 refer to DataratesCN470 and BandwidthsCN470 in "RegionCN470.h".
  */
    appDataSize = 4;
    appData[0] = 0x00;
    appData[1] = 0x01;
    appData[2] = 0x02;
    appData[3] = 0x03;
}


void setup() {
  boardInitMcu();
  Serial.begin(115200);
  delay(3000);
  Serial.println("\n\n\tApp Name: Helium Example");

  display.init();
  display.clear();
  displayCustomString("This is my test");
  
#if(AT_SUPPORT)
  enableAt();
#endif
  deviceState = DEVICE_STATE_INIT;
  LoRaWAN.ifskipjoin();
  
}

void loop()
{
  uint32_t currTime = millis();

  if ( currTime > lastTime + delayTime)
  {
    sendIt = true;
    lastTime = currTime; 
  }
  
  switch( deviceState )
  {
    case DEVICE_STATE_INIT:
    {
#if(AT_SUPPORT)
      getDevParam();
#endif
  
      printDevParam();
     
      LoRaWAN.init(loraWanClass,loraWanRegion);

      // If you reset Data rate or transmit power, be sure
      // it is after the LoRaWAN.init().

      Serial.print("Main: Get default data rate: ");
      Serial.println(LoRaWAN.getDataRateForNoADR());

      // default DR
      LoRaWAN.setDataRateForNoADR(DR_2);

      Serial.print("Main: Get new data rate after change: ");
      Serial.println(LoRaWAN.getDataRateForNoADR());

      deviceState = DEVICE_STATE_JOIN;
      break;
    }
    case DEVICE_STATE_JOIN:
    {
      LoRaWAN.join();
      
      break;
    }
    case DEVICE_STATE_SEND:
    {
    
      if (sendIt == false)
      {
        break;
      } else {
        sendIt = false;
      }
      
      sendCount++;
      printf("\n\tMain: sending - Count: %d\r\n\n", sendCount);

      prepareTxFrame( appPort );
     
      // check state of the Adaptive Data Rate flag
      MibRequestConfirm_t mibReq;
      mibReq.Type = MIB_ADR;
  
      if( LoRaMacMibGetRequestConfirm( &mibReq ) == LORAMAC_STATUS_OK )
      {
        Serial.print("ADR Enabled Results from MibGet: ");
        Serial.println(mibReq.Param.AdrEnable);
      }
    
      // if you want to reset the transmit power level on
      // the third send
      // Be carefull, the network sends a LinkADRReq MAC command
      // sometime after the first data uplink. The processing of 
      // MAC command will set the date rate and transmit power. 
      // the data rate used on the uplink is reflected back, thus
      // if you change it prior to the first uplink it is essentially
      // preserved.
      // As the network has no knowlege of the transmit power used
      // it defaults to suggesting max power

      if (sendCount == 2)
      {
      // get the current power level
        MibRequestConfirm_t mibReq;
        eLoRaMacStatus status;

        mibReq.Type = MIB_CHANNELS_TX_POWER;
    
        status = LoRaMacMibGetRequestConfirm( &mibReq ); 
        if( status == LORAMAC_STATUS_OK )
        {
          Serial.print("Current txPower level from MibGet: ");
          Serial.println(mibReq.Param.ChannelsTxPower);
        } else {
          Serial.print("Fetch of current power level failed: ");
          Serial.println( status);
        }

        // reset the transmit power
        mibReq.Type = MIB_CHANNELS_TX_POWER;
        mibReq.Param.ChannelsTxPower = TX_POWER_6;

         status = LoRaMacMibSetRequestConfirm( &mibReq ); 
        if( status == LORAMAC_STATUS_OK )
        {
          Serial.print("Tx power updated to: ");
          Serial.println(TX_POWER_6);
        } else {
          Serial.print("Tx power update failed: ");
          Serial.println(status);
        }

        // verify the current power level
        mibReq.Type = MIB_CHANNELS_TX_POWER;
    
        status = LoRaMacMibGetRequestConfirm( &mibReq ); 
        if( status == LORAMAC_STATUS_OK )
        {
          Serial.print("Verified txPower level from MibGet: ");
          Serial.println(mibReq.Param.ChannelsTxPower);
        } else {
          Serial.println("Verify of current power level failed: ");
          Serial.print( status);
        }

      }

      // change data rate at 6th send
      if (sendCount == 6)
      {
        Serial.print("Data Rate before app change: ");
        Serial.println(LoRaWAN.getDataRateForNoADR());
        
        //change to DR_1
        LoRaWAN.setDataRateForNoADR(DR_1);

        Serial.print("Data Rate after app change: ");
        Serial.println(LoRaWAN.getDataRateForNoADR());
      }

      // dump the user packet
      printf("Main:  packet size: %d\r\n", appDataSize);
      printf("\tmain packet data\r\n\t");
      for (uint8_t i = 0; i < appDataSize; i++) {
        printf("0x%x ", appData[i]);
      }
      printf("\r\n");

      //you can check send result
      LoRaMacStatus_t sendStatus = LoRaWAN.send();
			if (sendStatus != LORAMAC_STATUS_OK) {
				printf("Main: ERROR - send failed: %d\r\n", sendStatus);
			} else {
					printf("Main: - send success: %d\r\n", sendStatus);
			}
			printf("\n\n");
      deviceState = DEVICE_STATE_CYCLE;
      break;
    }
    case DEVICE_STATE_CYCLE:
    {
      // Schedule next packet transmission
      txDutyCycleTime = appTxDutyCycle + randr( 0, APP_TX_DUTYCYCLE_RND );
      LoRaWAN.cycle(txDutyCycleTime);
      deviceState = DEVICE_STATE_SLEEP;
      break;
    }
    case DEVICE_STATE_SLEEP:
    {
      LoRaWAN.sleep();
      break;
    }
    default:
    {
      deviceState = DEVICE_STATE_INIT;
      break;
    }
  }
}

// Display a custom string, callable from the app level
void displayCustomString( char * custString)
{
        display.setFont(ArialMT_Plain_16);
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.clear();
        display.drawStringMaxWidth(0, 1, 128, custString);
        display.display();
}