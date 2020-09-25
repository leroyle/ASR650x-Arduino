# sept 24, 2020
## FAQ:

- With my CubeCell I see the "joining", "joined", and a single "unconfirmed uplink sent" and then nothing:
  - This message is actually dumped before final packet length validation is performed. So, if the packet is too large for the defined data rate it may not be sent. Check to make sure the default data rate is correct for your region and that the maximum packet size for that data rate is not being exceeded by any transmits from your application.

- I see "uplink sent" messages on the serial port output but nothing shows up within the Helium console.
  - There is some sort of failure being detected within the send logic. Unfortunatly the Cubecell runtime send() API does not return error status to the app layer and does not dump any error message to the serial output.  Use a version of the runtime that supports returning send result status back up to the app layer. Add error checking/handling to the appp layer.

- With the latest version of the runtime my device never "joins" the network.
  - Check the preamble size in the RegionUS915.c file. 
    - Look for Radio.SetTxConfig(). The 7th parameter should be 8, not 14 or 16.

- How do I set data rate or transmit power from within my device application
  - refer to the top level HeliumExamples directory within this repository where you will find a sample application that demonstrates both API's. 
  - Be sure these are set "after" the call to LoRaWAN.init(). 
  - Pay attention to the note about setting transmit power level.
      
- I set my custom data rate and transmit power after the LoRaWAN.init() call but my transmit power is getting reset back to TX_POWER_0 (0).
  - Sometime after the first uplink is received by the network the network returns a LinkADRReq MAC command to the device. The purpose is to suggest to the app the proper channel selection mask, the data rate, and transmission power level for optimal netowork connection.
    - The channel selection mask is defined by the network operator and should be used.
    - The data rate is a mirrored back value from what was detected by the network from the inital uplink message. So it should be equal to what was set for the uplink message.
    - For transmission power the network has no knowlege of what the device used for uplink so it default to max power, TX_POWER_0 which is a value of 0.
  Thus if you override the transmit power it must be after the LinkADRReq MAC command is processed which may be after one or two uplink messages. 
  - The network will continue to send the LinkADRReq command until it receives a response from the device application, thus there is not a hard fast rule as to when the runtime processes the message.

- Why do I see my device transmitting empty packets.
    - The default runtime has a bug which allows zero byte packets to be sent if your packet size is larger than allowed for the current data rate setting. Trying increasing your data rate.

- Why do I see occasional payloads being sent to the network that are larger than my user packet data. Sometimes the payload size appears to exceed the maximum for the defined data rate. I thought the runtime would refuse to send packets that exceed the data rate maximum>
  - the oversize check is temporarily suspended if a MAC response is being returned to the network.
    - The network communicates house keeping messages with the end node device using MAC commands. Generally these are not exposed to the application API, rather are stripped out/added by the lower level runtimes. These are generally very infrequent and small in size. These downlink commands/requests are sent to the device during one of the normal device receive windows. The responses are packaged back up into the return payload. If your data rate setting maximum payload size limit and payload  actual length are very close adding the MAC responses may cause the overall length to exceed the data rate maximum specification. In this case a design decision was made to ignore the oversize length and send the packet anyway. The assumption here is that this occurance is very limited and the oversize difference is a byte or two. 




# This Repository Changes 
# sept 24, 2020

### Problem:

Added a platformio sample that uses the set/get API for data rate and transmit power and  send result status
### Problem:
Network specified Adaptive Data Rate changes were not being applied as expected
#### reworked a bit of the ADR handling 
# Sept 19, 2020
### Problem:
Last changes broke ADR data rate change as suggested by the network router
#### fix:
restore ability of network to influence data rate when ADR is enabled.

# Sept 18, 2020

### Problem:
Default data rate is fixed by a #define in the runtime
#### fix:
Along with Heltec support updated default data rate
- it is still set by a #define in the runtime,
- we now have API control to allow setting from the application

 ```
 void setDataRateForNoADR(int8_t dataRate);
 int8_t getDataRateForNoADR();
```
##### NOTE:
It looks like runtime support of Data Rate ADR is not there, so
   once Helium has this, the runtime will need to be checked/enhanced

### Problem:
The runtime did not return a "send" status to the app layer. It would
    succeed or fail silently,
#### fix:
we now return a code back up to the app layer

### Problem:
We need more exposure to what is happening
#### fix:
added more and indented debug messages

### Problem:
Several errors related to attempting to send too large of packet for the configured
data rate.
#### Problem:
The runtime would actually "send" the oversize packet if there was a pending MAC response. In this case we were responding to the Helium
     router LinkADRReq MAC command.
#### fix:
If there is an oversize packet and a pending MAC response, the runtime will only send the MAC response and will return an error status to the app layer.

If the DR_ length allows both the user data and the MAC response will be sent to the network.
#### Problem:
The runtime would send a zero length packet each time the user attempted to send the oversize packet even if there was not a pending MAC response
 #### fix:
 We now error out, do not send to the network and return fail status to the app layer
### Problem:
Heltec for some reason set the LoRaWan packet preamble to 14, I flagged it but they do not seen concerned
 #### fix:
 Changed packet preamble length back to 8
 
