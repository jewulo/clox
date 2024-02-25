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

#define TABLE_MAX_LOAD 0.75

void initTable(Table* table);
void freeTable(Table* table);
bool tableGet(Table* table, ObjString* key, Value* value);
bool tableSet(Table* table, ObjString* key, Value value);
bool tableDelete(Table* table, ObjString* key);
void tableAddAll(Table* from, Table* to);

#endif //CLOX_TABLE_H
