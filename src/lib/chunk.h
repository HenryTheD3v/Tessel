#include <stdint.h>
#include <stdbool.h>

#ifndef CHUNK_H
#define CHUNK_H

#define CHUNK_SIZE 16

typedef struct {
    int64_t x;
    int64_t z;

    int blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];

    bool modified;
} Chunk;

extern void InitChunk(Chunk *chunk, int64_t x, int64_t z, int fillBlock);

#endif