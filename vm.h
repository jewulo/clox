//
// Created by jewul on 20/02/2024.
//

#ifndef CLOX_VM_H
#define CLOX_VM_H

#include "chunk.h"
#include "object.h"
#include "table.h"
#include "value.h"

#define FRAMES_MAX  64
#define STACK_MAX   (FRAMES_MAX * UINT8_MAX)

//typedef struct {
//    ObjFunction*    function;
//    uint8_t*        ip;
//    Value*          slots;
//} CallFrame;

// Chapter 25, Page 468;
typedef struct {
    ObjClosure*     closure;
    uint8_t*        ip;
    Value*          slots;
} CallFrame;

//typedef struct {
//    Chunk*      chunk;  // code
//    uint8_t*    ip;     // instruction pointer
//    Value       stack[STACK_MAX];
//    Value*      stackTop;
//    Table       globals;
//    Table       strings;
//    Obj*        objects;
//} VM;

// Chapter 24, Page 443;
typedef struct {
    CallFrame   frames[FRAMES_MAX];
    int         frameCount;     // instruction pointer

    Value       stack[STACK_MAX];
    Value*      stackTop;
    Table       globals;
    Table       strings;
    ObjUpvalue* openUpvalues;
    Obj*        objects;
    int         grayCount;
    int         grayCapacity;
    Obj         **grayStack;

} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();
InterpretResult interpret_chunk(Chunk* chunk);
InterpretResult interpret(const char* source);
void push(Value value);
Value pop();

#endif //CLOX_VM_H
