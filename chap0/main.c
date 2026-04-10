#include <libepc.h>

int main(int argc, char *argv[])
{
   ClearScreen(0x07);
   SetCursorPosition(0, 0);
   
   PutString(">>>>>>> VT24 Anton Antpe029  <<<<<<<\r\n");
   
   return 0;
}
