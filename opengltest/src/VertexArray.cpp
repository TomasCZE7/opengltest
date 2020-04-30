#include "VertexArray.h"
#include "Renderer.h"

#include "VertexBufferLayout.h"

VertexArray::VertexArray() {
	callGL(glGenVertexArrays(1, &rendererId));
}

VertexArray::~VertexArray() {
	callGL(glDeleteVertexArrays(1, &rendererId));
}

void VertexArray::addBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout) {
	bind();
	buffer.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		//Specifies attributes of vertex.
		//index - the index of attribute
		//size - the number of variables discribing the attribute (only 2 positions = 2 floats)
		//type - the data type of data in attribute
		//normalized - if the data are normalized (i.e. if we have rgb color 255, that normalizes to 1, beacuse its max value)
		//stride - the offset of each vertex. How many bytes does the GL need to cross to reach next vertex
		//pointer - the offest of attribute. How many bytes does does the GL need to cross from the beggining to reach this attribute
		callGL(glVertexAttribPointer(i, element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*)offset));
		//enabling atttribute at specific index
		callGL(glEnableVertexAttribArray(i));

		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
}

void VertexArray::bind() const {
	callGL(glBindVertexArray(rendererId));
}

void VertexArray::unBind() const {
	callGL(glBindVertexArray(0));
}