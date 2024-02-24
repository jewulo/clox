//
// Created by jewul on 24/02/2024.
//

#ifndef CLOX_TABLE_H
#define CLOX_TABLE_H

#include "common.h"
#include "value.h"

typedef struct {
    ObjString*  key;
    Value       value;
} Entry;

typedef struct  {
    int     count;
    int     capacity;
    Entry*  entries;
} Table;

void initTable(Table* table);
void freeTable(Table* table);

#endif //CLOX_TABLE_H
