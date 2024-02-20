//
// Created by jewul on 20/02/2024.
//

#ifndef CLOX_DEBUG_H
#define CLOX_DEBUG_H


#include "chunk.h"

void disassembleChunk(Chunk *ptr, const char *string);
int disassembleInstruction(Chunk *ptr, int offset);

#endif //CLOX_DEBUG_H
