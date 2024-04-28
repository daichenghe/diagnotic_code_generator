
#ifndef __detect_H__
#define __detect_H__
#include <stdint.h>

typedef uint8_t bool;

bool PreDriver_ChipOtDiagnoticProcess();


bool PreDriver_CbUvDiagnoticProcess();


bool PreDriver_HighSideBcOvDiagnoticProcess();


bool PreDriver_CpOlDiagnoticProcess();


bool PreDriver_BcUvDiagnoticProcess();


bool PreDriver_VccOvDiagnoticProcess();


bool PreDriver_VccUvDiagnoticProcess();


bool PreDriver_VsOvDiagnoticProcess();


bool PreDriver_VsUvDiagnoticProcess();


bool PreDriver_DrainOvDiagnoticProcess();


bool PreDriver_DrainUvDiagnoticProcess();


bool PreDriver_ClockFailureDiagnoticProcess();


bool PreDriver_VsOlDiagnoticDiagnoticProcess();


bool PreDriver_MosfetOcDiagnoticProcess();


bool PreDriver_SignatureInvalidDiagnoticProcess();


bool PreDriver_ComFailDiagnoticProcess();


bool PreDriver_AdcSampleFailureDiagnoticProcess();


#endif
