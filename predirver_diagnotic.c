  
#include <stdio.h>  
#include <stdint.h> // ����stdint.h��ʹ��uint8_t����  
#include "detect.h"
#include "handler.h"

#ifndef TRUE
#define TRUE        0
#define FALSE       1  
#endif
 
#define NUM_DIAGNOSTICS 2  
#define MAX_DIAG_ID_LENGTH 2  
#define MAX_SUBITEM_ID_LENGTH 1  
#define MAX_SUBITEMS_PER_DIAG 16  
  
// ����ָ�����Ͷ��壬��Ҫ��C������ʵ����Щ����  
typedef bool (*detectProcess)();  
typedef void (*handleProcess)();  
  
// ����ṹ��  
typedef struct Subitem {  
    char id;  
    uint8_t DTI; 
    uint8_t tick;
    uint8_t priority;
    uint8_t fault_detection_count_threshold;   
    uint8_t fault_count;
    bool fault_status;
    detectProcess detectFunc; 
    handleProcess handleFunc; 
} Subitem;  
  
typedef struct {  
    int id; 
    uint16_t number;        
    Subitem** subitems;  
} DiagnosticGroup;  
  


Subitem ChipOt = 
{
    .id = 0,  
    .DTI = 5,  
    .priority = 0,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = PreDriver_ChipOtDiagnoticProcess,
    .handleFunc = PreDriver_ChipOtHandler, 
};

Subitem CbUv = 
{
    .id = 1,  
    .DTI = 5,  
    .priority = 2,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = PreDriver_CbUvDiagnoticProcess,
    .handleFunc = PreDriver_CbUvHandler, 
};

Subitem HighBcOv = 
{
    .id = 2,  
    .DTI = 5,  
    .priority = 2,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = PreDriver_HighSideBcOvDiagnoticProcess,
    .handleFunc = PreDriver_HighSideBcOvHandler, 
};

Subitem CpOl = 
{
    .id = 3,  
    .DTI = 5,  
    .priority = 0,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = PreDriver_CpOlDiagnoticProcess,
    .handleFunc = PreDriver_CpOlHandler, 
};

Subitem BcUv = 
{
    .id = 4,  
    .DTI = 5,  
    .priority = 0,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = PreDriver_BcUvDiagnoticProcess,
    .handleFunc = PreDriver_BcUvHandler, 
};

Subitem VccOv = 
{
    .id = 5,  
    .DTI = 5,  
    .priority = 0,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = PreDriver_VccOvDiagnoticProcess,
    .handleFunc = PreDriver_VccOvHandler, 
};

Subitem VccUv = 
{
    .id = 6,  
    .DTI = 5,  
    .priority = 0,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = PreDriver_VccUvDiagnoticProcess,
    .handleFunc = PreDriver_VccUvHandler, 
};

Subitem VsOv = 
{
    .id = 7,  
    .DTI = 5,  
    .priority = 0,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = PreDriver_VsOvDiagnoticProcess,
    .handleFunc = PreDriver_VsOvHandler, 
};

Subitem VsUv = 
{
    .id = 8,  
    .DTI = 5,  
    .priority = 0,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = PreDriver_VsUvDiagnoticProcess,
    .handleFunc = PreDriver_VsUvHandler, 
};

Subitem DrainOv = 
{
    .id = 9,  
    .DTI = 5,  
    .priority = 0,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = PreDriver_DrainOvDiagnoticProcess,
    .handleFunc = PreDriver_DrainOvHandler, 
};

Subitem DrainUv = 
{
    .id = 10,  
    .DTI = 5,  
    .priority = 0,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = PreDriver_DrainUvDiagnoticProcess,
    .handleFunc = PreDriver_DrainUvHandler, 
};

Subitem ClockFailure = 
{
    .id = 11,  
    .DTI = 5,  
    .priority = 2,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = PreDriver_ClockFailureDiagnoticProcess,
    .handleFunc = PreDriver_ClockFailureHandler, 
};

Subitem VsOl = 
{
    .id = 12,  
    .DTI = 5,  
    .priority = 2,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = PreDriver_VsOlDiagnoticDiagnoticProcess,
    .handleFunc = PreDriver_VsOlHandler, 
};

Subitem MosfetOc = 
{
    .id = 13,  
    .DTI = 5,  
    .priority = 2,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = PreDriver_MosfetOcDiagnoticProcess,
    .handleFunc = PreDriver_MosfetOcHandler, 
};

Subitem SignatureInvalid = 
{
    .id = 14,  
    .DTI = 5,  
    .priority = 2,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = PreDriver_SignatureInvalidDiagnoticProcess,
    .handleFunc = PreDriver_SignatureInvalidHandler, 
};

Subitem ComFail = 
{
    .id = 15,  
    .DTI = 5,  
    .priority = 2,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = PreDriver_ComFailDiagnoticProcess,
    .handleFunc = PreDriver_ComFailHandler, 
};

Subitem AdcSampleFailure = 
{
    .id = 0,  
    .DTI = 5,  
    .priority = 2,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = PreDriver_AdcSampleFailureDiagnoticProcess,
    .handleFunc = PreDriver_AdcSampleFailureHandler, 
};
Subitem* subitemsCDD_PreDriverDiagnoticGroup[16] = {&ChipOt, &CbUv, &HighBcOv, &CpOl, &BcUv, &VccOv, &VccUv, &VsOv, &VsUv, &DrainOv, &DrainUv, &ClockFailure, &VsOl, &MosfetOc, &SignatureInvalid, &ComFail};
Subitem* subitemsMCAL_AdcDiagnoticGroup[1] = {&AdcSampleFailure};

DiagnosticGroup CDD_PreDriverDiagnoticGroup = {
    .id = 0,
    .number = 16,
    .subitems = subitemsCDD_PreDriverDiagnoticGroup ,
};

DiagnosticGroup MCAL_AdcDiagnoticGroup = {
    .id = 1,
    .number = 1,
    .subitems = subitemsMCAL_AdcDiagnoticGroup ,
};
DiagnosticGroup*   diagnostics[2] = {&CDD_PreDriverDiagnoticGroup, &MCAL_AdcDiagnoticGroup };  
  
// ��ʱ��������ĺ���  
void check_diagnostics() {
    uint8_t diagnoticPeriod = 5;
    for (int i = 0; i < NUM_DIAGNOSTICS; i++) {
        for (int j = 0; j < diagnostics[i]->number; j++) {
            diagnostics[i]->subitems[j]->tick+= diagnoticPeriod;
            bool detection_result = FALSE;
            // ���ü�⺯��  
            if(diagnostics[i]->subitems[j]->tick >= diagnostics[i]->subitems[j]->DTI)
            {
                detection_result = diagnostics[i]->subitems[j]->detectFunc();  
                diagnostics[i]->subitems[j]->tick = 0;
            }
            // ����fault_detection_count��fault_status  
            if (detection_result) {
                diagnostics[i]->subitems[j]->fault_count++;  
                if (diagnostics[i]->subitems[j]->fault_count >= diagnostics[i]->subitems[j]->fault_detection_count_threshold) {
                    diagnostics[i]->subitems[j]->fault_status = TRUE;  
                    // ���ô�����  
                    diagnostics[i]->subitems[j]->handleFunc();  
                }
            } else {
                diagnostics[i]->subitems[j]->fault_status = FALSE;  
                diagnostics[i]->subitems[j]->fault_count = 0; // ������Ҫ���ü�����ȡ���ھ�������  
            }
        } 
    }  
}  

// ������  
int main() {
    // ��ʼ��detectFunc��handleFunc�ֶΣ�������ռλ������ʵ�ʺ�����  
    // ... (ΪdetectFunc��handleFunc�ֶ�����ʵ��ĳ�ʼ������)  
      
    // ģ�ⶨʱ����ѭ������������  
    while (1) {  
        check_diagnostics();  
        // �ȴ�DTIʱ��������������  
        // sleep(DTI); // ������sleep�������ã�ʵ��ʵ��ȡ����ƽ̨  
    } 
      
    return 0;  
}
