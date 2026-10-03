#include "lib/chunk.h"
#include "lib/world.h"



int64_t WorldToChunk(int64_t coordinate)
{
    if (coordinate >= 0)
        return coordinate / CHUNK_SIZE;

    return (coordinate + 1) / CHUNK_SIZE - 1;
}

void InitChunk(Chunk *chunk, int64_t x, int64_t z, int fillBlock){
    chunk->x = x;
    chunk->z = z;
    chunk->modified = false;

    for(int x = 0; x < CHUNK_SIZE; x++){
        for(int y = 0; y < 4; y++){
            for(int z = 0; z < CHUNK_SIZE; z++){
                chunk->blocks[x][y][z] = fillBlock;
            }
        }
    }
}

void SetBlock(int64_t x, int64_t y, int64_t z, int id)
{
    int localX;
    int localY;
    int localZ;

    localX = x % CHUNK_SIZE;
    localY = y;
    localZ = z % CHUNK_SIZE;

    if (localX < 0)
        localX += CHUNK_SIZE;

    if (localZ < 0)
        localZ += CHUNK_SIZE;

    testchunk.blocks[localX][localY][localZ] = id;
}

int GetBlock(int64_t x, int64_t y, int64_t z)
{
    int localX;
    int localY;
    int localZ;

    localX = x % CHUNK_SIZE;
    localY = y;
    localZ = z % CHUNK_SIZE;

    if (localX < 0)
        localX += CHUNK_SIZE;

    if (localZ < 0)
        localZ += CHUNK_SIZE;

    return testchunk.blocks[localX][localY][localZ];
}