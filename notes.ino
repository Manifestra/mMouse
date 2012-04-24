//Flood-fill Maze
byte xPosition;
byte yPosition;
byte[][] map =
{
{14,13,12,11,10,9,8,7,7,8,9,10,11,12,13,14},
{13,12,11,10,9,8,7,6,6,7,8,9,10,11,12,13},
{12,11,10,9,8,7,6,5,5,6,7,8,9,10,11,12},
{11,10,9,8,7,6,5,4,4,5,6,7,8,9,10,11},
{10,9,8,7,6,5,4,3,3,4,5,6,7,8,9,10},
{9,8,7,6,5,4,3,2,2,3,4,5,6,7,8,9},
{8,7,6,5,4,3,2,1,1,2,3,4,5,6,7,8},
{7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7},
{7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7},
{8,7,6,5,4,3,2,1,1,2,3,4,5,6,7,8},
{9,8,7,6,5,4,3,2,2,3,4,5,6,7,8,9},
{10,9,8,7,6,5,4,3,3,4,5,6,7,8,9,10},
{11,10,9,8,7,6,5,4,4,5,6,7,8,9,10,11},
{12,11,10,9,8,7,6,5,5,6,7,8,9,10,11,12},
{13,12,11,10,9,8,7,6,6,7,8,9,10,11,12,13},
{14,13,12,11,10,9,8,7,7,8,9,10,11,12,13,14}
};
//initial location at 8, has to go forward 1

    {
    Pull a cell from the stack
    Is the distance value of this cell = 1 + the minimum value of its open neighbors?
    No -> Change the cell to 1 + the minimum value of its open neighbors and
    push all of the cell's open neighbors onto the stack to be checked
    Yes -> Do nothing
    }




/*
Displacement
  Displacement: the remaining distance to travel or the remaining angle to turn
  byte leftWheelSteps;
  byte rightWheelSteps;
  byte linDisplacement = the number of steps that both motors need to perform
    to keep track of linDisplacement, we add one to a counter every time either the left wheel or
    the right wheel has a step forward.
  byte angDisplacement = the difference between the displacement of the right wheel and the
    displacement of the left wheel
    to keep track of angDisplacement, we assign positive to the forward of one motor (the left motor)
    and negative to the forward of the other. Each step forward the left wheel makes, we add one to
    the counter. Each step forward the right wheel makes, we subtract one from the counter.
*/

/*
Velocity
byte leftVelocity = linVelocity + angVelocity;
byte rightVelocity = linVelocity - angVelocity;
*/

/*
Acceleration
byte leftAcceleration = linAcceleration + angAcceleration;
byte rightAcceleration = linAcceleration - angAcceleration;
*/

/*
More Displacement
Assume a displacement D to cover. 
Assume we have acceleration acc and deceleration -acc
Assume robot has max speed vMax
Time required to accelerate to vMax is t = vMax / acc
Displacement from 0 to vMax is D == (time * vMax)/2 == (vMax * vMax)/(2 * acc)
  or assuming symmetric deceleration (acceleration 1/2 of the way, deceleration the other 1/2)
  we get D = (vMax * vMax)/acc
  if the displacement is < D = (vMax * vMax)/acc, then we never need to reach maximum speed

if (displacement > (vMax * vMax)/(2 * acc)) {    
  if(currentVelocity < vMax) {
    if(currentAccel < desiredAccel) {
      currentAccel = desiredAccel;                //sets current acceleration to the desired acceleration.
    }
    else {
      currentAccel = 0;                          //if at vMax, stop accelerating
  }
  else if(currentAccel > desiredAccel) {
    currentAcceleration = (desiredAccel * -1);
    }
  }
}
*/
