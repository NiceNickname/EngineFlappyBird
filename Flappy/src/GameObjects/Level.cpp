#include "Level.h"
#include <ctime>

Level::Level()
{
	srand(time(0));

	m_Bird = std::make_shared<Bird>();

	m_BackGroundShader = std::make_shared<Engine::Shader>("assets/shaders/bg.vert", "assets/shaders/bg.fragm");
	m_BackGroundShader->Bind();

	m_BackGroundTexture = std::make_shared<Engine::Texture>("assets/textures/BackGround.png");
	m_BackGroundTexture->Bind(0);

	Engine::Mat4f projection = Engine::Mat4f::Ortho(-10.0f, 10.0f, -10.0f * 9.0f / 16.0f, 10.0f * 9.0f / 16.0f, -1.0f, 1.0f);
	m_BackGroundShader->SetUniformMat4f("projection", projection);
	m_BackGroundShader->SetUniform1i("tex", 0);

	m_PipeShader = std::make_shared<Engine::Shader>("assets/shaders/pipe.vert", "assets/shaders/pipe.fragm");
	m_PipeShader->Bind();
	m_PipeShader->SetUniformMat4f("projection", projection);
	m_PipeShader->SetUniform1i("tex", 2);




	float vertices[] = {
		-10.0f,  10.0f * 9.0f / 16.0f, 0.0f, 0.0f, 1.0f,
		-10.0f, -10.0f * 9.0f / 16.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  -10.0f * 9.0f / 16.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,   10.0f * 9.0f / 16.0f, 0.0f, 1.0f, 1.0f
	};


	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	auto vertexbuffer = std::make_shared<Engine::VertexBuffer>(vertices, sizeof(vertices));
	auto indexbuffer = std::make_shared<Engine::IndexBuffer>(indices, sizeof(indices));

	Engine::VertexBufferLayout layout = { {"positions", Engine::DATATYPE::FLOAT3 },
											  {"texCoord", Engine::DATATYPE::FLOAT2} };

	vertexbuffer->SetLayout(layout);

	m_BackGround = std::make_shared<Engine::VertexArray>();

	m_BackGround->SetVB(vertexbuffer);
	m_BackGround->SetIB(indexbuffer);

	CreatePipes();
}

Level::~Level()
{

}

void Level::Update()
{
	if (m_Control)
	{
		m_XScroll--;
		if (-m_XScroll % 335 == 0) m_Map++;
		if (-m_XScroll > 250 && -m_XScroll % 120 == 0)
			UpdatePipes();
	}


	m_Bird->Update();

	if (m_Control && Collision())
	{
		m_Control = false;
		m_Bird->Fall();
	}


}

void Level::Render()
{
	m_BackGroundTexture->Bind(0);
	m_BackGroundShader->Bind();
	m_BackGround->Bind();

	for (int i = m_Map; i < m_Map + 4; i++)
	{
		m_BackGroundShader->SetUniformMat4f("view", Engine::Mat4f::Translate(Engine::Vector3f(i * 10 + m_XScroll * 0.03f, 0.0f, 0.0f)));
		m_BackGround->Draw();
	}

	RenderPipes();

	m_Bird->Render();

}

void Level::CreatePipes()
{
	Pipe::Create();
	for (int i = 0; i < 5 * 2; i += 2)
	{
		m_Pipes[i] = std::make_shared<Pipe>(m_Offset + m_index * 3.0f, static_cast<float>(rand() % 5));
		m_Pipes[i + 1] = std::make_shared<Pipe>(m_Pipes[i]->getX(), m_Pipes[i]->getY() - 11.5f);
		m_index += 2;
	}
}

void Level::RenderPipes()
{
	m_PipeShader->Bind();
	m_PipeShader->SetUniformMat4f("view", Engine::Mat4f::Translate(Engine::Vector3f(m_XScroll * 0.05f, 0.0f, 0.0f)));
	Pipe::getTexture()->Bind(2);

	Pipe::getMesh()->Bind();

	for (int i = 0; i < 5 * 2; i++)
	{
		m_PipeShader->SetUniformMat4f("model", m_Pipes[i]->getModel());
		m_PipeShader->SetUniform1i("top", i % 2 == 0 ? 1 : 0);
		Pipe::getMesh()->Draw();
	}


}

void Level::UpdatePipes()
{
	m_Pipes[m_index % 10] = std::make_shared<Pipe>(m_Offset + m_index * 3.0f, static_cast<float>(rand() % 5));
	m_Pipes[(m_index + 1) % 10] = std::make_shared<Pipe>(m_Pipes[m_index % 10]->getX(), m_Pipes[m_index % 10]->getY() - 11.5f);
	m_index += 2;
}


bool Level::Collision()
{
	for (int i = 0; i < 5 * 2; i++)
	{
		float birdX = -m_XScroll * 0.05f;
		float birdY = m_Bird->getY();
		float pipeX = m_Pipes[i]->getX();
		float pipeY = m_Pipes[i]->getY();

		float birdX0 = birdX - m_Bird->getSize() / 2.0f;
		float birdX1 = birdX + m_Bird->getSize() / 2.0f;
		float birdY0 = birdY - m_Bird->getSize() / 2.0f;
		float birdY1 = birdY + m_Bird->getSize() / 2.0f;

		float pipeX0 = pipeX;
		float pipeX1 = pipeX + Pipe::getWidth();
		float pipeY0 = pipeY;
		float pipeY1 = pipeY + Pipe::getHeight();

		if (birdX1 > pipeX0&& birdX0 < pipeX1)
		{
			if (birdY1 > pipeY0&& birdY0 < pipeY1)
			{
				return true;
			}
		}
	}
	return false;
}