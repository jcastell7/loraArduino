void setup() { 
//configure Serial1, this could also be a  
//software serial.  
//Serial1.begin(115200); 
//configure the mail RX0 and TX0 port on arduino 
Serial.begin(115200); 
} 

//string to hold the response of a command in rak811 
String response = ""; 

//the famous arduino loop function. runs continuosly 
void loop() { 
//try getting the version of the board firmware 
 sendCommand("at+version\r\n");
 sendCommand("at+at+get_config=dev_eui");
 //setConnConfigApp("70B3D57ED00103EE","ttn-account-v2.5aeTBSf-cnQuU8R2I5FEz4QQ8IM1r_hQtWKOgdIl0xw");
 //sendJoinReq(); 
 //send data too gateway 
 //sendData(1,2,"000000000000007F0000000000000000"); 
 delay(3000);  
} 

/** 
* Function to send a command to the  
* lora node and wait for a response 
*/ 

void sendCommand(String atComm){ 
response = ""; 
Serial.print(atComm); 
 while(Serial.available()){ 
   char ch = Serial.read(); 
   response += ch; 
 } 
 Serial.println(response); 
} 




/** 
* send the rak811 to sleep for time  
* specified in millis paramteer 
*/ 

void sleep(unsigned long milliseconds){ 
 sendCommand("at+sleep\r\n"); 
 delay(milliseconds); 
 //send any charcater to wakeup; 
 sendCommand("***\r\n"); 
} 



/** 
* reset board after the specified time delay millisenconds 
* <mode> = 0 Reset and restart module 
= 1 Reset LoRaWAN or LoraP2P stack and Module will reload LoRa 
configuration from EEPROM 
*/ 

void resetChip(int mode, unsigned long delaySec=0){ 
 delay(delaySec); 
 String command = (String)"at+reset=" + mode + (String)"\r\n"; 
 sendCommand(command); 
} 


/** 
* Reload the default parameters of LoraWAN or LoraP2P setting 
*/ 

void reload(unsigned long delaySec){ 
 delay(delaySec); 
 sendCommand("at+reload\r\n"); 
} 


/** 
* Function to set module mode 
* <mode> = 0 LoraWAN Mode (default mode) 
= 1 LoraP2P Mode 
*/ 
void setMode(int mode){ 
 String command = (String)"at+mode=" + mode + (String)"\r\n"; 
 sendCommand(command);   
} 



/** 
* Function to send data to a lora gateway; 
* <type> = 0 send unconfirmed packets 
= 1 send confirmed packets 
<port> = 1-223 port number from 1 to 223 
<data>= <hex value> hex value(no space). The Maximum length of <data> 64 bytes 
*/ 

void sendData(int type, int port, String data){ 
 String command = (String)"at+send=" + type + "," + port + "," + data + (String)"\r\n"; 
 sendCommand(command); 
} 


/** 
* Function to send a join request 
* allowed methods "otaa" and "abp" 
*/ 

void sendJoinReq(String method){ 
 String command = (String)"at+join=" + method + "\r\n"; 
 sendCommand(command); 
} 
void setConnConfigrx2(){ 
 sendCommand("at+set_config=rx2:3,868500000"); 
} 
void setConnConfigApp(String appEUI, String appKey){ 
 ("at+set_config=app_eui:" + appEUI + "&app_key:" + appKey + "\r\n"); 
}
