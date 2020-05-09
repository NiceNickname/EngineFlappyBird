#pragma once

#include "Engine.h"

class Bird
{
public:
	Bird();
	~Bird();
	void Update();
	void Render();
	void Fall();
	inline float getY() const { return m_Position.y; }
	inline float getSize() const { return m_Size; }
private:
	bool m_Control = true;
	int m_Size = 1.0f;
	std::shared_ptr<Engine::VertexArray> m_Mesh;
	std::shared_ptr<Engine::Texture> m_Texture;
	std::shared_ptr<Engine::Shader> m_Shader;
	Engine::Vector3f m_Position = Engine::Vector3f();
	float m_Rotation;
	float m_Delta = 0.0f;
};
