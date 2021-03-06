#define NORTH 0                                          //numbers representing direction
#define EAST 1
#define SOUTH 2
#define WEST 3

unsigned char xPosition = 0;                              //a value between 0 and 15 representing an x coordinate
unsigned char yPosition = 0;                              //a value between 0 and 15 representing a y coordinate
unsigned char mouseX = 0;                                 //a value representing the robot's current x position
unsigned char mouseY = 0;                                 //a value representing the robot's current y position

unsigned char currentFacing = 1;                          //the direction, N,S,E,W which the robot is facing.
                                                          // 0 for North, 1 for East, 2 for South, 3 for West.
unsigned char sides[4] = {255, 255, 255, 255};            //the number of the open sides i.e. adjacent cells with no walls
                                                       //in the way. The array is indexed based on direction. i.e. sides[0]
                                                       //holds the value of the cell to the north, or 255 if it is a wall.
                   
unsigned char mazeMap[16][16] =                               //the map of the maze, can keep static if merge movement with mapping
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

unsigned char walls[16][16] = {
{0x02,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0C},  
{0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0D},
{0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0D},
{0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0D},
{0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0D},
{0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0D},
{0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0D},
{0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0D},
{0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0D},
{0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0D},
{0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0D},
{0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0D},
{0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0D},
{0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0D},
{0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0D},
{0x03,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x09}};


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
    if (tmp + 1 == 4){      //changed from 5 to 4
      tmp = 0x00;
    }
    else{
      ++tmp;
    }
  }
  //if 
  return tmp;
}

void printDirection(unsigned char dir){
  if (dir == 0){
    Serial.println("North");
  }
  else if (dir == 1){
    Serial.println("East");
  }
  else if (dir == 2){
    Serial.println("South");
  }
  else if (dir == 3){
    Serial.println("West");
  }
}

void TheFlood(){
   unsigned char STACK_CAPACITY = 50;
   walls[mouseY][mouseX] = getWallConfig(mouseX, mouseY);
   fillSides(sides, mouseX, mouseY);
   if (checkCell(sides, mouseX, mouseY);
   {
     //faceideal
   }
   else 
   {
     unsigned char stackSize = 0;
     unsigned char xPosition = mouseX;
     unsigned char yPosition = mouseY;
     do {
       if (stackSize == STACK_CAPACITY)
       {
         //increase capacity
       }
       mazeMap[yPosition][xPosition] = getSidesMin() + 1;
       masterPush(sides, xPosition, yPosition);
       uchar cellPos = pop();
       xPosition = getX(cellPos);
       yPosition = getY(cellPos);
       fillSides(sides, xPosition, yPosition);
       if (!checkCell(sides, xPosition, yPosition)
       {
          masterPush(sides, xPosition, yPosition);
       }
      while (stackSize > 0);
     }
   }
}


