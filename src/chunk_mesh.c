#include <raylib.h>
#include <raymath.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "lib/chunk.h"
#include "lib/chunk_mesh.h"

static bool IsFaceVisible(const Chunk *chunk, int x, int y, int z, int face)
{
	static const int offsets[6][3] = {
		{ 1, 0, 0 }, { -1, 0, 0 },
		{ 0, 1, 0 }, { 0, -1, 0 },
		{ 0, 0, 1 }, { 0, 0, -1 }
	};
	int neighborX = x + offsets[face][0];
	int neighborY = y + offsets[face][1];
	int neighborZ = z + offsets[face][2];

	if (neighborX < 0 || neighborX >= CHUNK_SIZE ||
		neighborY < 0 || neighborY >= CHUNK_SIZE ||
		neighborZ < 0 || neighborZ >= CHUNK_SIZE) {
		return true;
	}

	return chunk->blocks[neighborX][neighborY][neighborZ] == 0;
}

static int GetTextureIndex(int blockId)
{
	return blockId >= 1 && blockId <= 4 ? blockId : 0;
}

Model ChunkToModel(const Chunk *chunk, float blockSize, const Texture2D textures[5])
{
	static const float faceCorners[6][4][3] = {
		{ { 1, 0, 0 }, { 1, 1, 0 }, { 1, 1, 1 }, { 1, 0, 1 } },
		{ { 0, 0, 1 }, { 0, 1, 1 }, { 0, 1, 0 }, { 0, 0, 0 } },
		{ { 0, 1, 1 }, { 1, 1, 1 }, { 1, 1, 0 }, { 0, 1, 0 } },
		{ { 0, 0, 0 }, { 1, 0, 0 }, { 1, 0, 1 }, { 0, 0, 1 } },
		{ { 1, 0, 1 }, { 1, 1, 1 }, { 0, 1, 1 }, { 0, 0, 1 } },
		{ { 0, 0, 0 }, { 0, 1, 0 }, { 1, 1, 0 }, { 1, 0, 0 } }
	};
	static const float faceNormals[6][3] = {
		{ 1, 0, 0 }, { -1, 0, 0 },
		{ 0, 1, 0 }, { 0, -1, 0 },
		{ 0, 0, 1 }, { 0, 0, -1 }
	};
	static const float faceTexcoords[4][2] = {
		{ 0, 1 }, { 0, 0 }, { 1, 0 }, { 1, 1 }
	};

	if (chunk == NULL || textures == NULL || blockSize <= 0.0f) return (Model){ 0 };

	int faceCounts[5] = { 0 };
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				int blockId = chunk->blocks[x][y][z];
				if (blockId == 0) continue;
				int textureIndex = GetTextureIndex(blockId);
				for (int face = 0; face < 6; face++) {
					if (IsFaceVisible(chunk, x, y, z, face)) faceCounts[textureIndex]++;
				}
			}
		}
	}

	int meshCount = 0;
	for (int textureIndex = 0; textureIndex < 5; textureIndex++) {
		if (faceCounts[textureIndex] > 0) meshCount++;
	}
	if (meshCount == 0) return (Model){ 0 };

	Model model = { 0 };
	model.meshCount = meshCount;
	model.materialCount = meshCount;
	model.meshes = MemAlloc((unsigned int)(meshCount * sizeof(Mesh)));
	model.materials = MemAlloc((unsigned int)(meshCount * sizeof(Material)));
	model.meshMaterial = MemAlloc((unsigned int)(meshCount * sizeof(int)));
	if (model.meshes == NULL || model.materials == NULL || model.meshMaterial == NULL) {
		MemFree(model.meshes);
		MemFree(model.materials);
		MemFree(model.meshMaterial);
		return (Model){ 0 };
	}
	memset(model.meshes, 0, (size_t)meshCount * sizeof(Mesh));
	memset(model.materials, 0, (size_t)meshCount * sizeof(Material));
	memset(model.meshMaterial, 0, (size_t)meshCount * sizeof(int));
	for (int materialIndex = 0; materialIndex < meshCount; materialIndex++) {
		model.materials[materialIndex] = LoadMaterialDefault();
	}

	int outputMesh = 0;
	for (int textureIndex = 0; textureIndex < 5; textureIndex++) {
		int faceCount = faceCounts[textureIndex];
		if (faceCount == 0) continue;

		int vertexCount = faceCount * 4;
		int indexCount = faceCount * 6;
		Mesh *mesh = &model.meshes[outputMesh];
		mesh->vertexCount = vertexCount;
		mesh->triangleCount = faceCount * 2;
		mesh->vertices = MemAlloc((unsigned int)(vertexCount * 3 * sizeof(float)));
		mesh->texcoords = MemAlloc((unsigned int)(vertexCount * 2 * sizeof(float)));
		mesh->normals = MemAlloc((unsigned int)(vertexCount * 3 * sizeof(float)));
		mesh->colors = MemAlloc((unsigned int)(vertexCount * 4 * sizeof(unsigned char)));
		mesh->indices = MemAlloc((unsigned int)(indexCount * sizeof(unsigned short)));
		if (mesh->vertices == NULL || mesh->texcoords == NULL || mesh->normals == NULL ||
			mesh->colors == NULL || mesh->indices == NULL) {
			UnloadModel(model);
			return (Model){ 0 };
		}

		int faceIndex = 0;
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int y = 0; y < CHUNK_SIZE; y++) {
				for (int z = 0; z < CHUNK_SIZE; z++) {
					int blockId = chunk->blocks[x][y][z];
					if (blockId == 0 || GetTextureIndex(blockId) != textureIndex) continue;

					for (int face = 0; face < 6; face++) {
						if (!IsFaceVisible(chunk, x, y, z, face)) continue;

						int firstVertex = faceIndex * 4;
						for (int corner = 0; corner < 4; corner++) {
							int vertex = firstVertex + corner;
							int vertexOffset = vertex * 3;
							int texcoordOffset = vertex * 2;
							int colorOffset = vertex * 4;

							mesh->vertices[vertexOffset] = (x + faceCorners[face][corner][0]) * blockSize;
							mesh->vertices[vertexOffset + 1] = (y + faceCorners[face][corner][1]) * blockSize;
							mesh->vertices[vertexOffset + 2] = (z + faceCorners[face][corner][2]) * blockSize;
							mesh->texcoords[texcoordOffset] = faceTexcoords[corner][0];
							mesh->texcoords[texcoordOffset + 1] = faceTexcoords[corner][1];
							mesh->normals[vertexOffset] = faceNormals[face][0];
							mesh->normals[vertexOffset + 1] = faceNormals[face][1];
							mesh->normals[vertexOffset + 2] = faceNormals[face][2];
							mesh->colors[colorOffset] = 255;
							mesh->colors[colorOffset + 1] = 255;
							mesh->colors[colorOffset + 2] = 255;
							mesh->colors[colorOffset + 3] = 255;
						}

						int indexOffset = faceIndex * 6;
						mesh->indices[indexOffset] = (unsigned short)firstVertex;
						mesh->indices[indexOffset + 1] = (unsigned short)(firstVertex + 1);
						mesh->indices[indexOffset + 2] = (unsigned short)(firstVertex + 2);
						mesh->indices[indexOffset + 3] = (unsigned short)firstVertex;
						mesh->indices[indexOffset + 4] = (unsigned short)(firstVertex + 2);
						mesh->indices[indexOffset + 5] = (unsigned short)(firstVertex + 3);
						faceIndex++;
					}
				}
			}
		}

		UploadMesh(mesh, false);
		model.materials[outputMesh].maps[MATERIAL_MAP_DIFFUSE].texture = textures[textureIndex];
		model.meshMaterial[outputMesh] = outputMesh;
		outputMesh++;
	}

	model.transform = MatrixTranslate(
		(float)((double)chunk->x * CHUNK_SIZE * blockSize),
		0.0f,
		(float)((double)chunk->z * CHUNK_SIZE * blockSize)
	);
	return model;
}
