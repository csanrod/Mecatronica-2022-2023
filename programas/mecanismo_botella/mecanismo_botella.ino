#include <Servo.h>
const unsigned int PIN_SERVO_BOTTLE = 11;
Servo myservo;
float pos;

void setup() 
{  
  Serial.begin(9600);
  myservo.attach(PIN_SERVO_BOTTLE);
  myservo.write(0);
}

void loop() 
{  
  Serial.print("Girando botella");
  
  // Ajustar valor
  for (pos = 0; pos <= 180; pos += 0.5) {
    myservo.write(pos);              
    delay(5);                       
  }

  Serial.print("Sirviendo bebida");
  delay(5000);
  
  for (pos = 180; pos >= 0; pos -= 0.5) {
    myservo.write(pos);              
    delay(5);                       
  }

  Serial.print("Botella vacía");
  delay(5000);
}
