/* Comunicanicacion inalámbrica con NRF24L01
  Ejemplo encendido led - confugracion de modulos
  Transmisor 
  Libreria actualizada - https://github.com/nRF24/RF24
*/

/* Incluimos la libreria SPI basica y la 
libreria RF24 */
#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10); /*Declaro pines a utlizar CE CSN */

const byte address[6] = "00001";   /*Declaro una matriz que permite elegir con que receptor nos comunicaremos, en el ejemplo usamos la misma en el transmisor y receptor*/  

void setup() 
{
  pinMode(5,OUTPUT);   //motores izquierdos hacia adelante - 5
  pinMode(4,OUTPUT);   //motores izquierdos hacia atrás - 4
  pinMode(3,OUTPUT);   //motores derechos hacia adelante -3
  pinMode(2,OUTPUT);   //motores derechos hacia atrás -2

  Serial.begin(9600);       /*comunicacion con el monitor serie de PC*/
  radio.begin();                 /*inicializo radio*/
  radio.openReadingPipe(0, address); /*Declaro direccion del receptor anteriormente delcarada*/
  radio.setPALevel(RF24_PA_MIN); /*Config nivel de amplificador de potencia / ver en caso de aumentar distancias*/
  radio.startListening();  
}

void loop(){
  
  if(radio.available()){
    int datos;
    radio.read(&datos, sizeof(datos));
    Serial.print("Recibido: ");
    Serial.println(datos);
    movimiento(datos);
  }

  delay(200);
}

void movimiento(int valor){

  if(valor == 1){            //mueve hacia adelante
    pararMotor();
    digitalWrite(5,HIGH);
    digitalWrite(3,HIGH);
    Serial.println("va pa delante");
  }
  
  else if(valor == 4){      //hacia atrás
    pararMotor();
    digitalWrite(4,LOW);
    digitalWrite(2,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(2,HIGH);
  }
  
  else if(valor == 3){      //gira las ruedas de la derecha
    pararMotor();
    digitalWrite(3,LOW);
    digitalWrite(3,HIGH);
  }
  
  else  if(valor == 2){      //gira las ruedas de la izquierda
    pararMotor();
    digitalWrite(5,LOW);
    digitalWrite(5,HIGH);
  }


  else if(valor ==  6){    //turn led on or off)
    pararMotor();
    digitalWrite(9,LOW);
    digitalWrite(9,HIGH);
  }
  else if(valor == 5){
    pararMotor();
  }
}

void pararMotor() {
  digitalWrite(5,LOW);  
  digitalWrite(4,LOW);  
  digitalWrite(3,LOW);  
  digitalWrite(2,LOW);  
}