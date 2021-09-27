#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
SoftwareSerial BT(10,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth

//HC-06 ES SÓLO ESCLAVO
//HC-05 ES ESCLAVO Y MAESTRO
//USAREMOS UN HC-05
//ENTRAMOS CON LA CONFIGURACIÓN AT1
//ESCRIBIMOS AT PARA RECIBIR OK
//CAMBIAMOS NOMBRE CON AT+NAME=<NOMBRE>
//CAMBIAMOS CÓDIGO CON AT+PSWD=<PIN>


 
void setup()
{
  BT.begin(9600);       // Inicializamos el puerto serie BT (Para Modo AT 2)
  Serial.begin(9600);   // Inicializamos  el puerto serie  
}
 
void loop()
{
  if(BT.available())    // Si llega un dato por el puerto BT se envía al monitor serial
  {
    Serial.write(BT.read());
  }
 
  if(Serial.available())  // Si llega un dato por el monitor serial se envía al puerto BT
  {
     BT.write(Serial.read());
  }
}
