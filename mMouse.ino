#include <PID_v1.h>                            //includes the PID library
#include <avr/pgmspace.h>                      //Allows for the direct usage of flash memory


unsigned char stepProgress = 0;               //the linear displacement since last stopped
unsigned char leftSensor = 0;
unsigned char rightSensor = 0;
unsigned char frontSensor = 0;

#define STEP_LENGTH 16;                        //the distance between two squares
const double L_CORRECTION = 0;                 //the left wheel's constant for steering control (for debugging only)
const double R_CORRECTION = 0;                 //the right wheel's constant for steering control (for debugging only)

const double idealLeftSensor = 46;             //calibrated value for Left sensor. for debugging, not used in final mouse
const double idealRightSensor = 60;

#define L_SENSOR_SETPOINT 46                   //setpoints for error comparison for the robot's sensors 
#define R_SENSOR_SETPOINT 60
#define F_SENSOR_SETPOINT 88

#define NO_FRONT_WALL 770                      //the threshold values determining whether or not a wall is considered present
#define NO_LEFT_WALL 550
#define NO_RIGHT_WALL 600

/* PINS */
#define L_FEEDBACK ?
#define R_FEEDBACK ?
#define L_SENS_PIN ?
#define R_SENS_PIN ?
#define F_SENS_PIN ?
#define L_FORWARD ?
#define R_FORWARD ?
#define L_REVERSE ?
#define R_REVERSE ?




void setup()
{ 
  attachInterrupt(0, incrLeftSteps, RISING);  //increments leftSteps whenever a rising edge is detected from the left motor
  attachInterrupt(1, incrRightSteps, RISING); //increments rightSteps whenever a rising edge is detected from the right motor
  
  
}

void loop()
{
  frontSensor = analogRead(FRONT_SENSOR);         //updates sensor readings
  leftSensor = analogRead(LEFT_SENSOR);
  rightSensor = analogRead(RIGHT_SENSOR);
  
  stepForward();     //move the mouse forward one cell
  update();          //redraws the map according to its surroundings
  faceLowest();      //faces the cell most likely to lead to the center

}


