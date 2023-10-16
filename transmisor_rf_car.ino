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
      Serial.begin(9600);
      radio.begin();                 /*inicializo radio*/
      radio.openWritingPipe(address); /*Declaro direccion del receptor anteriormente delcarada*/
      radio.setPALevel(RF24_PA_MIN); /*Config nivel de amplificador de potencia / ver en caso de aumentar distancias*/
      radio.stopListening(); 
    
    }


    void loop(){
      if(Serial.available()>0){
      int datos = Serial.parseInt();
      radio.write(&datos, sizeof(datos));
      Serial.print("Enviado: ");
      Serial.println(datos);
      delay(1000);
      }
    }

