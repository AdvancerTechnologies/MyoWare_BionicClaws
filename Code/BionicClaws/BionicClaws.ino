/*****************************************************************************
 **  COPYRIGHT (C) 2014-2015, ADVANCER TECHNOLOGIES, ALL RIGHTS RESERVED.
 *****************************************************************************/

//***********************************************
// Muscle Controlled Bionic Claws
//
// Developed by Brian E. Kaminski - Advancer Technologies, 
// http://www.AdvancerTechnologies.com
//
// License: CC BY-SA 3.0 https://creativecommons.org/licenses/by-sa/3.0/
//
// Revision history:
// 1.0 initial release BEK 25May2015
//***********************************************

#include <Servo.h> 

Servo myservo; 			  		  		

// constants
const int iServoPin = 3;          		// servo pin number
const int iSensorPin = A3;	  	  		// muscle sensor pin number
const int iMaxServoVal = 1140; 	  		// HS-7940's fully extracted claw servo position PWM value (in microseconds)
const int iMinServoVal = 1800;	  		// HS-7940's fully retracted claw servo position PWM value (in microseconds) 
const int iMinThreshVal = 200;	  		// muscle sensor threshold value to begin controlled extension
const int iServoStep = 10;        		// controls claw extension speed - increase to speed up
const unsigned long lLockOut = 2000L;   // duration to hold max threshval to toggle the lock state (in milliseconds)

// global variables
unsigned long lStartTime = 0L;    		// variable to store the time the timer was started
bool bStartLockTimer = false;     		// if true, the timer has been started; false otherwise
bool bActiveLock = false;         		// if true, the claws have been locked in fully extended state; unlocked otherwise.

void setup() 
{ 
  myservo.attach(iServoPin);  			// attaches the pin to the servo object
  delay(10000);							// 10 second delay to give you time to plug in the battery, stow it, and get clear
} 

void loop() 
{ 
  // read muscle sensor value
  int iSensorVal = analogRead(iSensorPin);
  int iServoVal =  iMinServoVal;    // intialize to min value 

  // determine what state to put the claws in based on the sensor value  
  // three possible states
  if(iSensorVal < iMinThreshVal)        
  { 
    // state 1 - below threshold - fully retract claws
    iServoVal = iMinServoVal; 
  }
  else 
  { 
    // state 2 - above max threshold - fully extend claws
    iServoVal = iMaxServoVal; 
  } 
  
  // if sensor is in state 2, start timer to trigger lLockOut
  if(iServoVal == iMaxServoVal)
  {
    // if the timer hasn't been started, then start it.
    if(!bStartLockTimer) 
    {
      lStartTime = millis();
      bStartLockTimer = true;
    }
  }
  else
  {
    // reset timer variables
    lStartTime = 0L;
    bStartLockTimer = false;
  }
    
  // check to see if the timer was started and it runs for the amount of time required to trigger lock/unlock
  if(bStartLockTimer && millis()-lStartTime >= lLockOut)
  {      
    // toggle lock state
    bActiveLock = !bActiveLock;
    
    // reset timer variables
    lStartTime = 0L;
    bStartLockTimer = false;
    
    // set servo value to max when locking
    if(bActiveLock) 
    {
      myservo.writeMicroseconds(iMaxServoVal);  
      iServoVal = iMaxServoVal;  
    }
    else // reset servo value to min when unlocking
    {
      myservo.writeMicroseconds(iMinServoVal);
      iServoVal = iMinServoVal;
    }
    
    // pause for a second to allow the user to adjust to the new setting
    delay(1000);
  }

  // move the servo to the desired postion
  if(bActiveLock)
    myservo.writeMicroseconds(iMaxServoVal);
  else    
    myservo.writeMicroseconds(iServoVal);
    
  // delay to not overload the ADC
  delay(100);
}
