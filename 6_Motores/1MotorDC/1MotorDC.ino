#define BUTTONCHANGE 6
#define BUTTONRIGHT 7
#define BUTTONLEFT 8
#define IN1 9
#define IN2 10
#define ENA 11

int speedMotor = 255;
bool statusLeft;
bool statusRight;
bool statusChange;
bool giro;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(BUTTONRIGHT, INPUT);
  pinMode(BUTTONLEFT, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  giro = true;
  //encender motor
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  statusRight = digitalRead(BUTTONRIGHT);//aumento de velocidad
  statusLeft = digitalRead(BUTTONLEFT);//disminucion de velocidad
  statusChange = digitalRead(BUTTONCHANGE);//cambio de giro
  
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
  
  if(statusChange == HIGH){//cambio de giro
    Serial.println("button giro presionado");
    giro = !giro;
    if(giro == true){
      Serial.println("giro true");
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }else{
      Serial.println("giro false");
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    }
  }
  
  analogWrite(ENA, speedMotor);
  delay(150);
}
