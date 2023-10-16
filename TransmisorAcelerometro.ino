//include RF
#include <SPI.h>
#include <RF24.h>
//include Acelerometro
#include "Wire.h"       
#include "I2Cdev.h"     
#include "MPU6050.h"    

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
  byte X;
  byte Y;
  byte Z;
};

MyData data;
RF24 radio(9, 10); /*Declaro pines a utlizar CE CSN */

const byte address[6] = "00001";


void setup() {
  //Configuracion de comunicacion
    Serial.begin(9600);
    radio.begin();                 /*inicializo radio*/
    radio.openWritingPipe(address); /*Declaro direccion del receptor anteriormente delcarada*/
    radio.setPALevel(RF24_PA_MIN); /*Config nivel de amplificador de potencia / ver en caso de aumentar distancias*/
    radio.stopListening(); 


  //Configuracion de Acelerometro
  // Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

}


void loop() {

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 0, 255 ); // X axis data
  data.Y = map(ay, -17000, 17000, 0, 255); 
  data.Z = map(az, -17000, 17000, 0, 255);  // Y axis data
  delay(1000);
  Serial.print("Axis X = ");
  Serial.print(data.X);
  Serial.print("  ");
  Serial.print("Axis Y = ");
  Serial.print(data.Y);
  Serial.print("  ");
  Serial.print("Axis Z  = ");
  Serial.println(data.Z);

  if(data.X > 20 && data.X < 50){ //ADELANTE
    int valorX = 1;
    enviar(valorX);
  }

  if(data.X > 150  && data.X< 180){ //ATRAS
    int valorX = 4;
    enviar(valorX);
  }

  else{ //otro valor se detiene
    int valorX = 5;
    enviar(valorX);
  }



}

void enviar(int num){ // Envio por RF el dato que obtengo 
  if(num > 0){
    //int datos = Serial.parseInt();
    radio.write(&num, sizeof(num));
    Serial.print("Enviado: ");
    Serial.println(num);
    delay(500);
  }
}
