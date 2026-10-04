#include <stdint.h>
#include <math.h>

#include "lib/generator.h"
#include "lib/chunk.h"

static uint64_t HashCoordinates(int64_t x, int64_t z, int64_t seed)
{
    uint64_t value = (uint64_t)x * UINT64_C(0x9E3779B185EBCA87);
    value ^= (uint64_t)z * UINT64_C(0xC2B2AE3D27D4EB4F);
    value ^= (uint64_t)seed * UINT64_C(0x165667B19E3779F9);
    value ^= value >> 30;
    value *= UINT64_C(0xBF58476D1CE4E5B9);
    value ^= value >> 27;
    value *= UINT64_C(0x94D049BB133111EB);
    value ^= value >> 31;
    return value;
}

static float LatticeNoise(int64_t x, int64_t z, int64_t seed)
{
    return (float)((HashCoordinates(x, z, seed) >> 40) / 8388607.5) - 1.0f;
}

static float SmoothNoise(float x, float z, int64_t seed)
{
    int64_t x0 = (int64_t)floorf(x);
    int64_t z0 = (int64_t)floorf(z);
    float blendX = x - (float)x0;
    float blendZ = z - (float)z0;
    blendX = blendX * blendX * (3.0f - 2.0f * blendX);
    blendZ = blendZ * blendZ * (3.0f - 2.0f * blendZ);

    float lower = LatticeNoise(x0, z0, seed) * (1.0f - blendX) +
                  LatticeNoise(x0 + 1, z0, seed) * blendX;
    float upper = LatticeNoise(x0, z0 + 1, seed) * (1.0f - blendX) +
                  LatticeNoise(x0 + 1, z0 + 1, seed) * blendX;
    return lower * (1.0f - blendZ) + upper * blendZ;
}

static int GetTerrainHeight(int64_t x, int64_t z, int64_t seed)
{
    float worldX = (float)x;
    float worldZ = (float)z;
    float height = 8.0f;
    height += SmoothNoise(worldX * 0.018f, worldZ * 0.018f, seed) * 4.0f;
    height += SmoothNoise(worldX * 0.055f, worldZ * 0.055f, seed + 1) * 2.0f;
    height += SmoothNoise(worldX * 0.14f, worldZ * 0.14f, seed + 2) * 0.7f;

    if (height < 1.0f) height = 1.0f;
    if (height > CHUNK_SIZE - 1) height = CHUNK_SIZE - 1;
    return (int)height;
}

void GenerateChunk(int64_t chunkX, int64_t chunkZ, int64_t worldSeed)
{
    Chunk *chunk = CreateChunk(chunkX, chunkZ);
    if (chunk == NULL) return;

    int64_t startX = chunkX * CHUNK_SIZE;
    int64_t startZ = chunkZ * CHUNK_SIZE;

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {

            int64_t worldX = startX + x;
            int64_t worldZ = startZ + z;

            int height = GetTerrainHeight(worldX, worldZ, worldSeed);

            for (int y = 0; y < CHUNK_SIZE; y++) {

                if (y > height) {
                    chunk->blocks[x][y][z] = 0;
                }
                else if (y == height) {
                    chunk->blocks[x][y][z] = 1;
                }
                else if (y >= height - 3) {
                    chunk->blocks[x][y][z] = 2;
                }
                else {
                    chunk->blocks[x][y][z] = 3;
                }
            }
        }
    }

    chunk->modified = true;
}

void GenerateWorld(int64_t chunkWidth, int64_t chunkDepth, int64_t seed)
{
    if (chunkWidth <= 0 || chunkDepth <= 0) return;

    for (int64_t x = 0; x < chunkWidth; x++) {
        for (int64_t z = 0; z < chunkDepth; z++) {
            GenerateChunk(x, z, seed);
        }
    }
}