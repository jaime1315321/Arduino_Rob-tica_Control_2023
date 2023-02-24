volatile int contador=0; 
int sensor=3;
float rpm=0;
unsigned long time_start;
void setup (){
   pinMode(3,INPUT);
   Serial.begin(9600);
   attachInterrupt(digitalPinToInterrupt(sensor), interrupcion, CHANGE);
   attachInterrupt(100,interrupcion,RISING);
  }

void loop(){
  delay(1);
  rpm = contador*60/78.7;
  Serial.println(rpm);
  contador=0;
  if (millis() - time_start >= 5000) 
    {
        while(1) {};
    }
  }

void interrupcion(){
  
      contador++;
      //Serial.println(contador);
  }