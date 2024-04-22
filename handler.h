
#ifndef __HANDLE_H__
#define __HANDLE_H__
#include <stdint.h>

typedef uint8_t bool;

bool Radiator_detect_process();

void Radiator_fault_handle();


bool Cooling_detect_process();

void Cooling_fault_handle();


bool Brake_detect_process();

void Brake_fault_handle();


bool Oc_detect_process();

void Oc_fault_handle();


bool Ov_detect_process();

void Ov_fault_handle();


#endif
