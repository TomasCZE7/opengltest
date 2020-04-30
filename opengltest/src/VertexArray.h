#pragma once

#include "VertexBuffer.h"


class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int rendererId;
public: 
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout);

	void bind() const;
	void unBind() const;
};