
#ifndef __handler_H__
#define __handler_H__
#include <stdint.h>

typedef uint8_t bool;

void PreDriver_ChipOtHandler();


void PreDriver_CbUvHandler();


void PreDriver_HighSideBcOvHandler();


void PreDriver_CpOlHandler();


void PreDriver_BcUvHandler();


void PreDriver_VccOvHandler();


void PreDriver_VccUvHandler();


void PreDriver_VsOvHandler();


void PreDriver_VsUvHandler();


void PreDriver_DrainOvHandler();


void PreDriver_DrainUvHandler();


void PreDriver_ClockFailureHandler();


void PreDriver_VsOlHandler();


void PreDriver_MosfetOcHandler();


void PreDriver_SignatureInvalidHandler();


void PreDriver_ComFailHandler();


void PreDriver_AdcSampleFailureHandler();


#endif
