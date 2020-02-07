//Pines para el motor
const int enableA = 10;
const int pinA1 = 9;
const int pinA2 = 8;
//pines para pushButton
const int pushButtonD=4;
const int pushButtonI=5;
const int LED = 7;
int valueD=0;
int valueI=0;
//Pines para el encoder LPD3806
int temp, counter = 0; 
//Pines para el encoder 2342L012 CR
const int canalA=20;
const int canalB=21;

int valor1;
int valor2;
int counterRayos = 0;
int milisInicial;
int milisFinal;
//Potenciometro-Amplificador
int PoAm = 11;

bool Dderecho = true;
void setup() {
  Serial.begin(9600);
 //Motor 
 pinMode(enableA, OUTPUT);
 pinMode(pinA1, OUTPUT);
 pinMode(pinA2, OUTPUT);
 pinMode(LED,OUTPUT);
 pinMode(pushButtonD,INPUT_PULLUP);
 pinMode(pushButtonI,INPUT_PULLUP);
 
 //Encoder LPD3806
 pinMode(2, INPUT_PULLUP); // Hilo verde
 pinMode(3, INPUT_PULLUP); // Hilo blanco 
 attachInterrupt(0, ai0, RISING); 
 attachInterrupt(1, ai1, RISING);
//Encoder velocidad
pinMode(canalA,INPUT_PULLUP);
pinMode(canalB,INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(canalA), cambio, CHANGE);
attachInterrupt(digitalPinToInterrupt(canalB), cambio, CHANGE);
milisInicial=millis();
//Amplificador
pinMode(PoAm,INPUT_PULLUP);
motorAForward();
}
void loop() {
  if(digitalRead(11)==HIGH){
    motorAOn();
    
  }else{
    motorAOff();
  }
  
  valueD = digitalRead(pushButtonD);
  valueI = digitalRead(pushButtonI);
  
  if(valueD==LOW){//si el boton esta presionado
      //motorABackward();
      Dderecho = false;
  }
  if(valueI==LOW){
      //motorAForward();
      Dderecho = true;
  }
  if(Dderecho){
    digitalWrite(pinA1, HIGH);
    digitalWrite(pinA2, LOW);
    delay(3);
    digitalWrite(pinA1, LOW);
    digitalWrite(pinA2, LOW);
    delay(50);
  }else{
    digitalWrite(pinA1, LOW);
    digitalWrite(pinA2, HIGH);
    delay(3);
    digitalWrite(pinA1, LOW);
    digitalWrite(pinA2, LOW);
    delay(50);
  }
  
  //Loop para encoder
  if( counter != temp ){
    Serial.print("Posicion: ");
    Serial.print(counter*0.45);
    Serial.println(" grados");
    temp = counter;
  }
  
 //delay(150);
}

//enable motor
void motorAOn(){
 digitalWrite(enableA, HIGH);
}
//disable motor
void motorAOff(){
 digitalWrite(enableA, LOW);
}

//motor A controls
void motorAForward()
{
 digitalWrite(pinA1, HIGH);
 digitalWrite(pinA2, LOW);
}
void motorABackward()
{
 digitalWrite(pinA1, LOW);
 digitalWrite(pinA2, HIGH);
}


//Encoder 
void ai0() {
  if(digitalRead(3)==LOW) {
    counter++;
  }else{
    counter--;
  }
}
   
void ai1() {
  if(digitalRead(2)==LOW) {
    counter--;
  }else{
    counter++;
  }
}
//Encoder 2342L012CR
void cambio(){//Cada vuelta de engrane mayor son 1800 pasadas de rayo 1800/24 = 75 la relacion es 75:1
  counterRayos++;
  if(counterRayos==48){
    milisFinal=millis();
    float milisV =milisFinal-milisInicial;
    float segundos = milisV/1000;
    float velocidadMenor = pow(segundos,-1);
    //Serial.print("velocidadMenor: ");
    //Serial.print(velocidadMenor);
    //Serial.println("rad/s");
    float velocidadMayor = velocidadMenor/75;
    Serial.print("velocidadMayor: ");
    Serial.print(velocidadMayor);
    Serial.println(" rad/s");
    milisInicial=millis();
    counterRayos=0;
  }
}
