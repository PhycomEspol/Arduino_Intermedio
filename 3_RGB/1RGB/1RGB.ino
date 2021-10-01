
#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
SoftwareSerial BT(10,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth
#include <ArduinoJson.h>


#define pinR 5 //Rojo
#define pinG 6 //Verde
#define pinB 7 //Azul 

String readString;


int red=0;
int green=0;
int blue=0;



void setup() {

  Serial.begin(9600); //Inicializa serial
  BT.begin(9600);  // Inicializa Bluetooth 

  pinMode(pinR,OUTPUT);
  pinMode(pinG,OUTPUT);
  pinMode(pinB,OUTPUT);
}

void loop() {

  while (BT.available()) {
    delay(10);  //small delay to allow input buffer to fill

   String c =  BT.readString();
    Serial.println(c);
  
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
      
    red =(int) doc["R"];
    green =(int) doc["G"];
    blue =(int) doc["B"];
    
  if (readString.length() >0) {
    Serial.println(readString); //prints string to serial port out

    Serial.println("RED"); //prints string to serial port out
    Serial.println(red);
    Serial.println("Green"); //prints string to serial port out
    Serial.println(green);
    Serial.println("Blue"); //prints string to serial port out
    Serial.println(blue);
    
    digitalWrite(pinR,red);
    digitalWrite(pinG,green);
    digitalWrite(pinB,blue);

    readString=""; //clears variable for new input
  }


}
