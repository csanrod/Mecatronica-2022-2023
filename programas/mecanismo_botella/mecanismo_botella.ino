#include <Servo.h>
const unsigned int PIN_SERVO_BOTTLE = 10;
Servo myservo;
int pos;

unsigned long t1 = 0;
unsigned long pausa = 2000;//T+Intervalo deseado=10+10=20 seg=20000 mseg


void setup() {
  myservo.attach(PIN_SERVO_BOTTLE);  // attaches the servo on pin 11
  pos=0;
  myservo.write(pos);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(200);                       // waits 28ms for every swept degree
  }

  delay(5000);

  
  /*
  unsigned long diff = millis() - t1;
  if (diff >= pausa) {
    t1=millis();
  
    for (pos = 0; pos <= 180; pos += 5) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(500);                       // waits 28ms for every swept degree
    }
    
    for (pos = 180; pos >= 0; pos -= 5) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(28);                       // waits 28ms for every swept degree
    }
    
  }
  */
}
