#include "Pipe.h"

float Pipe::s_Width = 1.5f;
float Pipe::s_Height = 8.0f;
std::shared_ptr<Engine::Texture> Pipe::s_Texture = nullptr;
std::shared_ptr<Engine::VertexArray> Pipe::s_Mesh = nullptr;

void Pipe::Create()
{
	float vertices[] = {
		 0.0f,   s_Height, 0.1f, 0.0f, 1.0f,
		 0.0f,   0.0f,     0.1f, 0.0f, 0.0f,
		s_Width, 0.0f,     0.1f, 1.0f, 0.0f,
		s_Width, s_Height, 0.1f, 1.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	s_Mesh = std::make_shared<Engine::VertexArray>();
	s_Texture = std::make_shared<Engine::Texture>("assets/textures/pipe.png");

	auto vertexbuffer = std::make_shared<Engine::VertexBuffer>(vertices, sizeof(vertices));
	auto indexbuffer = std::make_shared<Engine::IndexBuffer>(indices, sizeof(indices));

	Engine::VertexBufferLayout layout = { {"positions", Engine::DATATYPE::FLOAT3},
									{"texCoords", Engine::DATATYPE::FLOAT2} };

	vertexbuffer->SetLayout(layout);

	s_Mesh->SetVB(vertexbuffer);
	s_Mesh->SetIB(indexbuffer);
}

Pipe::Pipe(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Model = Engine::Mat4f::Translate(m_Position);
}

Pipe::~Pipe()
{

}

void Pipe::DeleteMeshAndTexture()
{

}

