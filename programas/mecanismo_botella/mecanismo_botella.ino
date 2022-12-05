#include <Servo.h>
enum states {WAITING_BUTTON,
             INIT_TO_POURING_G,
             INIT_TO_POURING_B,
             POURING,
             GOING_HOME};

const unsigned int PIN_SERVO_GLASS = 10,
                   PIN_SERVO_BOTTLE = 9,
                   PIN_BUTTON = 2;

unsigned long GLASS_MOVING_TIME = 3000,
              BOTTLE_MOVING_TIME = 4000,
              POURING_TIME = 5000;

Servo servo_glass,
      servo_bottle;
      
int glass_init_angle, 
    glass_end_angle, 
    bottle_init_angle,
    bottle_end_angle,
    current_state,
    button_value;

unsigned long move_start_time;

bool glass_home,
     bottle_home;

void setup() {
  Serial.begin(9600);
  current_state = WAITING_BUTTON;
 
  // Glass init
  glass_init_angle = 179;
  glass_end_angle = 135;
  glass_home = true;
  servo_glass.attach(PIN_SERVO_GLASS);
  servo_glass.write(glass_init_angle);

  // Bottle init
  bottle_init_angle = 0;
  bottle_end_angle = 105;
  bottle_home = true;
  servo_bottle.attach(PIN_SERVO_BOTTLE);
  servo_bottle.write(bottle_init_angle);

  // Button
  button_value = LOW;
  pinMode(PIN_BUTTON, INPUT);
}

void loop() {
  button_value = digitalRead(PIN_BUTTON); // pull up?? bouncing??
  
  // check_button(button_value, current_state, move_start_time)  
  if (button_value == HIGH) && (current_state == WAITING_BUTTON){
    current_state = INIT_TO_POURING_G;
    move_start_time = millis();
  }
    
  
  if (current_state != WAITING_BUTTON) {
    unsigned long progress = millis() - move_start_time;
    
    switch (current_state){
      case INIT_TO_POURING_G:
        // move_glass_to_pouring_pose();
        if (progress <= GLASS_MOVING_TIME) {
          long angle = map(progress, 0, GLASS_MOVING_TIME, glass_init_angle, glass_end_angle);
          servo_glass.write(angle);
        } else {
          current_state = INIT_TO_POURING_B;
          move_start_time = millis();
          glass_home = false;
        }
        
        break;
        
      case INIT_TO_POURING_B:
        // move_bottle_to_pouring_pose();
        if (progress <= BOTTLE_MOVING_TIME) {
          long angle = map(progress, 0, BOTTLE_MOVING_TIME, bottle_init_angle, bottle_end_angle);
          servo_bottle.write(angle); 
        } else {
          current_state = POURING;
          move_start_time = millis();
          bottle_home = false;
        }
        
        break;
        
      case POURING:
        // pouring();
        if (progress >= POURING_TIME) {
          current_state = GOING_HOME;
          move_start_time = millis();
        }
      
        break;
        
      case GOING_HOME:
        // set_all_to_default();
        if (progress <= GLASS_MOVING_TIME) {
          long angle = map(progress, 0, GLASS_MOVING_TIME, glass_end_angle, glass_init_angle);
          servo_glass.write(angle);
        } else 
          glass_home = true;

        if (progress <= BOTTLE_MOVING_TIME) {
          long angle = map(progress, 0, BOTTLE_MOVING_TIME, bottle_end_angle, bottle_init_angle);
          servo_bottle.write(angle); 
        } else
          bottle_home = true;

        if (glass_home && bottle_home)
          current_state = WAITING_BUTTON;
        
        break;      
    }
  }
}

void check_button() {
  if (button_value == HIGH) && (current_state == WAITING_BUTTON){
    current_state = INIT_TO_POURING_G;
    move_start_time = millis();
  }
}

void move_glass_to_pouring_pose(){
  if (progress <= GLASS_MOVING_TIME) {
    long angle = map(progress, 0, GLASS_MOVING_TIME, glass_init_angle, glass_end_angle);
    servo_glass.write(angle);
  } else {
    current_state = INIT_TO_POURING_B;
    move_start_time = millis();
    glass_home = false;
  }
}

void move_bottle_to_pouring_pose() {
  if (progress <= BOTTLE_MOVING_TIME) {
    long angle = map(progress, 0, BOTTLE_MOVING_TIME, bottle_init_angle, bottle_end_angle);
    servo_bottle.write(angle); 
  } else {
    current_state = POURING;
    move_start_time = millis();
    bottle_home = false;
  }
}

void pouring() {
  if (progress >= POURING_TIME) {
    current_state = GOING_HOME;
    move_start_time = millis();
  }
}

void set_all_to_default() {
  if (progress <= GLASS_MOVING_TIME) {
    long angle = map(progress, 0, GLASS_MOVING_TIME, glass_end_angle, glass_init_angle);
    servo_glass.write(angle);
  } else 
    glass_home = true;

  if (progress <= BOTTLE_MOVING_TIME) {
    long angle = map(progress, 0, BOTTLE_MOVING_TIME, bottle_end_angle, bottle_init_angle);
    servo_bottle.write(angle); 
  } else
    bottle_home = true;

  if (glass_home && bottle_home)
    current_state = WAITING_BUTTON;
}
