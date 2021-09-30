#define BUTTONRIGHT 7
#define BUTTONLEFT 8
#define IN1 9
#define IN2 10
#define ENA 11

int speedMotor = 255;
bool statusLeft;
bool statusRight;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTONRIGHT, INPUT);
  pinMode(BUTTONLEFT, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
 
  //encender motor
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  statusRight = digitalRead(BUTTONRIGHT);
  statusLeft = digitalRead(BUTTONLEFT);
  if(statusLeft == HIGH){
    if(speedMotor <= 0){
      speedMotor = 0;
    }else{
      speedMotor = speedMotor - 5; 
    }
  }
  
  if(statusRight == HIGH){
    if(speedMotor >= 255){
      speedMotor = 255;
    }else{
      speedMotor = speedMotor + 5; 
    }
  }

  analogWrite(ENA, speedMotor);
  delay(150);
}
