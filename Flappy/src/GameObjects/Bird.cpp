#include "Bird.h"

Bird::Bird()
{


	float vertices[] = {
		-m_Size / 2.0f,  m_Size / 2.0f, 0.2f, 0.0f, 1.0f,
		-m_Size / 2.0f, -m_Size / 2.0f, 0.2f, 0.0f, 0.0f,
		 m_Size / 2.0f, -m_Size / 2.0f, 0.2f, 1.0f, 0.0f,
		 m_Size / 2.0f,  m_Size / 2.0f, 0.2f, 1.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	m_Texture = std::make_shared<Engine::Texture>("assets/textures/bird.png");
	m_Shader = std::make_shared<Engine::Shader>("assets/shaders/bird.vert", "assets/shaders/bird.fragm");
	m_Texture->Bind(1);
	m_Shader->Bind();
	Engine::Mat4f projection = Engine::Mat4f::Ortho(-10.0f, 10.0f, -10.0f * 9.0f / 16.0f, 10.0f * 9.0f / 16.0f, -1.0f, 1.0f);
	m_Shader->SetUniformMat4f("projection", projection);
	m_Shader->SetUniformMat4f("model", Engine::Mat4f::Translate(m_Position));
	m_Shader->SetUniform1i("tex", 1);

	m_Mesh = std::make_shared<Engine::VertexArray>();

	auto vertexbuffer = std::make_shared<Engine::VertexBuffer>(vertices, sizeof(vertices));
	auto indexbuffer = std::make_shared<Engine::IndexBuffer>(indices, sizeof(indices));

	Engine::VertexBufferLayout layout = { {"positions", Engine::DATATYPE::FLOAT3 },
											  {"texCoord", Engine::DATATYPE::FLOAT2} };

	vertexbuffer->SetLayout(layout);

	m_Mesh->SetVB(vertexbuffer);
	m_Mesh->SetIB(indexbuffer);


}

Bird::~Bird()
{

}

void Bird::Update()
{
	m_Position.y -= m_Delta;
	if (m_Control && Engine::Input::IsKeyDown(GLFW_KEY_SPACE))
		m_Delta = -0.15f;
	else
		m_Delta += 0.01f;

	m_Rotation = -m_Delta * 90.0f;
}

void Bird::Render()
{
	m_Shader->Bind();
	m_Shader->SetUniformMat4f("model", Engine::Mat4f::Translate(m_Position).Product(Engine::Mat4f::Rotate(m_Rotation)));
	m_Texture->Bind(1);
	m_Mesh->Bind();

	m_Mesh->Draw();

}

void Bird::Fall()
{
	m_Control = false;
	m_Delta = -0.15f;
}