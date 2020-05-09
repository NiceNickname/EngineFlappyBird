#pragma once
#include "Engine.h"

class Pipe
{
public:
	static void Create();
	Pipe(float x, float y);
	~Pipe();
	inline float getX() const { return m_Position.x; }
	inline float getY() const { return m_Position.y; }
	inline static std::shared_ptr<Engine::VertexArray> getMesh() { return s_Mesh; }
	inline static std::shared_ptr<Engine::Texture> getTexture() { return s_Texture; }
	inline static float getWidth() { return s_Width; }
	inline static float getHeight() { return s_Height; }
	inline Engine::Mat4f getModel() { return m_Model; }
	static void DeleteMeshAndTexture();

private:
	Engine::Vector3f m_Position = Engine::Vector3f();
	Engine::Mat4f m_Model;
	static std::shared_ptr<Engine::VertexArray> s_Mesh;
	static std::shared_ptr<Engine::Texture> s_Texture;
	static float s_Width, s_Height;
};