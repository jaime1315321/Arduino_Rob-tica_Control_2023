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
  cli();                   //Desabilito las interrupciones
  TCCR1A = 0;              //El registro de control A queda todo en 0
  TCCR1B = 0;              //Limpia registrador
  TCCR1B |= B00000101;   //MODO CTC, prescaler //TCCR1B |= B00000100; //TCCR1B |= ( 1 << cs10 ) | ( 1 << cs12 ); 
  
  TCNT1   = 0;              //Inicializa el temporizador

  OCR1A  =  156.25;        //Carga el registrador de comparación: [ 16MHz / (Pre-escalador * FrecuenciaInterrupcionDeseada)] - 1   o dividir los pulsos del cristal entre la frecuencia deseada
  
  TIMSK1 |= ( 1 << OCIE1A); //Habilita interrupción por igualdad de comparacion // TIMSK1 |= B00000010;
  sei(); //Habilito las interrupciones
}

void loop() {

  //Serial.println("------------------Que esta pasando? ---------------------------");
  Serial.println(pv); 
}

ISR(TIMER1_COMPA_vect){    //Interrupción por igualdad de compación
  interrupcion();
  pv = contador*100*(60.0/27000.0); //RPM en eje de salida  
  //Serial.println(pv);  
  //Serial.println(contador);
  contador = 0;  
  TCNT1 = 0;      //Reestablecer el valor del temporizador porque si no contará hasta su valor máximo

  if (millis() - time_start >= 3000) 
   {
     while(1) {};
   } 
  
}

void interrupcion(){
  contador++;
  }
