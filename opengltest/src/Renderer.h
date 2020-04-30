#pragma once
#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define callGL(x) clearGLErrors();\
	x;\
	ASSERT(logGLCall(#x, __FILE__, __LINE__))

void clearGLErrors();

bool logGLCall(const char* function, const char* file, int line);

class Renderer {
public:
	void clear() const;
	void draw(const VertexArray& vertexArray, const IndexBuffer& ib, const Shader& shader) const;
};