#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdint.h>

void GenerateChunk(int64_t chunkX, int64_t chunkZ, int64_t worldSeed);
void GenerateWorld(int64_t chunkWidth, int64_t chunkDepth, int64_t seed);

#endif