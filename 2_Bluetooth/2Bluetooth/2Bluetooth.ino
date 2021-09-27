#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
SoftwareSerial BT(10,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth

String readString;

void setup() {

  Serial.begin(9600); //Inicializa serial
  BT.begin(9600);  // Inicializa Bluetooth 

}

void loop() {

  while (BT.available()) {
    delay(10);  //small delay to allow input buffer to fill
    
   String c =  BT.readString();
    Serial.println(c);
  
    readString += c;
    
  } 

}
