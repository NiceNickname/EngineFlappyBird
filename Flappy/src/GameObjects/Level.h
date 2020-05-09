#pragma once
#include "Engine.h"
#include "Bird.h"
#include "Pipe.h"

class Level
{
public:
	Level();
	~Level();
	void Update();
	void Render();
	void CreatePipes();
	void RenderPipes();
	void UpdatePipes();
	bool Collision();
	inline bool GetControl() { return m_Control; }


private:
	int m_XScroll = 0;
	int m_Map = 0;
	int m_index = 0;
	float m_Offset = 5.0f;
	bool m_Control = true;

private:
	std::shared_ptr<Engine::VertexArray> m_BackGround;
	std::shared_ptr<Engine::Texture> m_BackGroundTexture;
	std::shared_ptr<Engine::Shader> m_BackGroundShader;

	std::shared_ptr<Bird> m_Bird;

	std::shared_ptr<Engine::Shader> m_PipeShader;

	std::shared_ptr<Pipe> m_Pipes[10];

};