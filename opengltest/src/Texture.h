#pragma once

#include "Renderer.h"

class Texture {
private:
	unsigned int rendererId;
	std::string filepath;
	unsigned char* localBuffer;
	int width, height, BPP;
public:
	Texture(const std::string& filepath);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unBind() const;

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }
};