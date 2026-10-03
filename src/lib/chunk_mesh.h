#ifndef CHUNK_MESH_H
#define CHUNK_MESH_H

#include <raylib.h>
#include "chunk.h"

void DrawSimpleSquare(void);
Model ChunkToModel(const Chunk *chunk, float blockSize, const Texture2D textures[5]);

#endif