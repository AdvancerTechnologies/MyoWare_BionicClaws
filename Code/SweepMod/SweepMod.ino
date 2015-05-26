// SweepMod
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
int angle = 0;    // variable to store the servo position 
 //
void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(3);  // attaches the servo on pin 3 to the servo object 
  angle = 150;
  int microSec = map(angle, 0, 180, 1050, 1950);
  myservo.writeMicroseconds(microSec);
  delay(2000);
} 
 
 
void loop() 
{ 
  angle = 18;
  int microSec = map(angle, 0, 180, 1050, 1950);
  myservo.writeMicroseconds(microSec);
  Serial.println(microSec);
  delay(250);
  
  angle = 150;
  microSec = map(angle, 0, 180, 1050, 1950);
  myservo.writeMicroseconds(microSec);
  Serial.println(microSec);
  delay(2000);
} 
