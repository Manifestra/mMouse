typedef unsigned char uchar;

static uchar xPosition = 0;                    //a value between 0 and 15 representing the robot's current x position
static uchar yPosition = 0;                    //a value between 0 and 15 representing the robot's current y position

static uchar currentFacing = 1;                          //the direction, N,S,E,W which the robot is facing.
                                                         // 0 for North, 1 for East, 2 for South, 3 for West.
static uchar sides[SIDES_CAP] = {255, 255, 255, 255};    //the number of the open sides i.e. adjacent cells with no walls
                                                         //in the way. The array is indexed based on direction. i.e. sides[0]
                                                         //holds the value of the cell to the north, or 255 if it is a wall.
const uchar SIDES_CAP = 4;                               //the capacity of the sides array

const uchar NORTH = 0;                                  //numbers to represent direction
const uchar EAST = 1;
const uchar SOUTH = 2;
const uchar WEST = 3;
                   
static uchar[][] mazeMap =                              //the map of the maze
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
//@param uchar[] - the array to scan
//@param uchar - the capacity of the array
uchar getMinPosition(uchar[] ar, uchar cap)
{
  uchar minIndex;
  uchar index;
  for (index = 0; index < SIDES_SIZE && sides[index] != getSidesMin(); index++)
  {
    minIndex = index;
  }
  return minIndex;
}
    
  
//getSidesMin - searches an array and returns the miminum value.
//@param uchar[] - the array to scan
//@param uchar - the capacity of the array
uchar getSidesMin()
{
  uchar minimum = sides[0];                         //keeps track of the minimum value, set to the first element as default
  uchar index;                                 
  for (index = 1; index < SIDES_CAP; index++)      //traverse the array 4 times
  {
    if (sides[index] < minimum)                     //if an element is less than the current smallest element
    {                                               //update minimum to the value of that element, otherwise do nothing
       minimum = sides[index];                
    }
  }
  return minimum;              
}


//faceLowest - turns towards the lowest number square. The square which the robot currently came from has lower priority
//             in a tie. If three cells all have the same number, give the leftmost cell that is not the one the robot came
//             from has priorty
void faceLowest(){
  
}

//update() - rewrites the map if necessary. If the number of the current square is rewritten to be 1 + the minimum number of
//  the available adjacent squares. A square is available if there is no wall between the robot and it.
//precondition - used immediately after stepping, before turning.
void update()
{
  bool frontWall = (frontSensor < NO_FRONT_WALL);                                          //sets boolean values indicating the presence of walls
  bool leftWall = (leftSensor < NO_LEFT_WALL);
  bool rightWall = (rightSensor < NO_RIGHT_WALL);
    
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
          sides[SOUTH] = (!leftWall && yPosition < 15) ? mazeMap[yPosition + 1][xposition] : 255;        //updates sides[] with the south value
          sides[WEST] = (!frontWall && xPosition > 0) ? mazeMap[yPosition][xPosition - 1] : 255;         //updates sides[] with the west value
          break;
  }
  
  if (getSidesMin() > mazeMap[yPosition][xPosition]){                 //if the current cell is the lowest valued cell, update its value to
    mazeMap[yPosition][xPosition] = getSidesMin() + 1;                //1 + the value of the nearest open cell
  }
}

