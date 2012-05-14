#define NORTH 0                                          //numbers representing direction
#define EAST 1
#define SOUTH 2
#define WEST 3



static unsigned char xPosition = 0;                              //a value between 0 and 15 representing the robot's current x position
static unsigned char yPosition = 0;                              //a value between 0 and 15 representing the robot's current y position

static unsigned char currentFacing = 1;                          //the direction, N,S,E,W which the robot is facing.
                                                         // 0 for North, 1 for East, 2 for South, 3 for West.
static unsigned char sides[4] = {255, 255, 255, 255};    //the number of the open sides i.e. adjacent cells with no walls
                                                         //in the way. The array is indexed based on direction. i.e. sides[0]
                                                         //holds the value of the cell to the north, or 255 if it is a wall.
                   
static unsigned char mazeMap[][16] =                               //the map of the maze, can keep static if merge movement with mapping
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

//getMinPosition - searches an array and returns the index of the miminum value. This position will equal the direction
//                 of the lowest numbered open adjacent cell
//@return - the position of the smallest value
unsigned char getMinPosition()
{
  unsigned char minValue = getSidesMin();
  if (sides[0] == minValue) return 0;
  if (sides[1] == minValue) return 1;
  if (sides[2] == minValue) return 2;
  if (sides[3] == minValue) return 3;
}
    
//shiftClockwise - returns the direction (numOfTimes * 90degrees) clockwise of the init position
//@param numOfTimes - the amount of times you wish to look in terms of 90 degree clockwise increments on the compass
//      example
//           shiftClockwise(1, NORTH) == EAST, shiftClockwise(2, SOUTH) == NORTH
//@param initPosition - the position you are looking from. usually currentFacing
//@return - the direction numOfTimes * 90degrees clockwise of the init position
unsigned char shiftClockwise(unsigned char initPosition, unsigned char numOfTimes)
{
  unsigned char tmp = initPosition;
  /* unroll this loop */
  for (unsigned char i = 0; i < numOfTimes; i++){
    if (tmp + 0x01 == 0x05){
      tmp = 0x00;
    }
    else{
      ++tmp;
    }
  }
  //if 
  return tmp;
}

//getValueFrom - gets the value of the cell to the north, east, south, or west of the robot
//@param facing - the direction to look for the value, north, east, south, or west
//@return - the floodfill value of the referenced cell
unsigned char getValueFrom(unsigned char facing)
{
  switch (facing)
  {
    case NORTH:
      if(yPosition > 0) return mazeMap[yPosition - 1][xPosition];
      else return 255;
      break;
    case EAST:
      if(xPosition < 15) return mazeMap[yPosition][xPosition + 1];
      else return 255;
      break;
    case SOUTH:
      if(yPosition < 15) return mazeMap[yPosition + 1][xPosition];
      else return 255;
      break;
    case WEST:
      if(xPosition > 0) return mazeMap[yPosition][xPosition - 1];
      else return 255;
      break;
  }
}
  
//getSidesMin - searches the sides array and returns the miminum value.
//@return - the minimum value
unsigned char getSidesMin()
{
  unsigned char minimum = sides[0];                       // keeps track of the minimum value, set to the first element by default
  if (sides[1] < minimum) minimum = sides[1];     // Checks if values at the remaining positions in the array 
  if (sides[2] < minimum) minimum = sides[2];     // are less than the default minimum, updating the minimum accordingly
  if (sides[3] < minimum) minimum = sides[3];     
  return minimum;              
}


//faceLowest - turns towards the lowest number square. The square which the robot currently came from has lower priority
//             in a tie. If three cells all have the same number, the leftmost cell that is not the one the robot came
//             from has priorty
void faceLowest(){
  unsigned char minAdj = getSidesMin();                 //sets minAdj (minimum adjacent) equal to the lowest value of the adjacent sides[] array
  if (getValueFrom(currentFacing) == minAdj)                            //if the square in front of the robot is lower than its current square, maintain heading
  {}   
  else if (getValueFrom(shiftClockwise(currentFacing, 3)) == minAdj)    //if the square to the left is a minimum, turn left
  {
    turnLeft();
  }
  else if (getValueFrom(shiftClockwise(currentFacing, 1)) == minAdj)    //if the square to the right is a minimum, turn right
  {
    turnRight();
  }
  else                                                                  //else make a u-turn
  {
    turnLeft();
    turnLeft(); 
  }
  
}

//update() - rewrites the map if necessary. If the number of the current square is rewritten to be 1 + the minimum number of
//  the available adjacent squares. A square is available if there is no wall between the robot and it.
//precondition - used immediately after stepping, before turning.
void update()
{
  boolean frontWall = (frontSensor < NO_FRONT_WALL);                                                        //sets boolean values indicating the presence of walls
  boolean leftWall = (leftSensor < NO_LEFT_WALL);
  boolean rightWall = (rightSensor < NO_RIGHT_WALL);
    
  switch (currentFacing)                                                                                 //updates the sides[] array
  {
    case NORTH:                                                                                          //if the robot is currently facing north                                                     
          sides[NORTH] = (!frontWall && yPosition > 0) ? mazeMap[yPosition - 1][xPosition] : 255;        //updates sides[] with the north value
          sides[EAST] = (!rightWall && xPosition < 15) ? mazeMap[yPosition][xPosition + 1] : 255;        //updates sides[] with the east value
          sides[SOUTH] = mazeMap[yPosition + 1][xPosition];                                              //updates sides[] with value last moved from
          sides[WEST] = (!leftWall && xPosition > 0) ? mazeMap[yPosition][xPosition - 1] : 255;          //updates sides[] with the west value
          break;
     case EAST:                                                                                          //if the robot is currently facing east
          sides[NORTH] = (!leftWall && yPosition > 0) ? mazeMap[yPosition - 1][xPosition] : 255;         //updates sides[] with the north value
          sides[EAST] = (!frontWall && xPosition < 15) ? mazeMap[yPosition][xPosition + 1] : 255;        //updates sides[] with the east value
          sides[SOUTH] = (!rightWall && yPosition < 15) ? mazeMap[yPosition + 1][xPosition] : 255;       //updates sides[] with the south value
          sides[WEST] = (xPosition > 0) ? mazeMap[yPosition][xPosition - 1] : 255;                       //updates sides[] with west value (checks if initial conditions)
          break;
     case SOUTH:                                                                                         //if the robot is currently facing south
          sides[NORTH] = mazeMap[yPosition - 1][xPosition];                                              //updates sides[] with value last moved from
          sides[EAST] = (!leftWall && xPosition < 15) ? mazeMap[yPosition][xPosition + 1] : 255;         //updates sides[] with the east value
          sides[SOUTH] = (!frontWall && yPosition < 15) ? mazeMap[yPosition + 1][xPosition] : 255;       //updates sides[] with the south value
          sides[WEST] = (!rightWall && xPosition > 0) ? mazeMap[yPosition][xPosition - 1] : 255;         //updates sides[] with the west value
          break;
      case WEST:                                                                                         //if the robot is currently facing west
          sides[NORTH] = (!rightWall && yPosition > 0) ? mazeMap[yPosition - 1][xPosition] : 255;        //updates sides[] with the north value
          sides[EAST] = mazeMap[yPosition][xPosition + 1];                                               //updates sides[] with value last moved from
          sides[SOUTH] = (!leftWall && yPosition < 15) ? mazeMap[yPosition + 1][xPosition] : 255;        //updates sides[] with the south value
          sides[WEST] = (!frontWall && xPosition > 0) ? mazeMap[yPosition][xPosition - 1] : 255;         //updates sides[] with the west value
          break;
  }
  
  if (getSidesMin() > mazeMap[yPosition][xPosition]){                 //if the current cell is the lowest valued cell, update its value to
    mazeMap[yPosition][xPosition] = getSidesMin() + 1;                //1 + the value of the nearest open cell
  }
}

//wallInFront - returns true if there is a wall in front of the mouse
boolean wallInFront(){
  if(frontSensor < NO_FRONT_WALL) return true;
  else return false;
}

//walToLeft - returns true if there is a wall to the left of the mouse
boolean wallToLeft(){
  if(frontSensor < NO_LEFT_WALL) return true;
  else return false;
}

//walToRight - returns true if there is a wall to the right of the mouse
boolean wallToRight(){
  if(frontSensor < NO_RIGHT_WALL) return true;
  else return false;
}
