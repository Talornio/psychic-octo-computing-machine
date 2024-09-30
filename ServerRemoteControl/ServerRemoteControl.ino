/*
   -- ServerRemoteControlXY --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.10 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.13.11 or later version;
     - for iOS 1.10.3 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// you can enable debug logging to Serial at 115200
//#define REMOTEXY__DEBUGLOG    

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP32CORE_WIFI_CLOUD

#include <WiFi.h>

// RemoteXY connection settings 

//#define REMOTEXY_WIFI_SSID "TIM-18417049"
//#define REMOTEXY_WIFI_PASSWORD "aN5GXwlef2uCEG6s0VO2Kk9t"

//#define REMOTEXY_WIFI_SSID "WiFi Nonna"
//#define REMOTEXY_WIFI_PASSWORD "lenticchiaefagiolo21$"

#define REMOTEXY_WIFI_SSID "Vodafone-SMMF"
#define REMOTEXY_WIFI_PASSWORD "Malloppo1980$"

#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "29b624159302a1cf6525d897b5706bfa"


#include <RemoteXY.h>

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 69 bytes
  { 255,1,0,0,0,62,0,17,0,0,0,31,1,106,200,1,1,2,0,129,
  8,6,91,9,32,83,101,114,118,101,114,32,82,101,109,111,116,101,32,67,
  111,110,116,114,111,108,0,1,22,74,64,64,0,2,31,79,78,47,79,70,
  70,32,84,79,71,71,76,69,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t button; // =1 if button pressed, else =0

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_BUTTON 27


void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_BUTTON, OUTPUT);
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  digitalWrite(PIN_BUTTON, (RemoteXY.button==0)?LOW:HIGH);
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay(), use instead RemoteXY_delay() 


}
