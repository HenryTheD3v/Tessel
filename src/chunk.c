#include "lib/chunk.h"


void InitChunk(Chunk *chunk, int64_t x, int64_t z, int fillBlock){
    chunk->x = x;
    chunk->z = z;
    chunk->modified = false;

    for(int x = 0; x < CHUNK_SIZE; x++){
        for(int y = 0; y < CHUNK_SIZE; y++){
            for(int z = 0; z < CHUNK_SIZE; z++){
                chunk->blocks[x][y][z] = fillBlock;
            }
        }
    }
}