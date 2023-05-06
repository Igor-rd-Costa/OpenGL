#include "glm/glm.hpp"

#include "Mesh.h"
#include "../VertexBuffer.h"

namespace Core {

Mesh::Mesh(MeshID MeshType)
{
	switch (MeshType)
	{
	case CUBE_MESH: CreateCube();
		break;
	case PYRAMID_MESH: CreatePyramid();
		break;
	}
}

Mesh::~Mesh()
{
	delete m_VertexArray;
	delete m_VertexBuffer;
	delete m_IndexBuffer;
}


void Mesh::CreateCube()
{
	Vertex Vertices[24] = {

		//front
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f,

		//bottom
		-0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

		//left
		-0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		//right
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,

		 //back
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,

		//top
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f
	};


	uint32_t Indices[36];
	for (int x = 0, y = 0; x < 32; x += 6, y += 4)
	{
		Indices[x] = y;
		Indices[x + 1] = y + 1;
		Indices[x + 2] = y + 2;
		Indices[x + 3] = y + 2;
		Indices[x + 4] = y + 3;
		Indices[x + 5] = y;
	}
	
	this->IndexSize = sizeof(Indices);
	m_VertexArray = new VertexArray();
	m_VertexArray->Bind();

	m_VertexBuffer = new VertexBuffer(sizeof(Vertices), Vertices);
	m_VertexBuffer->Bind();

	m_VertexArray->AddAttribPointer<float>(3);
	m_VertexArray->AddAttribPointer<float>(3);
	m_VertexArray->AddAttribPointer<float>(2);
	m_VertexArray->SetAttribPointers();

	m_IndexBuffer = new IndexBuffer(IndexSize, Indices);
	
	m_VertexBuffer->Unbind();
	m_IndexBuffer->Unbind();
	m_VertexArray->Unbind();
}

void Mesh::CreatePyramid()
{
	Vertex Vertices[16];
	
		//bottom
		Vertices[0] = { -0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f};
		Vertices[1] = {  0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f};
		Vertices[2] = {  0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.5f};
		Vertices[3] = { -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.5f};



		glm::vec3 Vec0 = glm::vec3(-0.5f, -0.5f, 0.5f);
		glm::vec3 Vec1 = glm::vec3(0.5f, -0.5f, 0.5f);
		glm::vec3 Vec2 = glm::vec3(0.0f, 0.5f, 0.0f);
		glm::vec3 normal = glm::normalize(glm::cross(Vec1 - Vec0, Vec2 - Vec0));

		//front
		Vertices[4] = { -0.5f, -0.5f,  0.5f, normal.x, normal.y, normal.z, 0.0f, 0.5f};
		Vertices[5] = {  0.5f, -0.5f,  0.5f, normal.x, normal.y, normal.z, 1.0f, 0.5f};
		Vertices[6] = {  0.0f,  0.5f,  0.0f, normal.x, normal.y, normal.z, 0.5f, 1.0f};




		Vec0 = glm::vec3(-0.5f, -0.5f, -0.5f);
		Vec1 = glm::vec3(-0.5f, -0.5f, 0.5f);
		Vec2 = glm::vec3(0.0f, 0.5f, 0.0f);
		normal = glm::normalize(glm::cross(Vec1 - Vec0, Vec2 - Vec0));

		//left
		Vertices[7] = { -0.5f, -0.5f, -0.5f, normal.x, normal.y, normal.z, 0.0f, 0.5f };
		Vertices[8] = { -0.5f, -0.5f,  0.5f, normal.x, normal.y, normal.z, 1.0f, 0.5f };
		Vertices[9] = {  0.0f,  0.5f,  0.0f, normal.x, normal.y, normal.z, 0.5f, 1.0f };



		Vec0 = glm::vec3(0.5f, -0.5f, 0.5f);
		Vec1 = glm::vec3(0.5f, -0.5f, -0.5f);
		Vec2 = glm::vec3(0.0f, 0.5f, 0.0f);
		normal = glm::normalize(glm::cross(Vec1 - Vec0, Vec2 - Vec0));

		//right
		Vertices[10] = {  0.5f, -0.5f,  0.5f, normal.x, normal.y, normal.z, 0.0f, 0.5f };
		Vertices[11] = {  0.5f, -0.5f, -0.5f, normal.x, normal.y, normal.z, 1.0f, 0.5f };
		Vertices[12] = {  0.0f,  0.5f,  0.0f, normal.x, normal.y, normal.z, 0.5f, 1.0f };



		Vec0 = glm::vec3(0.5f, -0.5f, -0.5f);
		Vec1 = glm::vec3(-0.5f, -0.5f, -0.5f);
		Vec2 = glm::vec3(0.0f,  0.5f,  0.0f);
		normal = glm::normalize(glm::cross(Vec1 - Vec0, Vec2 - Vec0));

		//back
		Vertices[13] = {  0.5f, -0.5f, -0.5f, normal.x, normal.y, normal.z, 0.0f, 0.5f };
		Vertices[14] = { -0.5f, -0.5f, -0.5f, normal.x, normal.y, normal.z, 1.0f, 0.5f };
		Vertices[15] = {  0.0f,  0.5f,  0.0f, normal.x, normal.y, normal.z, 0.5f, 1.0f };

		uint32_t Indices[18];
		for (int x = 0, y = 0; x < 6; x += 6) {
			Indices[x] = y;
			Indices[x + 1] = y + 1;
			Indices[x + 2] = y + 2;
			Indices[x + 3] = y + 2;
			Indices[x + 4] = y + 3;
			Indices[x + 5] = y;
		}
		for (int x = 6, y = 4; x < 18; x += 3, y += 3)	{
			Indices[x] = y;
			Indices[x + 1] = y + 1;
			Indices[x + 2] = y + 2;
		}

		this->IndexSize = sizeof(Indices);

		m_VertexArray = new VertexArray();
		m_VertexArray->Bind();

		m_VertexBuffer = new VertexBuffer(sizeof(Vertices), Vertices);
		m_VertexBuffer->Bind();

		m_VertexArray->AddAttribPointer<float>(3);
		m_VertexArray->AddAttribPointer<float>(3);
		m_VertexArray->AddAttribPointer<float>(2);
		m_VertexArray->SetAttribPointers();

		m_IndexBuffer = new IndexBuffer(this->IndexSize, Indices);

		m_VertexBuffer->Unbind();
		m_IndexBuffer->Unbind();
		m_VertexArray->Unbind();

}

}