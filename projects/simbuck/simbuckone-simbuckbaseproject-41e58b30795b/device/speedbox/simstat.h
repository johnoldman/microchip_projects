#ifndef SIMSTAT_H
#define SIMSTAT_H

/** I N C L U D E S **********************************************************/
#include "GenericTypeDefs.h"

/** EXTERNS *****************************************************************/

/** D E F I N I T I O N S ****************************************************/
#define STANDARD        0x00
#define BIDIRECT        0x01
#define SINGLELOBE      0x02
#define MULTILOBE       0x04

#define recordLen       0x0B

/** S T R U C T U R E S ******************************************************/

typedef struct SIG_CONFIG
 {
  BYTE SIGpattern;			// Pattern to use
  BYTE pattern_len;                     // number of bytes in the pattern
  BYTE edgeCtr;				// Number of edges seen
  BYTE CID_edges;			// Number of edges counted for CID period
  BYTE SIGn_active;			// Signals that are now active [set phase]
  BYTE CID_period;			// Number of edges to change state
  BYTE num_Teeth;			// Maximum number of teeth in a revolution
  BYTE num_GapTeeth;                    // Number of 'missing' teeth
  BYTE CID_Start;			// Number of teeth after the 'gap' to start
  BYTE CID_PerHi;			// Number of teeth High
  BYTE CID_PerLo;			// Number of teeth Low
  BYTE CID_teeth[8];                    // number of teeth/period
  BYTE cycle_edges;                     // number of edges this cycle
  BYTE CID_transitions;                 // number of CID transitions this cycle
  BYTE CID_transitions_max;             // maximum number of CID transitions before reset
  BYTE CPS_Type;                        // standard or bi-directional
 } SIG_CONFIG;



/** P U B L I C  P R O T O T Y P E S *****************************************/
//void GetCIDpattern(void);
void InitSIGconfig(void);
void GetSIGpattern(void);
unsigned char checkSIGpatternSW(void);


#endif //SIMSTAT_H
