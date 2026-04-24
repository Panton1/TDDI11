#include <libepc.h>

void llmultiply(unsigned long long int l1,unsigned long long int l2, unsigned char *result);

///

 unsigned long int m32h(unsigned  long int A_4B,unsigned long  int B_4B){
 unsigned long int le=0xFFFF;
 
 unsigned long int AHigh=A_4B>>16;
 unsigned long int ALow=A_4B & le;
 unsigned long int BHigh=B_4B>>16;
 unsigned long int BLow=B_4B & le;

 unsigned  long int AL_BL=ALow*BLow; //i
 unsigned  long int AL_BH=ALow*BHigh;//i
 unsigned  long int AH_BL=AHigh*BLow;//i
 unsigned  long int AH_BH=AHigh*BHigh;//i

 unsigned short int AL_BL_H=AL_BL>>16;

 unsigned short int AL_BH_L=AL_BH;
 unsigned short int AL_BH_H=AL_BH>>16;

 unsigned short int AH_BL_L=AH_BL;
 unsigned short int AH_BL_H=AH_BL>>16;

 unsigned short int AH_BH_L=AH_BH;
 unsigned short int AH_BH_H=AH_BH>>16;


 unsigned long  int S1=AL_BL_H+AL_BH_L+AH_BL_L;

 unsigned long  int S2=AL_BH_H+AH_BL_H+AH_BH_L+(S1>>16);

 unsigned long  int S3=AH_BH_H+(S2>>16);

 unsigned long  int high32=(S2 & le)+(S3<<16);
 
 return high32;
};
///

void cllmultiply(unsigned long long int a,unsigned long long int b, unsigned char *result){

 unsigned long int le=0x00000000FFFFFFFF;
 unsigned short int ca=0;
 
 unsigned long int AHigh=a>>32;
 unsigned long int ALow=a & le;
 unsigned long int BHigh=b>>32;
 unsigned long int BLow=b & le;

 unsigned  long int AL_BL=ALow*BLow; //i
 unsigned long  int AL_BH=ALow*BHigh;//i
 unsigned long int AH_BL=AHigh*BLow;//i
unsigned  long int AH_BH=AHigh*BHigh;//i


//////  s1
 if ((m32h(ALow,BLow)+(AL_BH & le))<m32h(ALow,BLow)){
   ca=ca+1;
 }
 unsigned long   int S1=m32h(ALow,BLow)+(AL_BH & le);

  if ((S1+(AH_BL & le))<S1){
   ca=ca+1;
 }
 
 S1=S1+(AH_BL & le);

 unsigned long  int S2=ca;
 ca=0;

 /////////////////////////////////////s2
  if ((m32h(ALow,BHigh)+m32h(AHigh,BLow))<m32h(ALow,BHigh)){
   ca=ca+1;
 }


  S2=S2+m32h(ALow,BHigh)+m32h(AHigh,BLow);

  if ((S2+(AH_BH & le))<S2){
   ca=ca+1;
 }
  
  S2=S2+(AH_BH & le) ;

  /// s3
 unsigned  long int S3=m32h(AHigh,BHigh)+ca;
 
((unsigned long int*)result)[0]=AL_BL;
((unsigned long int*)result)[1]=S1;
((unsigned long int*)result)[2]=S2;
((unsigned long int*)result)[3]=S3;

 
};






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
  QWORD64 count_ms_before= CPU_Clock_Cycles();

  
  unsigned char result[16];
  int i;
  
  ClearScreen(0x07);
   SetCursorPosition(0, 0);





  
for (int x = 0; x < 1; ++x)
  {
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
    
    cllmultiply(cases[i].a, cases[i].b, result);
    
    PutString("Result ");
    PutUnsignedLongLong((unsigned long long int*)&result[8]);
    PutUnsignedLongLong((unsigned long long int*)&result[0]); 
    PutString("\r\n");
    
     PutString("\r\n");
  }
  }
  QWORD64 count_ms_after= CPU_Clock_Cycles();
  QWORD64 difftime=count_ms_after-count_ms_before;
  unsigned long long int res_time=(unsigned long long int)difftime;
  PutUnsignedLongLong((res_time/100000));
  return 0;
}
