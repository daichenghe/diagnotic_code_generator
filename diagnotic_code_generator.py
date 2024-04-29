import json  
import sys
import argparse
import os


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
    .priority = {fault_priority},
    .tick = 0,
    .fault_detection_count_threshold = {fault_detection_count_threshold},  
    .fault_recover_count_threshold = {fault_recover_count_threshold},
    // .detectFunc和.handleFunc需要指向实际的函数，这里仅作占位  
    .reset_enable = {reset_enable},
    .detectFunc = {detectFunc},
    .handleFunc = {handleFunc}, 
    .resetFunc = {resetFunc},
}};
'''

diagnotic_detect_source_function_template = '''
bool {detect_func_name}()
{{
    ;
}}

'''
diagnotic_handle_source_function_template = '''
void {handle_func_name}()
{{
    ;
}}

'''

diagnotic_reset_handle_source_function_template = '''
void {reset_handle_func_name}()
{{
    ;
}}

'''

diagnotic_detect_header_function_template = '''
bool {detect_func_name}();

'''

diagnotic_handle_header_function_template = '''
void {handle_func_name}();

'''

diagnotic_reset_handle_header_function_template = '''
void {reset_handle_func_name}();

'''

# 生成C代码  
def generate_c_code(data, detect_file, handle_file):
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
#include "{detect_file}.h"
#include "{handle_file}.h"

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
            resetEnable = 'FALSE'
            if subitem["reset_enable"] == True:
                resetEnable = "TRUE"
            diagnostic_subitem_struct = diagnostic_subitem_struct_def_template.format(reset_enable = resetEnable, subitem_name = subitem["name"], id = subitem["id"], DTI = subitem["DTI"], fault_priority = subitem["fault_priority"], fault_detection_count_threshold = count, fault_recover_count_threshold = subitem["fault_detection_count_threshold"], detectFunc = subitem["fault_detection_function_pointer"], handleFunc = subitem["fault_handling_function_pointer"], resetFunc = subitem["fault_reset_handling_function_pointer"])    
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
'''  
  
    return c_code  
  


def generate_diagnotic_interface_source_code(data, detect_file, handle_file):
    fs_detect = open( (detect_file + '.c'), 'w', encoding='utf-8')
    fs_handle = open( (handle_file + '.c'), 'w', encoding='utf-8')    
    detect_c_code = '''
#include "handler.h"
#include <stdio.h>
'''
    handle_c_code = '''
#include "handler.h"
#include <stdio.h>
'''
    for i, diag in enumerate(data["diagnostics"]):  
        for j, subitem in enumerate(diag.get("subitems", [])):  
            detect_c_code+= diagnotic_detect_source_function_template.format(detect_func_name = subitem["fault_detection_function_pointer"])
            handle_c_code+= diagnotic_handle_source_function_template.format(handle_func_name = subitem["fault_handling_function_pointer"])
            if(subitem["reset_enable"] == True):
                handle_c_code+= diagnotic_reset_handle_source_function_template.format(reset_handle_func_name = subitem["fault_reset_handling_function_pointer"])
    fs_detect.write(detect_c_code)
    fs_detect.close()
    fs_handle.write(handle_c_code)
    fs_handle.close()    
            
def generate_diagnotic_interface_header_code(data, detect_file, handle_file):
    fs_detect = open( (detect_file + '.h'), 'w', encoding='utf-8')
    fs_handle = open( (handle_file + '.h'), 'w', encoding='utf-8')    
    detect_h_code = '''
#ifndef __{name}_H__
#define __{name}_H__
#include <stdint.h>

typedef uint8_t bool;
'''.format(name = detect_file)
    handle_h_code = '''
#ifndef __{name}_H__
#define __{name}_H__
#include <stdint.h>

typedef uint8_t bool;
'''.format(name = handle_file)
    for i, diag in enumerate(data["diagnostics"]):  
        for j, subitem in enumerate(diag.get("subitems", [])):  
            detect_h_code+= diagnotic_detect_header_function_template.format(detect_func_name = subitem["fault_detection_function_pointer"])    
            handle_h_code+= diagnotic_handle_header_function_template.format(handle_func_name = subitem["fault_handling_function_pointer"])
            if(subitem["reset_enable"] == True):
                handle_h_code+= diagnotic_reset_handle_header_function_template.format(reset_handle_func_name = subitem["fault_reset_handling_function_pointer"])
    detect_h_code += '''
#endif
'''
    handle_h_code += '''
#endif
'''
    fs_detect.write(detect_h_code)
    fs_detect.close()
    fs_handle.write(handle_h_code)
    fs_handle.close()    
            
    
def build_args():
    """parse input arguments
    """
    parser = argparse.ArgumentParser(
        description='Diagnotic code generator input args command:', allow_abbrev=False)

    parser.add_argument("-output", dest='output_file',
                        help="set file path to save generate code(interface)")
    parser.add_argument("-detect", dest='output_detect_file',
                        help="set file path to save generate code(detect)")
    parser.add_argument("-handle", dest='output_handle_file',
                        help="set file path to save generate code(handle)")                        
    parser.add_argument("-s", "--set-para_path", dest='user_para',
                        help="set para json file path", default="./config.json")

    return parser.parse_args()

if __name__ == '__main__':
    parser = build_args()
    c_code = str()
    with open(parser.user_para, 'r') as fs:
        data = fs.read()
        json_data = json.loads(data)    
        c_code = generate_c_code(json_data, parser.output_detect_file, parser.output_handle_file)
    with open(parser.output_file, 'w', encoding='utf-8') as fs:
        fs.write(c_code)
        fs.close()
    generate_diagnotic_interface_source_code(json_data, parser.output_detect_file, parser.output_handle_file)
    generate_diagnotic_interface_header_code(json_data, parser.output_detect_file, parser.output_handle_file)