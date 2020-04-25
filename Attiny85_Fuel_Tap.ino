//ATtiny85 Fuel Switch.  One button with LED. Off is start up state.  One press to On with LED lighting. 
//                       One press to turn off and LED Off
const int led = 3;      // on/off led to tell if tap is on
const int button = 1;
int led_state = LOW;

// Button states and debounce
int buttonState = 0;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;

#include <SoftwareServo.h>

SoftwareServo myservo;  // creates name “my servo” as object to control a servo 
int pos = 0;            // variable to store the servo position 
int start_angle = 0;  
int end_angle = 180;
int servo_pin = 0;      // pin servo is attached to
int delay_time = 10;
int tap = false; 

void setup() {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  myservo.attach(servo_pin);
  on();
}

void loop() {
  int reading = digitalRead(button);
  if (reading != lastButtonState)
    lastDebounceTime = millis();

  if ((millis() - lastDebounceTime) > 10) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        led_state = !led_state;
        if (led_state == HIGH) 
        {off();
        }
        else{
       on();
        }
        }
      }
    }

  lastButtonState = reading;

//  digitalWrite(led, led_state);
}
  void on (){
          for(pos = 0; pos <= 180; pos += 1)        // goes from 0 degrees to 180 degrees 
        {                                         // in steps of 1 degree 
          myservo.write(pos);                     // tell servo to go to position in variable 'pos' 
          delay(delay_time);                      
          SoftwareServo::refresh();               // required by SoftwareServo Library to sweep correctly
        }           
       // delay (delay_time);                       // required by SoftwareServo Library to sweep correctly
    tap = true;
      digitalWrite(led, led_state);
    }
  
  void off(){
      for(pos = 180; pos>=0; pos-=1)  
        {                                
          myservo.write(pos);                     // tell servo to go to position in variable 'pos' 
          delay(delay_time);                      
          SoftwareServo::refresh();               // required by SoftwareServo Library to sweep correctly
        }
        delay(delay_time);                        // required by SoftwareServo Library to sweep correctly 
    tap = false;  
      digitalWrite(led, led_state);
  }   
  
