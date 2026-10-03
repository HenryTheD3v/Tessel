#include <raylib.h>
#include <stddef.h>
#include "lib/chunk.h"
#include "lib/chunk_mesh.h"

static Chunk *chunks;
static size_t chunkCount;
static size_t chunkCapacity;

static int64_t WorldToChunk(int64_t coordinate)
{
    if (coordinate >= 0)
        return coordinate / CHUNK_SIZE;

    return (coordinate + 1) / CHUNK_SIZE - 1;
}

static int WorldToLocal(int64_t coordinate)
{
    int local = (int)(coordinate % CHUNK_SIZE);
    return local < 0 ? local + CHUNK_SIZE : local;
}

static Chunk *FindChunk(int64_t chunkX, int64_t chunkZ)
{
    for (size_t index = 0; index < chunkCount; index++) {
        if (chunks[index].x == chunkX && chunks[index].z == chunkZ)
            return &chunks[index];
    }

    return NULL;
}

void InitChunk(Chunk *chunk, int64_t x, int64_t z, int fillBlock)
{
    chunk->x = x;
    chunk->z = z;
    chunk->modified = true;
    chunk->model = (Model){ 0 };
    chunk->modelReady = false;

    for (int blockX = 0; blockX < CHUNK_SIZE; blockX++) {
        for (int blockY = 0; blockY < CHUNK_SIZE; blockY++) {
            for (int blockZ = 0; blockZ < CHUNK_SIZE; blockZ++) {
                chunk->blocks[blockX][blockY][blockZ] = fillBlock;
            }
        }
    }
}

Chunk *CreateChunk(int64_t chunkX, int64_t chunkZ, int fillBlock)
{
    Chunk *existing = FindChunk(chunkX, chunkZ);
    if (existing != NULL) return existing;

    if (chunkCount == chunkCapacity) {
        size_t newCapacity = chunkCapacity == 0 ? 8 : chunkCapacity * 2;
        Chunk *newChunks = MemRealloc(chunks, (unsigned int)(newCapacity * sizeof(Chunk)));
        if (newChunks == NULL) return NULL;
        chunks = newChunks;
        chunkCapacity = newCapacity;
    }

    Chunk *chunk = &chunks[chunkCount++];
    InitChunk(chunk, chunkX, chunkZ, fillBlock);
    return chunk;
}

void CreateChunkGrid(int64_t startChunkX, int64_t startChunkZ, size_t width, size_t depth, int fillBlock)
{
    for (size_t x = 0; x < width; x++) {
        for (size_t z = 0; z < depth; z++) {
            CreateChunk(startChunkX + (int64_t)x, startChunkZ + (int64_t)z, fillBlock);
        }
    }
}

void ClearChunks(void)
{
    for (size_t index = 0; index < chunkCount; index++) {
        if (chunks[index].modelReady) UnloadModel(chunks[index].model);
    }

    MemFree(chunks);
    chunks = NULL;
    chunkCount = 0;
    chunkCapacity = 0;
}

size_t GetChunkCount(void)
{
    return chunkCount;
}

Chunk *GetChunkAt(size_t index)
{
    if (index >= chunkCount) return NULL;
    return &chunks[index];
}

void UpdateChunks(float blockSize, const Texture2D textures[5])
{
    for (size_t index = 0; index < chunkCount; index++) {
        Chunk *chunk = &chunks[index];
        if (!chunk->modified) continue;

        if (chunk->modelReady) UnloadModel(chunk->model);
        chunk->model = ChunkToModel(chunk, blockSize, textures);
        chunk->modelReady = chunk->model.meshCount > 0;
        chunk->modified = false;
    }
}

void DrawChunks(void)
{
    for (size_t index = 0; index < chunkCount; index++) {
        if (chunks[index].modelReady)
            DrawModel(chunks[index].model, (Vector3){ 0 }, 1.0f, WHITE);
    }
}

void SetBlock(int64_t x, int64_t y, int64_t z, int id)
{
    if (y < 0 || y >= CHUNK_SIZE) return;

    int64_t chunkX = WorldToChunk(x);
    int64_t chunkZ = WorldToChunk(z);
    int localX = WorldToLocal(x);
    int localZ = WorldToLocal(z);
    Chunk *chunk = CreateChunk(chunkX, chunkZ, 0);
    if (chunk == NULL) return;

    if (chunk->blocks[localX][(int)y][localZ] != id) {
        chunk->blocks[localX][(int)y][localZ] = id;
        chunk->modified = true;
    }
}

int GetBlock(int64_t x, int64_t y, int64_t z)
{
    if (y < 0 || y >= CHUNK_SIZE) return 0;

    int64_t chunkX = WorldToChunk(x);
    int64_t chunkZ = WorldToChunk(z);
    int localX = WorldToLocal(x);
    int localZ = WorldToLocal(z);
    Chunk *chunk = FindChunk(chunkX, chunkZ);
    if (chunk == NULL) return 0;

    return chunk->blocks[localX][(int)y][localZ];
}