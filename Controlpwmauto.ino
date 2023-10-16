  void setup() {

    pinMode(5,OUTPUT);   //motores izquierdos hacia adelante - 5
    pinMode(3,OUTPUT);
    pinMode(2,OUTPUT);
    pinMode(4,OUTPUT);   //motores derechos hacia adelante -3
    pinMode(6,OUTPUT);
    pinMode(9,OUTPUT);

    Serial.begin(9600);
  
  }

  void loop() {
    // Incrementa la velocidad del motor de 0 a 255
      if(Serial.available()){
       // pararMotor();
        int motorSpeed = Serial.parseInt();
        if(motorSpeed != 0){
        analogWrite(6, motorSpeed);
        analogWrite(9, motorSpeed);
        digitalWrite(5, LOW);
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(2, LOW);
        
        delay(3000); // Tiempo de espera
        Serial.println("cargado :" + String(motorSpeed));
        }
      }
  
    
    // Decrementa la velocidad del motor de 255 a 0
  
  
  }

  void pararMotor() {
    digitalWrite(5,LOW);  
    digitalWrite(3,LOW);  
    digitalWrite(4,LOW);  
    digitalWrite(2,LOW);  
     
  }
  