float  pv; //Variable de proceso coentiene la salida de PWM
int pinA = 3;
volatile long contador = 0;
unsigned long previousMillis = 0;
long interval = 1000;
unsigned long time_start;

void setup() {
  pinMode(pinA, INPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(pinA), interrupcion,RISING);
  }

void loop() {
    unsigned long currentMillis = millis();
    if ((currentMillis - previousMillis >= interval)){
        previousMillis = currentMillis;
        pv = contador*(60.0/27000.0); //RPM en eje de salida
                
        contador = 0;
         if (millis() - time_start >= 2000) 
         {
           while(1) {};
         } 
      }
      
     Serial.println(pv);  
  }

void interrupcion(){
  contador++;
  }
