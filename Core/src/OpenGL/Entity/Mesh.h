#pragma once

#include <array>

#include "../IndexBuffer.h"
#include "../VertexArray.h"
#include "../VertexBuffer.h"

namespace Core {

struct Vertex
{
	std::array<float, 3> PosCoords;
	std::array<float, 3> Normal;
	std::array<float, 2> TexCoords;
};

class Mesh
{
public:

	enum MeshID {CUBE_MESH = 1, PYRAMID_MESH = 2};
	Mesh(MeshID MeshType);
	~Mesh();

	VertexArray* m_VertexArray;
	VertexBuffer* m_VertexBuffer;
	IndexBuffer* m_IndexBuffer;
	uint32_t IndexSize;
private:
	void CreateCube();
	void CreatePyramid();
};

}