/* Wall Presence Functions */
boolean isLeftWall(){
  return (leftSensor < NO_LEFT_WALL);
}
boolean isRightWall(){
  return (rightSensor < NO_RIGHT_WALL);
}
boolean isFrontWall(){
  return (frontSensor < NO_FRONT_WALL);
}
/* Bit-Access Functions */
unsigned char setBit(unsigned char x, unsigned char k, unsigned char b) {
return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char getBit(unsigned char x, unsigned char k) {
return ((x & (0x01 << k)) != 0);
}

//getWallConfig - returns a char whose bits 3:0 represent the wall configuration of the mouse's current cell
//@return unsigned char - the configuration of walls in the current square. Bits[3:0] represent the wall's status.
// B3 represents WEST, B2 represents SOUTH, B1 represents EAST, B0 represents NORTH
// 1 represents an open path, 0 represents a wall. EG, the starting configuration would be 0x02
unsigned char getWallConfig(){
  boolean leftWall = isLeftWall();
  boolean rightWall = isRightWall();
  boolean frontWall = isFrontWall();
  unsigned char wallConfig = 0x00;
  switch (currentFacing)                                                                                 
  {
    case NORTH:                                                                               //if the robot is currently facing north                                                     
          wallConfig |= 0x04;                                                                      //Just came from south, south wall must be open
          leftWall ? setBit(wallConfig, WEST, 0) : setBit(wallConfig, WEST, 1);
          rightWall ? setBit(wallConfig, EAST, 0) : setBit(wallConfig, EAST, 1);
          frontWall ? setBit(wallConfig, NORTH, 0) : setBit(wallConfig, NORTH, 1);
          break;
     case EAST:                                                                               //if the robot is currently facing east
          if ((mouseX != 0) || (mouseY != 0)){ wallConfig |= 0x08; }                               //Just came from west, west wall must be open...
          else { wallConfig &= 0xF7; }                                                             //  ...unless in starting position
          leftWall ? setBit(wallConfig, NORTH, 0) : setBit(wallConfig, NORTH, 1);
          rightWall ? setBit(wallConfig, SOUTH, 0) : setBit(wallConfig, SOUTH, 1);
          frontWall ? setBit(wallConfig, EAST, 0) : setBit(wallConfig, EAST, 1);
          break;
     case SOUTH:                                                                              //if the robot is currently facing south
          wallConfig |= 0x01;                                                                      //Just came from north, north wall must be open
          leftWall ? setBit(wallConfig, EAST, 0) : setBit(wallConfig, EAST, 1);
          rightWall ? setBit(wallConfig, WEST, 0) : setBit(wallConfig, WEST, 1);
          frontWall ? setBit(wallConfig, SOUTH, 0) : setBit(wallConfig, SOUTH, 1);
          break;
      case WEST:                                                                              //if the robot is currently facing west
          wallConfig |= 0x02;                                                                      //Just came from east, east wall must be open
          leftWall ? setBit(wallConfig, SOUTH, 0) : setBit(wallConfig, SOUTH, 1);
          rightWall ? setBit(wallConfig, NORTH, 0) : setBit(wallConfig, NORTH, 1);
          frontWall ? setBit(wallConfig, WEST, 0) : setBit(wallConfig, WEST, 1);
          break;
  }
  return wallConfig;
}

//getValueFrom - gets the value of the cell to the north, east, south, or west of a specified cell
// NOTE - overloaded function allowing a reference point other than the mouses current position
//        I do not know if overloaded functions are supported in the arduino environment
//@param facing - the direction to look for the value, north, east, south, or west
//@param x - the x position of the cell to look from
//@param y - the y position of the cell to look from
//@return - the floodfill value of the referenced cell
unsigned char getValueFrom(unsigned char facing, unsigned char x, unsigned char y)
{
  switch (facing)
  {
    case NORTH:
      if(yPosition > 0) return mazeMap[y - 1][xPosition];
      else return 255;
      break;
    case EAST:
      if(xPosition < 15) return mazeMap[y][x + 1];
      else return 255;
      break;
    case SOUTH:
      if(yPosition < 15) return mazeMap[y + 1][x];
      else return 255;
      break;
    case WEST:
      if(xPosition > 0) return mazeMap[y][x - 1];
      else return 255;
      break;
  }
}

unsigned char arbSides[4] = {255, 255, 255, 255};  //the sides array of an arbitrarily selected cell
//fillSides - fills the arbSides array with values corresponding to the adjacent cells of a cell specified by positions x and y
//            if a wall is present, sets the value to 255.
//@param walls - the wall configuration of the specified cell
//@param x - the x position of the specified cell
//@param y - the y position of the specified cell
void fillSides(unsigned char walls, unsigned char x, unsigned char y){
  arbSides[NORTH] = getBit(walls, NORTH) ? getValueFrom(NORTH, x, y) : 255;    //if the cell to the north is open, assign it's value to the NORTH index of arbSides[], else 255
  arbSides[EAST] = getBit(walls, EAST) ? getValueFrom(EAST, x, y) : 255;
  arbSides[SOUTH] = getBit(walls, SOUTH) ? getValueFrom(SOUTH, x, y) : 255;
  arbSides[WEST] = getBit(walls, WEST) ? getValueFrom(WEST, x, y) : 255;
}

//getSidesMin - searches the sides array and returns the miminum value.
//@param sidesAr[] - a size-4 array (presumably a sides array)
//@return - the minimum value of the array
unsigned char getSidesMin(unsigned char sidesAr[])
{
  unsigned char minimum = sidesAr[NORTH];               // keeps track of the minimum value, set to the first element by default
  if (sides[EAST] < minimum) minimum = sidesAr[EAST];      // Checks if values at the remaining positions in the array 
  if (sides[EAST] < minimum) minimum = sidesAr[SOUTH];     // are less than the default minimum, updating the minimum accordingly
  if (sides[EAST] < minimum) minimum = sidesAr[WEST];     
  return minimum;  
}

//cellCheck - checks if cell is 1+ the minimum value of its open neighbors
//@param adjSides[] - a 4-array representing the values of the open cells adjacent to the cell specified by x and y
//@param x - the x position being referenced
//@param y - the y position being referenced
//@return - true if the cell's value is 1+ the minimum value of its open neighbors, else false
//precondition - adjSides[] must reference the sides adjacent to mazeMap[y][x]
boolean cellCheck(unsigned char adjSides[], unsigned char x, unsigned char y){
  unsigned char minimum = getSidesMin(adjSides);
  return (mazeMap[y][x] == (minimum + 1));
}

//getMinPosition - searches an array and returns the index of the miminum value. This position will equal the direction
//                 of the lowest numbered open adjacent cell
//@param sidesAr[] - a size-4 sides array search
//@return - the position of the smallest value
//POTENTIAL PROBLEMS!!! if the min is at more than 1 position, the function will return the direction of the last if statement 
//       THIS IS LIKELY WHAT CAUSED OUR PROLEM WITH THE FIRST FLOOD FILL
unsigned char getMinPosition(unsigned char sidesAr[])
{
  unsigned char minValue = getSidesMin(sides);
  unsigned char minAt = 0;
  if (sidesAr[NORTH] == minValue) minAt = 0;
  if (sidesAr[EAST] == minValue) minAt = 1;
  if (sidesAr[SOUTH] == minValue) minAt = 2;
  if (sidesAr[WEST] == minValue) minAt = 3;

  return minAt;
}

//isNorthWall - determines if there is a north wall from a cell's wall configuration
//@param wallConfig - a cell's wall configuration determined earlier by getWallConfig()
//@return - true if a north wall is present, else false
boolean isNorthWall(unsigned char wallConfig){
  return getBit(~wallConfig, NORTH);
}
boolean isEastWall(unsigned char wallConfig){
  return getBit(~wallConfig, EAST);
}
boolean isSouthWall(unsigned char wallConfig){
  return getBit(~wallConfig, SOUTH);
}
boolean isWestWall(unsigned char wallConfig){
  return getBit(~wallConfig, WEST);
}

//faces the mouse in the ideal position
unsigned char faceIdeal(){
  fillSides(sides, mouseX, mouseY);
  unsigned char ideal = getSidesMin(sides);
  if (sides[currentFacing] == ideal) return;
  else if (sides[shiftClockwise(currentFacing, 1)] == ideal){
    turnRight();
  else if (sides[shiftClockwise(currentFacing, 2)] == ideal){
    turnLeft();
    turnLeft();
  }
  else if (sides[shiftClockwise(currentFacing, 3)] == ideal){
    turnLeft();
  }
}