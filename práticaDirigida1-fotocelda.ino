//*****************************************************************
//********Práctica dirigida.Sistema de alarma con fotocelda********
//*****************************************************************



//Variables que asocian los puertos del arduino.
int pinRojo=3;
int pinAzul =5;
int piezo =6;
int fotocelda = 0; //Está en el pin A0


void setup() {
  // Se le indica a los puertos anteriores el trabajo que harán.

    pinMode(pinRojo, OUTPUT);
    pinMode(pinAzul, OUTPUT);
    pinMode(piezo, OUTPUT);
    pinMode (fotocelda, INPUT);
    Serial.begin(9600);
}

void loop() {
    while (analogRead(fotocelda)<50) //Chequea el estatus de la fotocelda. Se activan los led y audio si detecta movimiento (al ponerse oscuro).
  {
    //El led Rojo está encendido y el azul apagado en el tiempo determinado por el espera.
    Serial.println(analogRead(fotocelda)); //Envía información al monitor
    digitalWrite(pinRojo, HIGH);
    digitalWrite(pinAzul, LOW);
    delay(500);
    
    //El led Rojo está apagado y el azul encendido en el tiempo determinado por el espera..
    digitalWrite(pinRojo, LOW);
    digitalWrite(pinAzul, HIGH);
    delay(500);

    //Suena el piezo o parlante en dos notas diferentes.
    tone(piezo, 300,100);
    delay(100);
    tone(piezo, 450,50);
 
    delay(100);
  }


      while (analogRead(fotocelda)>50)//Chequea el estatus de la fotocelda. Se mantienen los led apagados si no detecta movimiento.
  {
    digitalWrite(pinRojo, LOW);
    digitalWrite(pinAzul, LOW);
    Serial.println(analogRead(fotocelda));
  }
}
