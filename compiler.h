//
// Created by jewul on 21/02/2024.
//

#ifndef CLOX_COMPILER_H
#define CLOX_COMPILER_H

#include "object.h"
#include "vm.h"
#include "chunk.h"

// void compile(const char* source);
bool compile(const char* source, Chunk* chunk);

#endif //CLOX_COMPILER_H
