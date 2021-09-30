#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
SoftwareSerial BT(10,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth
#include <ArduinoJson.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(6, 9); // RX, TX del MP3
DFRobotDFPlayerMini myDFPlayer;

void printDetail(uint8_t type, int value);


String readString;

int id = 0;
int act = 0;
int value = 0;

void setup() {

  Serial.begin(9600); //Inicializa serial
  BT.begin(9600);  // Inicializa Bluetooth 

  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  
//  myDFPlayer.setTimeOut(500); 
//  myDFPlayer.volume(20);  //Set volume value. From 0 to 30

  //myDFPlayer.play(2);
}

void loop() {

  while (BT.available()) {
    delay(10);  //small delay to allow input buffer to fill

   String c =  BT.readString();

  
    if (c == ',') {
      break;
    }  //breaks out of capture loop to print readstring
    readString += c;
    
  } 



  //makes the string readString 
int str_len = readString.length() + 1; 
      char json[str_len];
      readString.toCharArray(json, str_len);
      
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, json);
        
         id =(int) doc["I"];
    value =(int) doc["V"];
    act =(int) doc["A"];
      
    if (readString.length() >0) {
      Serial.println(readString); //prints string to serial port out



    
  if (id==2){

    Serial.println("Entramos a id");
  actionMP3( act,  value);
  }
    
    readString=""; //clears variable for new input
  }

}


void actionMP3(int act, int value){
    Serial.println("Entramos a mp3");

  if (act == 0){
    Serial.println("Entramos a P");

    
    if (value == 0){
        Serial.println("Entramos a 0");
        myDFPlayer.play(2);
        delay(1000);
    }
//    else if (value ==1){
//          Serial.println("Entramos a 1");
//
//       myDFPlayer.start();  //start the mp3 from the pause
//       delay(1000);
//    }
  }
//  else if (act == 1){
//    
//  }
//  else if (act == 2){
//    
//  }
//  else{
//    Serial.println("No hay acción detectada");
//    }  
  
  }
