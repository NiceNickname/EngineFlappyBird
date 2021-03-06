#pragma once
#include "VertexBufferLayout.h"

namespace Engine
{
	class VertexBuffer
	{
	public:
		VertexBuffer(float* data, unsigned int size);
		~VertexBuffer();
		void SetData(float* data, unsigned int size);
		void SetLayout(const VertexBufferLayout& layout);
		void Bind();
		void Unbind();
		inline VertexBufferLayout GetLayout() { return m_Layout; }

	private:
		unsigned int m_Id;
		VertexBufferLayout m_Layout = {};
	};
}