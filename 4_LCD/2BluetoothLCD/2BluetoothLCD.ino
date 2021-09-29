#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
SoftwareSerial BT(10,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth
#include <ArduinoJson.h>

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);


#define pinR 5 //Rojo
#define pinG 6 //Verde
#define pinB 7 //Azul 


#define pinStateBT 28//Estado del Bluetooth 
String readString;


int red=0;
int green=0;
int blue=0;

String frase1="";
String frase2="";
int isResult=0;

int stateBT=0;

void setup() {

  Serial.begin(9600); //Inicializa serial
  BT.begin(9600);  // Inicializa Bluetooth 


  pinMode(pinR,OUTPUT);
  pinMode(pinG,OUTPUT);
  pinMode(pinB,OUTPUT);
  
  pinMode(pinStateBT,INPUT);
  
  Wire.begin();
  // Inicializar el LCD
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();
  

  
  lcd.clear();
}

void loop() {


  /***LCD***/
  stateBT = digitalRead(pinStateBT); //Estado de conección del bluetooth

  if(stateBT==LOW){
    frase1="Conectando";
    frase2="Bluetooth...";
    
    lcd.clear();
    lcd.print(frase1);
    lcd.setCursor(0, 1);
    lcd.print(frase2);
    delay(100);

    isResult=0;
  }
  else{
    /***Bluetooth***/
  
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


        frase1 = "LUCES R: "+ (String)red;
        frase2 ="G: "+ (String)green +" B: "+ (String)blue;

        
        isResult=1;



        
        digitalWrite(pinR,red);
        digitalWrite(pinG,green);
        digitalWrite(pinB,blue);
    
        readString=""; //clears variable for new input




    }

    if(!isResult){
      
    frase1="Bluetooth";
    frase2="Conectado";
    }


    lcd.clear();
    lcd.print(frase1);
    lcd.setCursor(0, 1);
    lcd.print(frase2);
    delay(100);





    
  }
  

}
