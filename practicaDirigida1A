
#include <LiquidCrystal.h>//Librería para LCD
#include <Servo.h>//Librería para el servo

Servo servo1; //Constructor de la sentencia servo
LiquidCrystal lcd(8,9,4,5,6,7); //Se definen los pines que controlan la LCD en la tarjeta de Arduino.

//Creación de variables
int trig = 13; //Envía una onda ultrasónica a través del disparador
int echo = 12; // Recibe las ondas que rebotan en el objeto
float disCalculada; //Variable que guarda el valor de la distancia
int piezo=2; //variable del pin del piezo

//Estos datos son para el servo
int puertoservo=3; //variable que envía datos al servo
int grados; //Variable que guarda los grados del ángulo del servo
int tmp=0; //variable temporal
int pulsominimo=650; //variable que define el ángulo menor del servo
int pulsomaximo=2550; //variable que define el ángulo mayor del servo

//Datos para la LCD
int v=-1; 
//------------------------------------------------------------------------

void setup() {
  // Se activan los eventos que requerimos para el sensor
  pinMode (trig, OUTPUT);
  pinMode (echo, INPUT);
  pinMode(piezo, OUTPUT); 
  Serial.begin (9600);//activa el monitor serial a una frecuencia de 9600 para ir viendo sus valores

//Se indica al servo por cuál pin nos vamos a comunicar y cuál es su ángulo máximo y mínimo
  servo1.attach(puertoservo,pulsominimo,pulsomaximo);

//Instrucciones para la LCD
lcd.setCursor(4,1); //Posición 4 de la fila 1.
lcd.print("PRONIE"); //muestra en pantalla el texto
lcd.noBlink(); //para que la pantalla no parpadee.
delay(200);
}

//---------------------------------------------------------------------------

void loop() {
  // Todo esto es para programar el sensor ultrasónico
  disCalculada = calcularDistancia(); //A la variable disCalculada le devolvemos el valor del procedimiento
  Serial.println("-------"); //println() da un enter para ver la información en otro renglón. Esto crea una línea que divide la lectura en información
  Serial.print("cm :"); //print() imprime en el mismo renglón
  Serial.println(disCalculada); //se muestra el valor de la variable
  delay(200);

  //Código para el servo
  grados=servo1.read(); //Esta variable guarda los grados del ángulo que giró el servo.
  Serial.print("Grados :");
  Serial.println(grados);
  delay(200);
  
// Esta condicional es para el piezo, si está a una distancia menor a 100 suena el piezo, sino no haga nada. En el caso del servo se utiliza la variable temporal.
  if(disCalculada < 100)
  {
    tone(piezo,600,100);
    tmp=100; //Para que tmp tenga 100grados y abra la puerta
  }
  else
  {
  tmp=0; //Pone la variable en 0 para que se cierre la puerta.
  }
  delay(10);
  servo1.write(tmp);


//Programación para la pantalla LCD
lcd.setCursor(1,1); //Texto aparece en Fila 1, posición 1
lcd.print("Distancia "); 
lcd.println(disCalculada);
}
//------------------------------------------------------------------------

//Esto es para la programación del sensor ultrasónico
int calcularDistancia(){
    long distancia;
    long duracion;
    
    digitalWrite(trig, LOW);
    delayMicroseconds(4);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duracion=pulseIn (echo, HIGH);
    duracion=duracion/2;
    distancia=duracion/29;
    return distancia;
}
