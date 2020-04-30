#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
		: count(count) {
	callGL(glGenBuffers(1, &rendererId));
	callGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId));
	callGL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer(){
	callGL(glDeleteBuffers(1, &rendererId));
}

void IndexBuffer::bind() const {
	callGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId));
}

void IndexBuffer::unBind() const {
	callGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
