
# Sept 19, 2020

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
 
