#include <Servo.h>
#include <SPI.h>     // incluye libreria bus SPI
#include <MFRC522.h> // incluye libreria especifica para MFRC522
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
#include <ArduinoJson.h>


SoftwareSerial BT(10,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth

#define RST_PIN 9 // constante para referenciar pin de reset
#define SS_PIN 53 // constante para referenciar pin de slave select


#define pinR 5 //Rojo
#define pinG 6 //Verde
#define pinB 7 //Azul 

int red=0;
int green=0;
int blue=0;



MFRC522 mfrc522(SS_PIN, RST_PIN); // crea objeto mfrc522 enviando pines de slave select y reset

byte ActualUID[4];                           //almacenará el código del Tag leído
byte Usuario1[4] = {0x4B, 0x8C, 0x2D, 0x3B}; //código del usuario 1
byte Usuario2[4] = {0xFC, 0xE5, 0x56, 0x4B}; //código del usuario 2

Servo myservo; // create servo object to control a servo

int pos = 0; // variable to store the servo position

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{

  Serial.begin(9600); // inicializa comunicacion por monitor serie a 9600 bps
  SPI.begin();        // inicializa bus SPI
  mfrc522.PCD_Init(); // inicializa modulo lector
  Serial.println("Control de acceso:");

  BT.begin(9600);  // Inicializa Bluetooth 
  
  myservo.attach(4); // attaches the servo on pin 9 to the servo object
  myservo.write(0);

  Wire.begin();
  
  lcd.init();// Inicializar el LCD

  
  lcd.backlight();//Encender la luz de fondo.


  pinMode(pinR,OUTPUT);
  pinMode(pinG,OUTPUT);
  pinMode(pinB,OUTPUT);

  
  escribirLCD("Inserte","Tarjeta");
        colorRGB(0, 0, 255);
}

void loop()
{



  if (mfrc522.PICC_IsNewCardPresent())
  {

    if (mfrc522.PICC_ReadCardSerial())
    {

        escribirLCD("Leyendo","Tarjeta");
      Serial.print("UID:"); // muestra texto UID:
      for (byte i = 0; i < mfrc522.uid.size; i++)
      { // bucle recorre de a un byte por vez el UID

        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        ActualUID[i] = mfrc522.uid.uidByte[i];
      }

      Serial.print("     ");
      //comparamos los UID para determinar si es uno de nuestros usuarios
      if (compareArray(ActualUID, Usuario1) || compareArray(ActualUID, Usuario2))
      {


        escribirLCD("Acceso","Concedido");
        
        colorRGB(0, 255, 0);
        myservo.write(90);
        delay(1000);

        myservo.write(0);
        delay(1000);
      }

      else
      {

        escribirLCD("Acceso","Denegado");

        colorRGB(255, 0, 0);
        myservo.write(0);
        delay(1000);
      }

      // Terminamos la lectura de la tarjeta tarjeta  actual
      mfrc522.PICC_HaltA();

        escribirLCD("Inserte","Tarjeta");
        colorRGB(0, 0, 255);
    }
  }
}

//Función para comparar dos vectores
boolean compareArray(byte array1[], byte array2[])
{
  if (array1[0] != array2[0])
    return (false);
  if (array1[1] != array2[1])
    return (false);
  if (array1[2] != array2[2])
    return (false);
  if (array1[3] != array2[3])
    return (false);
  return (true);
}

void escribirLCD(String texto1,String texto2){
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(texto1);
  lcd.setCursor(0, 1);
  lcd.print(texto2);
  
}

void colorRGB(int R, int G, int B){
  
    digitalWrite(pinR,R);
    digitalWrite(pinG,G);
    digitalWrite(pinB,B);
  
}
