int button = 8;
int led = 13;

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
  Serial.println(buttonState);
  if ( buttonState == LOW){

    delay(100);
    
  if ( buttonState == LOW){
    
    Serial.println("Button is pressed");
    delay(500);
  }
  }
 }
