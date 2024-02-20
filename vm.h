//
// Created by jewul on 20/02/2024.
//

#ifndef CLOX_VM_H
#define CLOX_VM_H

#include "chunk.h"

#define STACK_MAX 256

typedef struct {
    Chunk*      chunk;  // code
    uint8_t*    ip;     // instruction pointer
    Value       stack[STACK_MAX];
    Value*      stackTop;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);
void push(Value value);
Value pop();

#endif //CLOX_VM_H
