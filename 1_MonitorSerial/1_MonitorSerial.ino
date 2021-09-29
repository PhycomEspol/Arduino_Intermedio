//#include <time.h>

int button = 8;
int led = 13;
bool bandera = false;
unsigned long t_before = 0;
unsigned long t_now;
int t_espera = 5000;

void setup() {
  // put your setup code here, to run once:
pinMode(button, INPUT);
pinMode(led, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {
    char ledState = Serial.read();
    if(ledState == '1'){
      digitalWrite(led, HIGH);
    }
    if(ledState == '0'){
      digitalWrite(led, LOW);
    }
  }
 
  int buttonState = digitalRead(button);
  if ( buttonState == HIGH){
    delay(100);
  if ( buttonState == HIGH){
    Serial.println("Button is pressed");
    delay(500);
    if (bandera == true){
      t_now = millis();
      if (t_now - t_before < t_espera){
        bandera = false;
        digitalWrite(led, LOW);
        Serial.println("LED is OFF");

        t_before = 0;
      }else{
        bandera = true;
        digitalWrite(led, HIGH);
        t_before = millis();
      }
    }else{
      bandera = true;
      digitalWrite(led, HIGH);
      Serial.println("LED is ON");

    }
    }
   }
  
 }
