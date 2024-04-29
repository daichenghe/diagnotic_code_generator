
#ifndef __handler_H__
#define __handler_H__
#include <stdint.h>

typedef uint8_t bool;

void PreDriver_ChipOtHandler();


void PreDriver_ChipOtResetHandler();


void PreDriver_CbUvHandler();


void PreDriver_CbUvResetHandler();


void PreDriver_HighSideBcOvHandler();


void PreDriver_HighSideBcOvResetHandler();


void PreDriver_CpOlHandler();


void PreDriver_CpOlResetHandler();


void PreDriver_BcUvHandler();


void PreDriver_BcUvResetHandler();


void PreDriver_VccOvHandler();


void PreDriver_VccOvResetHandler();


void PreDriver_VccUvHandler();


void PreDriver_VccUvResetHandler();


void PreDriver_VsOvHandler();


void PreDriver_VsOvResetHandler();


void PreDriver_VsUvHandler();


void PreDriver_VsUvResetHandler();


void PreDriver_DrainOvHandler();


void PreDriver_DrainOvResetHandler();


void PreDriver_DrainUvHandler();


void PreDriver_DrainUvResetHandler();


void PreDriver_ClockFailureHandler();


void PreDriver_ClockFailureResetHandler();


void PreDriver_VsOlHandler();


void PreDriver_VsOlResetHandler();


void PreDriver_MosfetOcHandler();


void PreDriver_MosfetOcResetHandler();


void PreDriver_SignatureInvalidHandler();


void PreDriver_SignatureInvalidResetHandler();


void PreDriver_ComFailHandler();


void PreDriver_ComFailResetHandler();


void PreDriver_AdcSampleFailureHandler();


void PreDriver_AdcSampleFailureResetHandler();


#endif
