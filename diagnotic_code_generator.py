import json  
import sys
  
# 假设json_str是从文件中读取的JSON字符串  
json_str = '''  
{  
    "diagnostics": [  
        {  
            "id": 0,  
            "name": "group1",
            "subitems": [  
                {  
                    "id": 0, 
                    "name": "radiator",
                    "description": "Brake fluid leak",               
                    "DTI": 5,  
                    "FDTI": 10,  
                    "fault_status": "NORMAL",  
                    "fault_detection_function_pointer": "Radiator_detect_process",  
                    "fault_handling_function_pointer": "Radiator_fault_handle"  
                },  
                {  
                    "id": 1,  
                    "name": "cool",                    
                    "DTI": 5,  
                    "FDTI": 20,  
                    "fault_status": "NORMAL",  
                    "fault_detection_function_pointer": "Cooling_detect_process",  
                    "fault_handling_function_pointer": "Cooling_fault_handle"  
                }  
            ]  
        },  
        {  
            "id": 1,  
            "name": "group2",
            "subitems": [  
                {  
                    "id": 0,  
                    "name": "brake",
                    "DTI": 5,  
                    "FDTI": 30,  
                    "fault_status": "NORMAL",  
                    "fault_detection_function_pointer": "Brake_detect_process",  
                    "fault_handling_function_pointer": "Brake_fault_handle"  
                },  
                {  
                    "id": 1,  
                    "name": "oc",
                    "DTI": 5,  
                    "FDTI": 100,  
                    "fault_status": "NORMAL",  
                    "fault_detection_function_pointer": "Oc_detect_process",  
                    "fault_handling_function_pointer": "Oc_fault_handle"  
                },  
                {  
                    "id": 2,  
                    "name": "ov",
                    "DTI": 5,  
                    "FDTI": 10,  
                    "fault_status": "NORMAL",  
                    "fault_detection_function_pointer": "Ov_detect_process",  
                    "fault_handling_function_pointer": "Ov_fault_handle"  
                }  
            ]  
        }  
    ],
    "diagnotic task period": 5
}  
'''  
  
# 解析JSON  
data = json.loads(json_str)  




diagnostic_group_struct_def_template = '''
DiagnosticGroup {group_name} = {{
    .id = {id},
    .number = {number},
    .subitems = {subitems}
}};
'''

diagnostic_subitem_struct_def_template = '''
Subitem {subitem_name} = 
{{
    .id = {id},  
    .DTI = {DTI},  
    .fault_detection_count_threshold = {fault_detection_count_threshold},  
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .detectFunc = {detectFunc},
    .handleFunc = {handleFunc}, 
}};
'''

# 生成C代码  
def generate_c_code(data):  
    # 计算诊断项和子项的数量  
    num_diagnostics = len(data["diagnostics"])  
    max_diag_id_length = max(len(str(diag["id"])) for diag in data["diagnostics"]) + 1  # 加1是为了字符串的结束符'\0'  
    max_subitem_id_length = 1  
    max_subitems_per_diag = max(len(diag.get("subitems", [])) for diag in data["diagnostics"])  
    diagnostic_defs = str()

    subitems = list()
    # 生成C代码  
    c_code = f'''  
#include <stdio.h>  
#include <stdint.h> // 引入stdint.h以使用uint8_t类型  
#include "handle.h"
  
#ifndef TRUE
#define TRUE        0
#define FALSE       1  
#endif
 
#define NUM_DIAGNOSTICS {num_diagnostics}  
#define MAX_DIAG_ID_LENGTH {max_diag_id_length}  
#define MAX_SUBITEM_ID_LENGTH {max_subitem_id_length}  
#define MAX_SUBITEMS_PER_DIAG {max_subitems_per_diag}  
  
// 函数指针类型定义，需要在C代码中实现这些函数  
typedef bool (*detectProcess)();  
typedef void (*handleProcess)();  
  
// 定义结构体  
typedef struct Subitem {{  
    char id;  
    uint8_t DTI;  
    uint8_t fault_detection_count_threshold;   
    uint8_t fault_count;
    bool fault_status;
    detectProcess detectFunc; 
    handleProcess handleFunc; 
}} Subitem;  
  
typedef struct {{  
    int id; 
    uint16_t number;        
    Subitem** subitems;  
}} DiagnosticGroup;  
  

'''  


    # 填充诊断项和子项数据  
    for i, diag in enumerate(data["diagnostics"]):  
        
        subitems_code = ''  
        for j, subitem in enumerate(diag.get("subitems", [])):  
            count = int(subitem["FDTI"]/subitem["DTI"])
            diagnostic_subitem_struct = diagnostic_subitem_struct_def_template.format(subitem_name = subitem["name"], id = subitem["id"], DTI = subitem["DTI"], fault_detection_count_threshold = count, detectFunc = subitem["fault_detection_function_pointer"], handleFunc = subitem["fault_handling_function_pointer"])    
            c_code += diagnostic_subitem_struct

    for diag in (data["diagnostics"]):  
        subitem_group = list()
        subsubitems = "Subitem* subitems{0}[{1}] = {{".format(diag["name"], len(diag['subitems']))    
        '''
        for subitem in diag['subitems']:
            # subitem_group.append(subitem)
            subsubitems+= (subitem['name']+', ')
        '''
        length = len(diag['subitems'])
        for i, subitem in enumerate(diag['subitems']):
            subsubitems+= ('&' + (subitem['name'])    )         
            if i < length - 1:
                subsubitems+= ', '   
        subsubitems+= '};\n'
        c_code += subsubitems


    DiagnosticGroupArray = list()
    for i, diag in enumerate(data["diagnostics"]):  
        group_name = diag["name"]
        DiagnosticGroupArray.append(group_name)
        max_subitems_per_diag = len(diag["subitems"])
        diagnostic_group_struct = diagnostic_group_struct_def_template.format(group_name = group_name, id = diag["id"], number = max_subitems_per_diag, subitems = "subitems{0} ,".format(diag["name"]) )
        c_code += diagnostic_group_struct
        

    DiagnosticGroupArrayStr = "DiagnosticGroup*   diagnostics[{0}] = {{".format(len(DiagnosticGroupArray))
    for array in DiagnosticGroupArray:
        DiagnosticGroupArrayStr+= '&{0}'.format(array)
        if array != DiagnosticGroupArray[-1]:
            DiagnosticGroupArrayStr+= ', '
    DiagnosticGroupArrayStr+= ' };'
    c_code+= DiagnosticGroupArrayStr
    #print(c_code)        
    #exit()     
    # 结尾部分  
    c_code += '''  
  
// 定时检查诊断项的函数  
void check_diagnostics() {
    for (int i = 0; i < NUM_DIAGNOSTICS; i++) {
        for (int j = 0; j < diagnostics[i]->number; j++) {
            // 调用检测函数  
            bool detection_result = diagnostics[i]->subitems[j]->detectFunc();  
              
            // 更新fault_detection_count和fault_status  
            if (detection_result) {
                diagnostics[i]->subitems[j]->fault_count++;  
                if (diagnostics[i]->subitems[j]->fault_count >= diagnostics[i]->subitems[j]->fault_detection_count_threshold) {
                    diagnostics[i]->subitems[j]->fault_status = TRUE;  
                    // 调用处理函数  
                    diagnostics[i]->subitems[j]->handleFunc();  
                }
            } else {
                diagnostics[i]->subitems[j]->fault_status = FALSE;  
                diagnostics[i]->subitems[j]->fault_count = 0; // 可能需要重置计数，取决于具体需求  
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
'''  
  
    return c_code  
  
# 生成C代码
fs = open(sys.argv[1], 'w')
c_code = generate_c_code(data)  
fs.write(c_code)
fs.close()
