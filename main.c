  
#include <stdio.h>  
#include <stdint.h> // ����stdint.h��ʹ��uint8_t����  
#include "handler.h"
  
#ifndef TRUE
#define TRUE        0
#define FALSE       1  
#endif
 
#define NUM_DIAGNOSTICS 2  
#define MAX_DIAG_ID_LENGTH 2  
#define MAX_SUBITEM_ID_LENGTH 1  
#define MAX_SUBITEMS_PER_DIAG 3  
  
// ����ָ�����Ͷ��壬��Ҫ��C������ʵ����Щ����  
typedef bool (*detectProcess)();  
typedef void (*handleProcess)();  
  
// ����ṹ��  
typedef struct Subitem {  
    char id;  
    uint8_t DTI; 
    uint8_t tick;    
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
  


Subitem radiator = 
{
    .id = 0,  
    .DTI = 5,  
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = Radiator_detect_process,
    .handleFunc = Radiator_fault_handle, 
};

Subitem cool = 
{
    .id = 1,  
    .DTI = 10,  
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = Cooling_detect_process,
    .handleFunc = Cooling_fault_handle, 
};

Subitem brake = 
{
    .id = 0,  
    .DTI = 15,  
    .tick = 0,
    .fault_detection_count_threshold = 2,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = Brake_detect_process,
    .handleFunc = Brake_fault_handle, 
};

Subitem oc = 
{
    .id = 1,  
    .DTI = 20,  
    .tick = 0,
    .fault_detection_count_threshold = 5,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = Oc_detect_process,
    .handleFunc = Oc_fault_handle, 
};

Subitem ov = 
{
    .id = 2,  
    .DTI = 25,  
    .tick = 0,
    .fault_detection_count_threshold = 0,  
    // .detectFunc��.handleFunc��Ҫָ��ʵ�ʵĺ������������ռλ  
    .detectFunc = Ov_detect_process,
    .handleFunc = Ov_fault_handle, 
};
Subitem* subitemsgroup1[2] = {&radiator, &cool};
Subitem* subitemsgroup2[3] = {&brake, &oc, &ov};

DiagnosticGroup group1 = {
    .id = 0,
    .number = 2,
    .subitems = subitemsgroup1 ,
};

DiagnosticGroup group2 = {
    .id = 1,
    .number = 3,
    .subitems = subitemsgroup2 ,
};
DiagnosticGroup*   diagnostics[2] = {&group1, &group2 };  
  
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
