  
#include <stdio.h>  
#include <stdint.h> // 引入stdint.h以使用uint8_t类型  
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
  
// 函数指针类型定义，需要在C代码中实现这些函数  
typedef bool (*detectProcess)();  
typedef void (*handleProcess)();  
  
// 定义结构体  
typedef struct Subitem {  
    char id;  
    uint8_t DTI; 
    uint8_t tick;
    uint8_t priority;
    uint8_t fault_detection_count_threshold;   
    uint8_t fault_count;
    uint8_t fault_recover_count_threshold;   
    uint8_t recover_count;    
    bool fault_status;
    bool reset_enable;
    detectProcess detectFunc; 
    handleProcess handleFunc; 
    handleProcess resetFunc;
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
    .fault_recover_count_threshold = 2,
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .reset_enable = TRUE,
    .detectFunc = PreDriver_ChipOtDiagnoticProcess,
    .handleFunc = PreDriver_ChipOtHandler, 
    .resetFunc = PreDriver_ChipOtResetHandler,
};

Subitem CbUv = 
{
    .id = 1,  
    .DTI = 5,  
    .priority = 2,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    .fault_recover_count_threshold = 2,
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .reset_enable = TRUE,
    .detectFunc = PreDriver_CbUvDiagnoticProcess,
    .handleFunc = PreDriver_CbUvHandler, 
    .resetFunc = PreDriver_CbUvResetHandler,
};

Subitem HighBcOv = 
{
    .id = 2,  
    .DTI = 5,  
    .priority = 2,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    .fault_recover_count_threshold = 2,
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .reset_enable = TRUE,
    .detectFunc = PreDriver_HighSideBcOvDiagnoticProcess,
    .handleFunc = PreDriver_HighSideBcOvHandler, 
    .resetFunc = PreDriver_HighSideBcOvResetHandler,
};

Subitem CpOl = 
{
    .id = 3,  
    .DTI = 5,  
    .priority = 0,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    .fault_recover_count_threshold = 2,
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .reset_enable = TRUE,
    .detectFunc = PreDriver_CpOlDiagnoticProcess,
    .handleFunc = PreDriver_CpOlHandler, 
    .resetFunc = PreDriver_CpOlResetHandler,
};

Subitem BcUv = 
{
    .id = 4,  
    .DTI = 5,  
    .priority = 0,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    .fault_recover_count_threshold = 2,
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .reset_enable = TRUE,
    .detectFunc = PreDriver_BcUvDiagnoticProcess,
    .handleFunc = PreDriver_BcUvHandler, 
    .resetFunc = PreDriver_BcUvResetHandler,
};

Subitem VccOv = 
{
    .id = 5,  
    .DTI = 5,  
    .priority = 0,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    .fault_recover_count_threshold = 2,
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .reset_enable = TRUE,
    .detectFunc = PreDriver_VccOvDiagnoticProcess,
    .handleFunc = PreDriver_VccOvHandler, 
    .resetFunc = PreDriver_VccOvResetHandler,
};

Subitem VccUv = 
{
    .id = 6,  
    .DTI = 5,  
    .priority = 0,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    .fault_recover_count_threshold = 2,
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .reset_enable = TRUE,
    .detectFunc = PreDriver_VccUvDiagnoticProcess,
    .handleFunc = PreDriver_VccUvHandler, 
    .resetFunc = PreDriver_VccUvResetHandler,
};

Subitem VsOv = 
{
    .id = 7,  
    .DTI = 5,  
    .priority = 0,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    .fault_recover_count_threshold = 2,
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .reset_enable = TRUE,
    .detectFunc = PreDriver_VsOvDiagnoticProcess,
    .handleFunc = PreDriver_VsOvHandler, 
    .resetFunc = PreDriver_VsOvResetHandler,
};

Subitem VsUv = 
{
    .id = 8,  
    .DTI = 5,  
    .priority = 0,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    .fault_recover_count_threshold = 2,
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .reset_enable = TRUE,
    .detectFunc = PreDriver_VsUvDiagnoticProcess,
    .handleFunc = PreDriver_VsUvHandler, 
    .resetFunc = PreDriver_VsUvResetHandler,
};

Subitem DrainOv = 
{
    .id = 9,  
    .DTI = 5,  
    .priority = 0,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    .fault_recover_count_threshold = 2,
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .reset_enable = TRUE,
    .detectFunc = PreDriver_DrainOvDiagnoticProcess,
    .handleFunc = PreDriver_DrainOvHandler, 
    .resetFunc = PreDriver_DrainOvResetHandler,
};

Subitem DrainUv = 
{
    .id = 10,  
    .DTI = 5,  
    .priority = 0,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    .fault_recover_count_threshold = 2,
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .reset_enable = TRUE,
    .detectFunc = PreDriver_DrainUvDiagnoticProcess,
    .handleFunc = PreDriver_DrainUvHandler, 
    .resetFunc = PreDriver_DrainUvResetHandler,
};

Subitem ClockFailure = 
{
    .id = 11,  
    .DTI = 5,  
    .priority = 2,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    .fault_recover_count_threshold = 2,
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .reset_enable = TRUE,
    .detectFunc = PreDriver_ClockFailureDiagnoticProcess,
    .handleFunc = PreDriver_ClockFailureHandler, 
    .resetFunc = PreDriver_ClockFailureResetHandler,
};

Subitem VsOl = 
{
    .id = 12,  
    .DTI = 5,  
    .priority = 2,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    .fault_recover_count_threshold = 2,
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .reset_enable = TRUE,
    .detectFunc = PreDriver_VsOlDiagnoticDiagnoticProcess,
    .handleFunc = PreDriver_VsOlHandler, 
    .resetFunc = PreDriver_VsOlResetHandler,
};

Subitem MosfetOc = 
{
    .id = 13,  
    .DTI = 5,  
    .priority = 2,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    .fault_recover_count_threshold = 2,
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .reset_enable = TRUE,
    .detectFunc = PreDriver_MosfetOcDiagnoticProcess,
    .handleFunc = PreDriver_MosfetOcHandler, 
    .resetFunc = PreDriver_MosfetOcResetHandler,
};

Subitem SignatureInvalid = 
{
    .id = 14,  
    .DTI = 5,  
    .priority = 2,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    .fault_recover_count_threshold = 2,
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .reset_enable = TRUE,
    .detectFunc = PreDriver_SignatureInvalidDiagnoticProcess,
    .handleFunc = PreDriver_SignatureInvalidHandler, 
    .resetFunc = PreDriver_SignatureInvalidResetHandler,
};

Subitem ComFail = 
{
    .id = 15,  
    .DTI = 5,  
    .priority = 2,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    .fault_recover_count_threshold = 2,
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .reset_enable = TRUE,
    .detectFunc = PreDriver_ComFailDiagnoticProcess,
    .handleFunc = PreDriver_ComFailHandler, 
    .resetFunc = PreDriver_ComFailResetHandler,
};

Subitem AdcSampleFailure = 
{
    .id = 0,  
    .DTI = 5,  
    .priority = 2,
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    .fault_recover_count_threshold = 2,
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .reset_enable = TRUE,
    .detectFunc = PreDriver_AdcSampleFailureDiagnoticProcess,
    .handleFunc = PreDriver_AdcSampleFailureHandler, 
    .resetFunc = PreDriver_AdcSampleFailureResetHandler,
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
  
// 定时检查诊断项的函数  
void check_diagnostics() {
    uint8_t diagnoticPeriod = 5;
    for (int i = 0; i < NUM_DIAGNOSTICS; i++) {
        for (int j = 0; j < diagnostics[i]->number; j++) {
            diagnostics[i]->subitems[j]->tick+= diagnoticPeriod;
            bool detection_result = FALSE;
            // 调用检测函数  
            if(diagnostics[i]->subitems[j]->tick >= diagnostics[i]->subitems[j]->DTI)
            {
                detection_result = diagnostics[i]->subitems[j]->detectFunc();  
                diagnostics[i]->subitems[j]->tick = 0;
            }
            // 更新fault_detection_count和fault_status  
            if (detection_result) {
                if(diagnostics[i]->subitems[j]->fault_status = FALSE)
                {
                    diagnostics[i]->subitems[j]->fault_count++;  
                    if (diagnostics[i]->subitems[j]->fault_count >= diagnostics[i]->subitems[j]->fault_detection_count_threshold) {
                        diagnostics[i]->subitems[j]->fault_status = TRUE;  
                        // 调用处理函数  
                        diagnostics[i]->subitems[j]->handleFunc();  
                        diagnostics[i]->subitems[j]->fault_count = 0;  
                    }
                }
            } else {
                if(diagnostics[i]->subitems[j]->fault_status = TRUE)
                {
                    diagnostics[i]->subitems[j]->recover_count++;  
                    if (diagnostics[i]->subitems[j]->recover_count >= diagnostics[i]->subitems[j]->fault_recover_count_threshold) {
                        diagnostics[i]->subitems[j]->fault_status = FALSE;  
                        // 调用恢复函数 
                        diagnostics[i]->subitems[j]->resetFunc(); 
                        diagnostics[i]->subitems[j]->recover_count = 0; 
                    }
                }
            }
        } 
    }  
}  

// 主函数  
int main() {
    // 初始化detectFunc和handleFunc字段（这里用占位符代替实际函数）  
    // ... (为detectFunc和handleFunc字段添加适当的初始化代码)  
      
    // 模拟定时器或循环来检查诊断项  
    while (1) {  
        check_diagnostics();  
        // 等待DTI时间或进行其他操作  
        // sleep(DTI); // 假设有sleep函数可用，实际实现取决于平台  
    } 
      
    return 0;  
}
