void TheFlood()
{
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
         
