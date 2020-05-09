#include "Game.h"

void Game::Start()
{
	m_Level = std::make_shared<Level>();
}

void Game::Update()
{
	m_Level->Update();
	if (Engine::Input::IsKeyDown(GLFW_KEY_SPACE) && !m_Level->GetControl())
		m_Level = std::make_shared<Level>();
}

void Game::Render()
{
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_Level->Render();

}


Engine::App* CreateApp()
{
	return new Game();
}