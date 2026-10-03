#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <raylib.h>

#ifndef CHUNK_H
#define CHUNK_H

#define CHUNK_SIZE 16

typedef struct {
    int64_t x;
    int64_t z;

    int blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];

    bool modified;
    Model model;
    bool modelReady;
} Chunk;

void InitChunk(Chunk *chunk, int64_t x, int64_t z, int fillBlock);
Chunk *CreateChunk(int64_t chunkX, int64_t chunkZ, int fillBlock);
void CreateChunkGrid(int64_t startChunkX, int64_t startChunkZ, size_t width, size_t depth, int fillBlock);
void ClearChunks(void);
size_t GetChunkCount(void);
Chunk *GetChunkAt(size_t index);
void UpdateChunks(float blockSize, const Texture2D textures[5]);
void DrawChunks(void);
void SetBlock(int64_t x, int64_t y, int64_t z, int id);
int GetBlock(int64_t x, int64_t y, int64_t z);

#endif