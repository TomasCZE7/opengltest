#include <GL/glew.h>
#include <iostream>
#include "Renderer.h"

void clearGLErrors() {
	while (glGetError() != GL_NO_ERROR);
}

bool logGLCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "OpenGL error - " << error << " - " << function << " " << file << ": " << line;
		return false;
	}
	return true;
}

void Renderer::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const {
	shader.bind();
	vertexArray.bind();
	indexBuffer.bind();

	callGL(glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const {
	callGL(glClear(GL_COLOR_BUFFER_BIT));
}