#include <LiquidCrystal.h>
#include <Servo.h>//Librería para el servo

//Creación de variables
int trig = 13; //Envía una onda ultrasónica a través del disparador
int echo = 12; // Recibe las ondas que rebotan en el objeto
float disCalculada; //Variable que guarda el valor de la distancia
int piezo=2; //variable del pin del piezo

//Variables dem los led
int ledRojo = 10;
int ledVerde = 11;


//Estos datos son para el servo
Servo servo1; //Constructor de la sentencia servo

int puertoservo=3; //variable que envía datos al servo
int grados; //Variable que guarda los grados del ángulo del servo
int tmp=0; //variable temporal
int pulsominimo=650; //variable que define el ángulo menor del servo
int pulsomaximo=2550; //variable que define el ángulo mayor del servo


//Datos para la contraseña con la LCD
LiquidCrystal lcd(8,9, 4, 5, 6, 7);

int adc_key_val[5] = {50, 200, 400, 600, 800 };

int NUM_KEYS = 5;              

int adc_key_in;              /// Variables que se utilizan para el manejo del teclado de la pantalla(boton presionado)
int key=-1;
int oldkey=-1;


boolean luzEncendida=true;      // variable bool para saber cuando la luz esta apagada o encendida
boolean cursorActivo=false;    // variable bool para saber si el cursor esta activo o no
unsigned long time;

int x=0;   /// variable que se utiliza para llevar la posicion x en la matriz de la pantalla

String contrasena = "123";// variable String para almacenar la contraseña permanente
String nuevaContra="";   // variable String en la que se guardará la nueva contrasenna temporalmente

int tam = contrasena.length();   // obtener el tamano del de la contrasena

char caracterActual = '0';   // char que se utilizará para recibir cada caracter que se ingresa con los botones


int conta=0;  // Index para llevar el control cuando compara la contrasena vieja con la insertada en ese momento
int m =0;  // Contador para llevar las comparaciones en Login
int t = 0;  // Contador para llevar el total de intentos del Login



int conta2= 0;  // Index para llevar el control cuando compara la contrasena vieja con la insertada en ese momento en la parte de Digitar Vieja contrasenna
int m2 = 0;  // Contador para llevar las comparaciones en Digitar Vieja contrasenna
int t2= 0;  // Contador para llevar el total de intentos en Digitar Vieja contrasenna

int conta3 = 0;  // El index global que se utiliza para ir insertando la contrasenna nueva en la variable de contrasenna nueva


 //Estados / Login, Digitar vieja contra y digitar Nueva contra
int estado = 0;   // 0 -> Login
                   // 1 -> Vieja Contrasenna 
                   // 2 -> Nueva Contrasenna
  


//-------------------------------------------------------------------------
void setup() {
  // Se activan los eventos que requerimos para el sensor ultrasónico
  pinMode (trig, OUTPUT);
  pinMode (echo, INPUT);
  pinMode(piezo, OUTPUT); 
  Serial.begin (9600);//activa el monitor serial a una frecuencia de 9600 para ir viendo sus valores

//LED
pinMode (ledRojo, OUTPUT);
pinMode (ledVerde, OUTPUT);

//Instrucciones para la LCD
for(int i=0; i<10; i++){
  tone(piezo,200,100);
  lcd.setCursor(4,1); //Posición 4 de la fila 1.
  lcd.print("Bienvenido"); //muestra en pantalla el texto
  lcd.noBlink(); //para que la pantalla no parpadee.
  delay(200);
  
}

//COnfiguración para la contraseña con LCD
  lcd.clear(); 
  lcd.begin(16, 2);
  lcd.setCursor(0,0); 
  lcd.print("Contrasena");
  time = millis();         // variable para llevar un timer 

//Se indica al servo por cuál pin nos vamos a comunicar y cuál es su ángulo máximo y mínimo
  servo1.attach(puertoservo,pulsominimo,pulsomaximo);

}



//-----------------------------------------------------------------------
void loop() {
  // Todo esto es para programar el sensor ultrasónico
  disCalculada = calcularDistancia(); //A la variable disCalculada le devolvemos el valor del procedimiento


 //Código para el servo
  grados=servo1.read(); //Esta variable guarda los grados del ángulo que giró el servo.


  // Esta condicional es para el piezo, si está a una distancia menor a 100 suena el piezo, sino no haga nada. En el caso del servo se utiliza la variable temporal.
  if(disCalculada < 20)
  {
   // tone(piezo,600,100);
    Login();
    
  }
  else
  {
  }
  servo1.write(0);
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
//-------------------------------------------------------------------------------------

void Login(){
    
      adc_key_in = analogRead(0);    // Variable que lee el valor de la pulsacion
      key = get_key(adc_key_in);    // Obtenemos el boton pulsado
    
      if (key != oldkey)   // si se ha apretado una tecla
      {
        delay(50);  // Espera para evitar los rebotes de las pulsaciones
        adc_key_in = analogRead(0);    // Leemos el valor de la pulsación
        key = get_key(adc_key_in);    // Obtenemos el botón pulsado
        if (key != oldkey)    
        {
          time = millis();  // TODO: falta la comprobacion de si se ha desbordado el tiempo
          if (!luzEncendida) {  // Al pulsar cualquier tecla encendemos la pantalla
           // pinMode(10, INPUT);
            luzEncendida=true;
          } 
          else {  // si la pantalla esta encendida seguimos funcionando normalmente
            lcd.setCursor(x, 1);
            oldkey = key;
            if (key >=0){  // Si se ha pulsado cualquier tecla
              lcd.blink();  // Mostramos el cursor parpadeando
              cursorActivo=true;   
            }
          }
         
         
            if ((key == 0) && (estado==0)){  // Se ha pulsado la tecla derecha en login
              
              char c = caracterActual;
              if(c==contrasena[conta]){
                m++;
              }
              else{
                m--;
              }
              conta++;
              x++;
              if (x>15) x=15;
              caracterActual='0';
            }
            else if ((key == 0) && (estado==1)){  // Se ha pulsado la tecla derecha en digitar vieja contra
                  
                  char c = caracterActual;
                  if(c==contrasena[conta2]){
                    m2++;
                  }
                  else{
                    m2--;
                  }
                  conta2++;
                  x++;
                  if (x>15) x=15;
                  caracterActual='0';
                }
            
            else if ((key == 0) && (estado==2)){  // Se ha pulsado la tecla derecha en digitar nueva contrasenna
                  
                  String c = String(caracterActual);
                  
                  nuevaContra= nuevaContra+c;
                    
                  //conta3++;
                  x++;
                  if (x>15) x=15;
                  caracterActual='0';
                }
            
            
            
            else if ((key == 1) && (estado==0)) {  // Se ha pulsado la tecla arriba en login
                caracterActual++;
              if (caracterActual > '9') caracterActual='9';
                lcd.write(caracterActual);
            }
            
            else if ((key == 1) && (estado==1)) {  // Se ha pulsado la tecla arriba en digitar vieja contrasena
                  caracterActual++;
                  if (caracterActual > '9') caracterActual='9';
                  lcd.write(caracterActual);
            }
            
            else if ((key == 1) && (estado==2)) {  // Se ha pulsado la tecla arriba en digitar nueva contrasenna
                  caracterActual++;
                  if (caracterActual > '9') caracterActual='9';
                  lcd.write(caracterActual);
            }
            
            
            else if ((key == 2) && (estado==0)) {  // Se ha pulsado la tecla abajo en login
                caracterActual--;
              if (caracterActual < '0') caracterActual='0';
                lcd.write(caracterActual);
            }
            
            else if ((key == 2) && (estado==1)) {  // Se ha pulsado la tecla abajo en digitar vieja contrasenna
                  caracterActual--;
                  if (caracterActual < '0') caracterActual='0';
                  lcd.write(caracterActual);
            }
                
            else if ((key == 2) && (estado==2)){  // Se ha pulsado la tecla abajo en digitar nueva contrasenna
                  caracterActual--;
                  if (caracterActual < '0') caracterActual='0';
                  lcd.write(caracterActual);
            }
            
            else if((key == 3) && (estado==0)){    // Se ha pulsado la tecla izquierda en login
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.clear();
              lcd.print("Vieja Contra");
              
              estado=1; // se cambia el estado a 1 indicando que ahora esta digitando la vieja contrasenna
              
            }

            else if ((key == 4) && (estado==0)){  // Se ha pulsado la tecla de seleccion en login
            
               lcd.clear();
               
               if(m==tam){
                 tone(piezo,600,100);
                 delay(2000);
                 servo1.write(100);
                 delay(2000);
                 lcd.setCursor(4,1);
                 lcd.print("CORRECTO");
                 digitalWrite(11, HIGH);   // enciende el led verde, indicando que la puerta se ha abierto
                 delay(2000);              // se espera por 2 segundos
                 digitalWrite(11, LOW);   // apaga la luz 
                 limpiar();              // limpia todos los contadores que se utilizan para llevar la posición actual,entre otros.
                 setup();
               }
               else{
                 lcd.setCursor(4,1);
                 lcd.print("INCORRECTO");
                 digitalWrite(10, HIGH);   // enciende el led rojo,indicando que se ha ingresado una contraseña errónea
                 delay(2000);   
                 digitalWrite(10, LOW); // se espera por 2 segundos
                 if(t==2){
                   for(int i=0; i<5; i++){   // for que se utiliza para encender el led rojo intermitentemente
                   digitalWrite(10, HIGH);
                   delay(500);
                   digitalWrite(10, LOW);
                   delay(500);
                   }
                   lcd.clear();
                   lcd.begin(16, 2);
                   lcd.setCursor(0,0); 
                   lcd.print("Contrasena");
                   t=0;
                 }
                 else{
                   
                   lcd.clear();
                   t++;
                   conta=0;
                   x=0;
                   m=0;
                   caracterActual = '0';
                   setup();
                 }
               }
            }
            
            
            else if((key==4) && (estado==1)){
                                      // Se ha pulsado la tecla de selección en digitar vieja contraseña
                 lcd.clear();
                 
                 if(m2==tam){
                   lcd.setCursor(0,0);
                   x=0;
                   lcd.clear();
                   lcd.print("Nueva Contra"); 
                   estado=2;                   /// se cambia el estado a 2,indicando que ahora está digitando nueva contraseña
                   
                   
                 }
                 else{
                   lcd.setCursor(3,1);
                   lcd.print("Incorrecta");
                   digitalWrite(10, HIGH);   // enciende el led rojo
                   delay(2000);              // se espera por 2 segundos
                   if(t2==2){
                     for(int i=0; i<10; i++){
                     digitalWrite(13, HIGH);
                     delay(500);
                     digitalWrite(13, LOW);
                     delay(500);
                     }
                   }
                   else{
                     
                     lcd.clear();
                     t2++;
                     conta2=0;
                     x=0;
                     m=0;
                     caracterActual = '0';
                     lcd.clear();
                     lcd.setCursor(0,0);
                     lcd.print("Vieja Contra");
                   }
               }
              
            }
            
            else if ((key == 4) && (estado==2)){  // Se ha pulsado la tecla de selección en digitar nueva contraseña
                  
                  lcd.clear();
                  lcd.print("Cambio Exitoso");
                  contrasena =nuevaContra;

                  delay(2000);
                  lcd.clear();
                  limpiar();
                  setup();
                
              }
          
          }
        }
     delay(100);
   }


//-------------------------------------------------------------------------

// Convertimos el valor leído en analógico en un número de botón pulsado
int get_key(unsigned int input)
{
  int k;

  for (k = 0; k < NUM_KEYS; k++)
  {
    if (input < adc_key_val[k])
    {
      return k;
    }
  }

  if (k >= NUM_KEYS)k = -1;  // Error en la lectura
  return k;
}
//-------------------------------------------------------------------------

void limpiar(){  /// Función para limpiar todos los contadores
   x=0;
   t=0;
   t2=0;
   m=0;
   m2=0;
   conta=0;
   conta2=0;
   conta3=0;
   estado=0;
  
   
}
