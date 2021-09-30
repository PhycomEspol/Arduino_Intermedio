#include <SPI.h>      // incluye libreria bus SPI
#include <MFRC522.h>      // incluye libreria especifica para MFRC522

#define RST_PIN  9      // constante para referenciar pin de reset
#define SS_PIN  53      // constante para referenciar pin de slave select

MFRC522 mfrc522(SS_PIN, RST_PIN); // crea objeto mfrc522 enviando pines de slave select y reset

byte ActualUID[4]; //almacenará el código del Tag leído
byte Usuario1[4]= {0x4B, 0x8C, 0x2D, 0x3B} ; //código del usuario 1
byte Usuario2[4]= {0xFC, 0xE5, 0x56, 0x4B} ; //código del usuario 2

void setup() {
  Serial.begin(9600);     // inicializa comunicacion por monitor serie a 9600 bps
  SPI.begin();        // inicializa bus SPI
  mfrc522.PCD_Init();     // inicializa modulo lector
  Serial.println("Control de acceso:");
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) // si no hay una tarjeta presente
    return;         // retorna al loop esperando por una tarjeta
  
  if ( ! mfrc522.PICC_ReadCardSerial())   // si no puede obtener datos de la tarjeta
    return;         // retorna al loop esperando por otra tarjeta
    
  Serial.print("UID:");       // muestra texto UID:
  for (byte i = 0; i < mfrc522.uid.size; i++) { // bucle recorre de a un byte por vez el UID

    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);   
    ActualUID[i]=mfrc522.uid.uidByte[i];   
 
  } 

  Serial.print("     ");                 
  //comparamos los UID para determinar si es uno de nuestros usuarios  
  if(compareArray(ActualUID,Usuario1))
  Serial.println("Acceso concedido...");
  else if(compareArray(ActualUID,Usuario2))
  Serial.println("Acceso concedido...");
  else
  Serial.println("Acceso denegado...");
                  
  // Terminamos la lectura de la tarjeta tarjeta  actual
  mfrc522.PICC_HaltA();

}

//Función para comparar dos vectores
 boolean compareArray(byte array1[],byte array2[])
{
  if(array1[0] != array2[0])return(false);
  if(array1[1] != array2[1])return(false);
  if(array1[2] != array2[2])return(false);
  if(array1[3] != array2[3])return(false);
  return(true);
}
