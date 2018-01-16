//***************************************************
//********Práctica dirigida.Sistema de alarma********
//***************************************************



//Variables que asocian los puertos del arduino.
int pinRojo=3;
int pinAzul =5;
int piezo =6;
int boton = 2;
int estado =0;

void setup() {
  // Se le indica a los puertos anteriores el trabajo que harán.

    pinMode(pinRojo, OUTPUT);
    pinMode(pinAzul, OUTPUT);
    pinMode(piezo, OUTPUT);
    pinMode (boton, INPUT);
    Serial.begin(9600);
}

void loop() {
    while (digitalRead(boton)==0) // El botón está sin presionar
  {
    //El led Rojo está encendido y el azul apagado en el tiempo determinado por el espera.
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
    Serial.println(digitalRead(boton)); //Envía información al monitor
    delay(100);
  }


      while (digitalRead(boton)==1) //El botón está presionado.
  {
    digitalWrite(pinRojo, LOW);
    digitalWrite(pinAzul, LOW);
    Serial.println(digitalRead(boton));
  }
}
