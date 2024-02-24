//
// Created by jewul on 20/02/2024.
//

#ifndef CLOX_VALUE_H
#define CLOX_VALUE_H

#include "common.h"

typedef enum {
    VAL_BOOL,
    VAL_NIL,
    VAL_NUMBER
} ValueType;

// typedef double Value;
typedef struct {
    ValueType type;
    union {
        bool    boolean;
        double  number;
    } as;
} Value;

// clox type verifiers
#define IS_BOOL(value)      ((value).type == VAL_BOOL)
#define IS_NIL(value)       ((value).type == VAL_NIL)
#define IS_NUMBER(value)    ((value).type == VAL_NUMBER)

// convert clox's dynamic types to C-language static types
#define AS_BOOL(value)             ((value).as.boolean)
#define AS_NUMBER(value)           ((value).as.number)

// convert C-language static types to clox's dynamic types
#define BOOL_VAL(value)     ((Value){VAL_BOOL,      {.boolean = value}})
#define NIL_VAL             ((Value){VAL_NIL,       {.number = 0}})
#define NUMBER_VAL(value)   ((Value){VAL_NUMBER,    {.number = value}})
typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

bool valuesEqual(Value a, Value b);
void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);


#endif //CLOX_VALUE_H
