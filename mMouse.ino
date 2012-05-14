

volatile unsigned long leftWheelSteps = 0;
volatile unsigned long rightWheelSteps = 0;
unsigned long stepProgress = 0;                        //the linear displacement since last stopped
unsigned long leftSensor = 0;
unsigned long rightSensor = 0;
unsigned long frontSensor = 0;

#define STEP_LENGTH 250;                        //the distance between two squares

#define F_SENSOR_SETPOINT 850

#define NO_FRONT_WALL 770                      //the threshold values determining whether or not a wall is considered present
#define NO_LEFT_WALL 550
#define NO_RIGHT_WALL 600

/* PINS */
#define L_FEEDBACK 2
#define R_FEEDBACK 3
#define L_SENS_PIN A6
#define R_SENS_PIN A7
#define F_SENS_PIN A5
#define L_PLUS 4
#define R_PLUS 7
#define L_MINUS 5
#define R_MINUS 6
#define EN_LEFT 10
#define EN_RIGHT 11




void setup()
{ 
  Serial.begin(9600);
  attachInterrupt(0, incrLeftSteps, RISING);  //increments leftSteps whenever a rising edge is detected from the left motor
  attachInterrupt(1, incrRightSteps, RISING); //increments rightSteps whenever a rising edge is detected from the right motor
  pinMode(EN_LEFT, OUTPUT);
  pinMode(EN_RIGHT, OUTPUT);
  pinMode(L_PLUS, OUTPUT);
  pinMode(L_MINUS, OUTPUT);
  pinMode(R_MINUS, OUTPUT);
  pinMode(R_PLUS, OUTPUT);
  pinMode(F_SENS_PIN, INPUT);
  pinMode(L_SENS_PIN, INPUT);
  pinMode(R_SENS_PIN, INPUT);
  left_right_calibration(); 
  
}

void loop()
{
  frontSensor = analogRead(F_SENS_PIN);         //updates sensor readings
  leftSensor = analogRead(L_SENS_PIN);
  rightSensor = analogRead(R_SENS_PIN);
  
  stepForward();     //move the mouse forward one cell
  update();          //redraws the map according to its surroundings
  faceLowest(); //faces the cell most likely to lead to the center
  
  //if mazeMap([yPosition][xPosition] == 0){
    //xPosition = 0; yPosition = 0;
    //delay(10000);
  //}
}
