//
// Created by jewul on 19/02/2024.
//

#ifndef CLOX_COMMON_H
#define CLOX_COMMON_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define NAN_BOXING
#define DEBUG_PRINT_CODE
#define DEBUG_TRACE_EXECUTION

#undef DEBUG_STRESS_GC
#undef DEBUG_LOG_GC

#define UINT8_COUNT (UINT8_MAX + 1)

#endif //CLOX_COMMON_H
