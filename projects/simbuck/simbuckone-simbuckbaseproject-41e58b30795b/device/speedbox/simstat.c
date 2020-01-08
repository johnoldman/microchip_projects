/** I N C L U D E S **********************************************************/
#include  <p18cxxx.h>
#include "simbuck_cfg.h"
#include "HardwareProfile.h"
#include "GenericTypeDefs.h"
#include "simstat.h"
#include "system/eeprom/eeprom.h"


/** V A R I A B L E S ********************************************************/
#pragma udata
BYTE SIGpattern;
BYTE patternStart;

SIG_CONFIG SIGconfig;
extern unsigned char INPacket[64];	//User application buffer for sending IN packets to the host


/** P R O T O T Y P E S ********************************************************/


/** D E C L A R A T I O N S **************************************************/
#pragma code

void GetSIGpattern(void)
{
  int i;
  
  INTCONbits.GIE = 0;	   		

  SIGconfig.SIGpattern = (~PORTD)&0x0F;

  patternStart = (SIGconfig.SIGpattern)*recordLen;

  if(ReadFromEEPROM(patternStart) == 0xFF)
  {
     InitSIGconfig();
  }
  else
    {
      SIGconfig.num_Teeth=ReadFromEEPROM(patternStart);
      SIGconfig.num_GapTeeth=ReadFromEEPROM(patternStart+1);
      SIGconfig.CID_Start=ReadFromEEPROM(patternStart+2);
      SIGconfig.CID_PerHi=ReadFromEEPROM(patternStart+3);
      SIGconfig.CID_PerLo=ReadFromEEPROM(patternStart+4);

      for(i=0;i<=7;i++)
        {
         // test code
         SIGconfig.CID_teeth[i]=ReadFromEEPROM((patternStart+3) + i);

         if(SIGconfig.CID_teeth[i] != 0)
          {
           SIGconfig.CID_transitions_max++;
          }
        }

      SIGconfig.CID_period = SIGconfig.CID_teeth[0];
      SIGconfig.edgeCtr = 0;
      SIGconfig.CID_edges = 0;
      SIGconfig.SIGn_active = 0;
  
      SIGconfig.CID_transitions = 0;
      
      //SIGconfig.CPS_Type = STANDARD;
      SIGconfig.CPS_Type = MULTILOBE;
      SIGconfig.pattern_len = 11;
      }
  
    INTCONbits.GIE = 1;

}

unsigned char checkSIGpatternSW(void)
{
   SIGpattern = (~PORTD)&0x0F; 
   return SIGpattern;
}

void InitSIGconfig(void)
{
  int i;

  SIGconfig.SIGpattern = checkSIGpatternSW();

  patternStart = -1;

  SIGconfig.num_Teeth=100;
  SIGconfig.num_GapTeeth=3;
  SIGconfig.CID_Start=2;
  SIGconfig.CID_PerHi=25;
   SIGconfig.CID_teeth[0]=25;
  SIGconfig.CID_PerLo=15;
   SIGconfig.CID_teeth[1]=15;

   for(i=2;i<=7;i++)
     {
      // test code
      SIGconfig.CID_teeth[i]=ReadFromEEPROM((patternStart+3) + i);
     }

  SIGconfig.edgeCtr=0;
  SIGconfig.CID_edges=0;
  SIGconfig.cycle_edges=0;
  SIGconfig.SIGn_active=0;

  SIGconfig.CID_transitions=0;
  SIGconfig.CID_transitions_max=0;

  SIGconfig.CPS_Type = BIDIRECT;
  SIGconfig.pattern_len=0;
  
}

/** EOF simstat.c ***************************************************************/
