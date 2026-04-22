#include <libepc.h>

//void llllmultiply(unsigned long long int l1,unsigned long long int l2, unsigned char *result);

void llmultiply(unsigned long long int l1,
		unsigned long long int l2,
		unsigned char *result);

void cmultiply(unsigned long long int a, unsigned long long int b, unsigned char *result){
  unsigned long long int maskLow4B=0x00000000FFFFFFFF;
  unsigned long long int maskHigh4B=0xFFFFFFFF00000000;
    
  /* unsigned long int ALow=((a<<32)>>32); */
  /* unsigned long int AHigh=(a>>32); */
  /* unsigned long int BLow=((b<<32)>>32); */
  /* unsigned long int BHigh=(b>>32); */

  unsigned long long int ALow=a & maskLow4B;
  unsigned long long int AHigh=a & maskHigh4B;
  unsigned long long int BLow=b & maskLow4B;
  unsigned long long int BHigh=b & maskHigh4B;
  // -------------///

  unsigned long long int AL_BL=ALow*BLow;
  unsigned long long int AL_BH=ALow*BHigh;
  unsigned long long int AH_BL=AHigh*BLow;
  // unsigned long long int AH_BH=AHigh*BHigh;
  
   

  
  unsigned long  long int AL_BLLOW=(AL_BL & maskLow4B);
  unsigned long long int AL_BHHIGH=(AL_BH & maskHigh4B);
  unsigned long long int AL_BHLOW=(AL_BH & maskHigh4B);

  unsigned long long int AH_BLLOW=(AH_BL & maskLow4B);
  unsigned long long int AL_BLHIGH=(AL_BL & maskHigh4B);
  


			   
  unsigned long int test1 =0xABABABAB;
  // unsigned long int test2 =0xFEFEFEFE;
    
  // result[0]=test1;
  //  result[1]=test2;
  unsigned long long int r2 = AL_BLHIGH+AL_BHLOW+AH_BLLOW;
  
  
  *(unsigned long int*)&result[0]=(unsigned long int)(AL_BLLOW);
  // *(unsigned long int*)&result[1]=r2;
  *(unsigned long long int*)&result[4]=test1;

  
  // *(unsigned long long int*)&result[0]=test1;
 

 
   
}

struct test_case {
  unsigned long long int a;
  unsigned long long int b;
  unsigned long long int rh;
  unsigned long long int rl;
};

struct test_case cases[6] = {

  { 0x0000111122223333ULL, 0x0000555566667777ULL,
    0x0000000005B061D9ULL, 0x58BF0ECA7C0481B5ULL },

  { 0x3456FEDCAAAA1000ULL, 0xEDBA00112233FF01ULL,
    0x309A912AF7188C57ULL, 0xE62072DD409A1000ULL },

  { 0xFFFFEEEEDDDDCCCCULL, 0xBBBBAAAA99998888ULL,
    0xBBBB9E2692C5DDDCULL, 0xC28F7531048D2C60ULL },

  { 0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL,
    0xFFFFFFFFFFFFFFFEULL, 0x0000000000000001ULL },
  
  { 0x00000001FFFFFFFFULL, 0x00000001FFFFFFFFULL,
    0x0000000000000003ULL, 0xFFFFFFFC00000001ULL },

  { 0xFFFEFFFFFFFFFFFFULL, 0xFFFF0001FFFFFFFFULL,
    0xFFFE0002FFFDFFFEULL, 0x0001FFFE00000001ULL }
};

void PutUnsignedLongLong(unsigned long long int* ulli)
{
  unsigned long int* uli = (unsigned long int*)ulli; 
  PutUnsigned(uli[1], 16, 8);
  PutUnsigned(uli[0], 16, 8); 
}

int main(int argc, char *argv[])
{
  unsigned char result[16];
  int i;
  
  ClearScreen(0x07);
  SetCursorPosition(0, 0);

  for (i = 0; i < 6; ++i)
    {
      PutString("Test : ");
      PutUnsignedLongLong(&cases[i].a);
      PutString(" * ");
      PutUnsignedLongLong(&cases[i].b); 
      PutString("\r\n");
   
      PutString("    == ");
      PutUnsignedLongLong(&cases[i].rh);
      PutUnsignedLongLong(&cases[i].rl);
      PutString("\r\n");
    
      cmultiply(cases[i].a, cases[i].b, result);
    
      PutString("Result ");
      PutUnsignedLongLong((unsigned long long int*)&result[8]);
      PutUnsignedLongLong((unsigned long long int*)&result[0]); 
      PutString("\r\n");
    
      PutString("\r\n");
    }

  return 0;
}



