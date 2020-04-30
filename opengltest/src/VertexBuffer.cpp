#include "VertexBuffer.h"
#include "Renderer.h"
#include <iostream>

VertexBuffer::VertexBuffer(const void* data, unsigned int size){
	callGL(glGenBuffers(1, &rendererId));
	callGL(glBindBuffer(GL_ARRAY_BUFFER, rendererId));
	callGL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer(){
	callGL(glDeleteBuffers(1, &rendererId));
}

void VertexBuffer::bind() const {
	callGL(glBindBuffer(GL_ARRAY_BUFFER, rendererId));
}

void VertexBuffer::unBind() const {
	callGL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
