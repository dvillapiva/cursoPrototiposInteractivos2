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


//Declaración de variables para la melodía
int spk=2;                             // altavoz a GND y pin 2
int c[5]={131,262,523,1046,2093};       // frecuencias 4 octavas de Do
int cs[5]={139,277,554,1108,2217};      // Do#
int d[5]={147,294,587,1175,2349};       // Re
int ds[5]={156,311,622,1244,2489};    // Re#
int e[5]={165,330,659,1319,2637};      // Mi
int f[5]={175,349,698,1397,2794};       // Fa
int fs[5]={185,370,740,1480,2960};     // Fa#
int g[5]={196,392,784,1568,3136};     // Sol
int gs[5]={208,415,831,1661,3322};   // Sol#
int a[5]={220,440,880,1760,3520};      // La
int as[5]={233,466,932,1866,3729};    // La#
int b[5]={247,494,988,1976,3951};      // Si

void nota(int a, int b);            // declaración de la función auxiliar. Recibe dos números enteros.
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
  if(disCalculada < 30)
  {
    Melodia();
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

//Función con melodía "Entre dos aguas"
void Melodia()
{
  /*     entre dos aguas     */

nota(a[1],400);noTone(spk);delay(400);
nota(e[1],400);noTone(spk);delay(400);
nota(a[1],400);noTone(spk);delay(200);
nota(e[1],200);noTone(spk);delay(200);
nota(a[1],200);noTone(spk);delay(200);
nota(as[1],100);noTone(spk);delay(100);
nota(b[1],400);noTone(spk);delay(400);
nota(fs[1],400);noTone(spk);delay(400);
nota(b[1],400);noTone(spk);delay(200);
nota(fs[1],200);noTone(spk);delay(200);
nota(b[1],200);noTone(spk);delay(200);
nota(as[1],100);noTone(spk);delay(100);
nota(a[1],400);noTone(spk);delay(400);
nota(e[1],400);noTone(spk);delay(400);
nota(a[1],400);noTone(spk);delay(400);    
}

void nota(int frec, int t)
{
    tone(spk,frec);      // suena la nota frec recibida
    delay(t);                // para despues de un tiempo t
}
