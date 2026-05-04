#include <os_cpu.h>
#include <os_cfg.h>
#include <ucos_ii.h> /* os_c??.h must be included before ! */
#include <libepc.h>

#include "inbound.h"
#include "elapsed.h"
#include "serial.h"

void ReceivePackets(void)
{
  SerialInit() ;
  
  for (;;)
  {
    int type, byte, bytes ;
    BYTE8 *bfr ;
    
    if (SerialGet() != 0xFF)
      continue ;
    
    switch (type = SerialGet())
    {
      default:
        continue ;
      case 1:
      case 2:
        break ;
    }
    
    bytes = SerialGet();
    bfr = (BYTE8 *) malloc(bytes) ;
    if (!bfr)
    {
      for (;;)
        ;
    }
    
    for (byte = 0; byte < bytes; byte++)
    {
      bfr[byte] = SerialGet() ;
    }
    switch (type)
    {
      case 1:
        PostText(bfr) ;
        break ;
      case 2:
        PostTime(bfr) ;
        break ;
    }
  }
}





void SendPacket(int type, BYTE8 *bfr, int byte_C)
{ int loop;

   OSSemCreate(1); //PERFECT?
  
   OSSemPend(OSSemCreate(1), 0 , *err);

  ///HMMMMMMMM 
  /// OS_EVENT *OSSemCreate(int count);,CREATE LOCK
  /// OSSemPend(OS_EVENT *semaphore, int timeout, BYTE8 *err);, LOCK
  /// OSSemPost(OS_EVENT *semaphore);, UNLOCK???
    SerialPut(0xff); 
    SerialPut(type);
    SerialPut(byte_C);
    
for (loop = 0; loop < byte_C;loop++) {
    SerialPut(bfr[loop]);
 }

  
  /*
   * Your code here !
   */

 OSSemPost(OSSemCreate(1));
}
