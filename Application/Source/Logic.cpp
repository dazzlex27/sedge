#include "Logic.h"

using namespace s3dge;

uint* QuadElementArray = nullptr;
uint* Cube24ElementArray = nullptr;

void LoadResources()
{
	TextureManager::Add("cry", "Resources/Models/nanosuit/body_dif.png");
	TextureManager::Add("lm-test", "Resources/Textures/lm-test.png");
	TextureManager::Add("lm-test-sp", "Resources/Textures/lm-test-sp.png");
	FontManager::Add("font1", "Resources/Fonts/Assistant-Regular.ttf", 24);
}

void CreateRenderables()
{
	Label* label = LabelFactory::CreateLabel("startup...", FontManager::Get("font1"), Vector2(0.3f, 8.4f), 0, Size2D(2, 2));
	Label* label2 = LabelFactory::CreateLabel("p:", FontManager::Get("font1"), Vector2(0.3f, 7.8f), 0, Size2D(2, 2));

	GraphicsManager::AddMesh("cube", CreateTexturedCubeUnitSize(nullptr));
	GraphicsManager::AddLabel("fps", label);
	GraphicsManager::AddLabel("position", label2);
}

uint*const CreateQuadElementArray()
{
	uint*const elements = new uint[6];

	elements[0] = 0;
	elements[1] = 1;
	elements[2] = 2;
	elements[3] = 2;
	elements[4] = 3;
	elements[5] = 0;

	return elements;
}

uint*const CreateCube24ElementArray()
{
	int offset = 0;
	uint*const elements = new uint[36];

	for (int i = 0; i < 36; i += 6)
	{
		elements[i + 0] = 0 + offset;
		elements[i + 1] = 1 + offset;
		elements[i + 2] = 2 + offset;
		elements[i + 3] = 2 + offset;
		elements[i + 4] = 3 + offset;
		elements[i + 5] = 0 + offset;
		offset += 4;
	}

	return elements;
}

uint*const GetQuadElementArray()
{
	if (QuadElementArray == nullptr)
		QuadElementArray = CreateQuadElementArray();

	return QuadElementArray;
}

uint*const GetCube24ElementArray()
{
	if (Cube24ElementArray == nullptr)
		Cube24ElementArray = CreateCube24ElementArray();

	return Cube24ElementArray;
}

Mesh*const CreateArrowMesh()
{
	VertexData* vertexData = new VertexData[3];

	vertexData[0].Position = Vector3(1, 1, -4);
	vertexData[0].Color = Color(0xff00ffff);
	vertexData[0].Normal = Vector3(0.0f, 0.0f, 1.0f);
	vertexData[1].Position = Vector3(2, 0.5, -4);
	vertexData[1].Color = Color(0xffff00ff);
	vertexData[1].Normal = Vector3(0.0f, 0.0f, 1.0f);
	vertexData[2].Position = Vector3(1, 0, -4);
	vertexData[2].Color = Color(0xffffff00);
	vertexData[2].Normal = Vector3(0.0f, 0.0f, 1.0f);

	uint* elements = new uint[3];
	elements[0] = 0;
	elements[1] = 1;
	elements[2] = 2;

	Mesh*const mesh = MeshFactory::CreateMesh(vertexData, 3, elements, 3);

	return mesh;
}

Mesh*const CreateRoomMesh(Texture2D*const texture)
{
	VertexData* vertexData = new VertexData[4];

	vertexData[0].Position = Vector3(-4, 0, 8);
	vertexData[0].Color = Color(0xffffffff);
	vertexData[0].Normal = Vector3(0, 1, 0);
	vertexData[0].UV = Vector2(0.0f, 0.0f);
	vertexData[0].TextureID = 1;

	vertexData[1].Position = Vector3(-4, 0, -8);
	vertexData[1].Color = Color(0xffffffff);
	vertexData[1].Normal = Vector3(0, 1, 0);
	vertexData[1].UV = Vector2(0.0f, 1.0f);
	vertexData[1].TextureID = 1;

	vertexData[2].Position = Vector3(4, 0, -8);
	vertexData[2].Color = Color(0xffffffff);
	vertexData[2].Normal = Vector3(0, 1, 0);
	vertexData[2].UV = Vector2(1.0f, 1.0f);
	vertexData[2].TextureID = 1;

	vertexData[3].Position = Vector3(4, 0, 8);
	vertexData[3].Color = Color(0xffffffff);
	vertexData[3].Normal = Vector3(0, 1, 0);
	vertexData[3].UV = Vector2(1.0f, 0.0f);
	vertexData[3].TextureID = 1;

	Mesh*const mesh = MeshFactory::CreateMesh(vertexData, 8, GetQuadElementArray(), 6, texture);

	return mesh;
}

static void AssignVertexData(VertexData& vertex, const Vector3& position, const uint color, const Vector3& normal, const Vector2& uv)
{
	vertex.Position = position;
	vertex.Color = Color(color);
	vertex.Normal = normal;
	vertex.UV = uv;
	vertex.TextureID = 1;
}

Mesh*const CreateTexturedCubeUnitSize(Texture2D*const texture)
{
	const int vertexCount = 24;
	VertexData* vertexData = new VertexData[vertexCount];

	// front face
	Vector3 frontNormal(0, 0, 1);
	AssignVertexData(vertexData[0], Vector3(0, 0, 1), 0xffffffff, frontNormal, Vector2(0.0f, 0.0f));
	AssignVertexData(vertexData[1], Vector3(0, 1, 1), 0xffffffff, frontNormal, Vector2(0.0f, 1.0f));
	AssignVertexData(vertexData[2], Vector3(1, 1, 1), 0xffffffff, frontNormal, Vector2(1.0f, 1.0f));
	AssignVertexData(vertexData[3], Vector3(1, 0, 1), 0xffffffff, frontNormal, Vector2(1.0f, 0.0f));

	// back face
	Vector3 backNormal(0, 0, -1);
	AssignVertexData(vertexData[4], Vector3(1, 0, 0), 0xffffffff, backNormal, Vector2(0.0f, 0.0f));
	AssignVertexData(vertexData[5], Vector3(1, 1, 0), 0xffffffff, backNormal, Vector2(0.0f, 1.0f));
	AssignVertexData(vertexData[6], Vector3(0, 1, 0), 0xffffffff, backNormal, Vector2(1.0f, 1.0f));
	AssignVertexData(vertexData[7], Vector3(0, 0, 0), 0xffffffff, backNormal, Vector2(1.0f, 0.0f));

	// top face
	Vector3 topNormal(0, 1, 0);
	AssignVertexData(vertexData[8], Vector3(0, 1, 1), 0xffffffff, topNormal, Vector2(0.0f, 0.0f));
	AssignVertexData(vertexData[9], Vector3(0, 1, 0), 0xffffffff, topNormal, Vector2(0.0f, 1.0f));
	AssignVertexData(vertexData[10], Vector3(1, 1, 0), 0xffffffff, topNormal, Vector2(1.0f, 1.0f));
	AssignVertexData(vertexData[11], Vector3(1, 1, 1), 0xffffffff, topNormal, Vector2(1.0f, 0.0f));

	// bottom face
	Vector3 bottomNormal(0, -1, 0);
	AssignVertexData(vertexData[12], Vector3(0, 0, 1), 0xffffffff, bottomNormal, Vector2(0.0f, 0.0f));
	AssignVertexData(vertexData[13], Vector3(0, 0, 0), 0xffffffff, bottomNormal, Vector2(0.0f, 1.0f));
	AssignVertexData(vertexData[14], Vector3(1, 0, 0), 0xffffffff, bottomNormal, Vector2(1.0f, 1.0f));
	AssignVertexData(vertexData[15], Vector3(1, 0, 1), 0xffffffff, bottomNormal, Vector2(1.0f, 0.0f));

	// left face
	Vector3 leftNormal(-1, 0, 0);
	AssignVertexData(vertexData[16], Vector3(0, 0, 0), 0xffffffff, leftNormal, Vector2(0.0f, 0.0f));
	AssignVertexData(vertexData[17], Vector3(0, 1, 0), 0xffffffff, leftNormal, Vector2(0.0f, 1.0f));
	AssignVertexData(vertexData[18], Vector3(0, 1, 1), 0xffffffff, leftNormal, Vector2(1.0f, 1.0f));
	AssignVertexData(vertexData[19], Vector3(0, 0, 1), 0xffffffff, leftNormal, Vector2(1.0f, 0.0f));

	// right face
	Vector3 rightNormal(1, 0, 0);
	AssignVertexData(vertexData[20], Vector3(1, 0, 1), 0xffffffff, rightNormal, Vector2(0.0f, 0.0f));
	AssignVertexData(vertexData[21], Vector3(1, 1, 1), 0xffffffff, rightNormal, Vector2(0.0f, 1.0f));
	AssignVertexData(vertexData[22], Vector3(1, 1, 0), 0xffffffff, rightNormal, Vector2(1.0f, 1.0f));
	AssignVertexData(vertexData[23], Vector3(1, 0, 0), 0xffffffff, rightNormal, Vector2(1.0f, 0.0f));

	Mesh*const mesh = MeshFactory::CreateMesh(vertexData, vertexCount, GetCube24ElementArray(), 36, texture);

	return mesh;
}