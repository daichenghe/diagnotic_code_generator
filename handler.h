
#ifndef __HANDLE_H__
#define __HANDLE_H__
#include <stdint.h>

typedef uint8_t bool;

bool PreDriver_ChipOtDiagnoticProcess();

void PreDriver_ChipOtHandler();


bool PreDriver_CbUvDiagnoticProcess();

void PreDriver_CbUvHandler();


bool PreDriver_HighSideBcOvDiagnoticProcess();

void PreDriver_HighSideBcOvHandler();


bool PreDriver_CpOlDiagnoticProcess();

void PreDriver_CpOlHandler();


bool PreDriver_BcUvDiagnoticProcess();

void PreDriver_BcUvHandler();


bool PreDriver_VccOvDiagnoticProcess();

void PreDriver_VccOvHandler();


bool PreDriver_VccUvDiagnoticProcess();

void PreDriver_VccUvHandler();


bool PreDriver_VsOvDiagnoticProcess();

void PreDriver_VsOvHandler();


bool PreDriver_VsUvDiagnoticProcess();

void PreDriver_VsUvHandler();


bool PreDriver_DrainOvDiagnoticProcess();

void PreDriver_DrainOvHandler();


bool PreDriver_DrainUvDiagnoticProcess();

void PreDriver_DrainUvHandler();


bool PreDriver_ClockFailureDiagnoticProcess();

void PreDriver_ClockFailureHandler();


bool PreDriver_VsOlDiagnoticDiagnoticProcess();

void PreDriver_VsOlHandler();


bool PreDriver_MosfetOcDiagnoticProcess();

void PreDriver_MosfetOcHandler();


bool PreDriver_SignatureInvalidDiagnoticProcess();

void PreDriver_SignatureInvalidHandler();


bool PreDriver_ComFailDiagnoticProcess();

void PreDriver_ComFailHandler();


bool PreDriver_AdcSampleFailureDiagnoticProcess();

void PreDriver_AdcSampleFailureHandler();


#endif
