int pinRojo=3;
int pinAzul =5;
int piezo =6;
int boton = 2;
int estado =0;
 
void setup() {
  // put your setup code here, to run once:

    pinMode(pinRojo, OUTPUT);
    pinMode(pinAzul, OUTPUT);
    pinMode(piezo, OUTPUT);
    pinMode (boton, INPUT);
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    while (digitalRead(boton)==0)
  {
    digitalWrite(pinRojo, HIGH);
    digitalWrite(pinAzul, LOW);
    delay(500);
    
    digitalWrite(pinRojo, LOW);
    digitalWrite(pinAzul, HIGH);
    delay(500);
  
    tone(piezo, 300,100);
    delay(100);
    tone(piezo, 450,50);
    Serial.println(digitalRead(boton));
    delay(100);
  }


      while (digitalRead(boton)==1)
  {
    digitalWrite(pinRojo, LOW);
    digitalWrite(pinAzul, LOW);
    Serial.println(digitalRead(boton));
  }
}
