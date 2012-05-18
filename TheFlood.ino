unsigned char STACK_CAPACITY = 50; //declare outside of the array itself
void TheFlood()
{
   walls[mouseY][mouseX] = getWallConfig(mouseX, mouseY);
   fillSides(sides, mouseX, mouseY);
   if (checkCell(sides, mouseX, mouseY))
   {
     return;
   }
   else
   {
     unsigned char stackSize = 0;
     unsigned char xPosition = mouseX;
     unsigned char yPosition = mouseY;
     masterPush(sides, xPosition, yPosition);
     do {
       if (stackSize == STACK_CAPACITY)
       {
         //increase capacity
       }
       uchar cellPos = pop();
       xPosition = getX(cellPos);
       yPosition = getY(cellPos);
       fillSides(sides, xPosition, yPosition);
       if (!checkCell(sides, xPosition, yPosition))
       {
          mazeMap[yPosition][xPosition] = ++(getSidesMin(sides));
          masterPush(sides, xPosition, yPosition);
       }
       else if (stackSize >= 1)
       {
          xPosition = getX(stack[stackSize - 1]);
          yPosition = getX(stack[stackSize - 1]);
       }
     }
     while (stackSize > 0);
}