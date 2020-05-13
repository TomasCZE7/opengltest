#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image.h"

Texture::Texture(const std::string& filepath)
	: rendererId(0), filepath(filepath), localBuffer(nullptr), width(0), height(0), BPP(0){

	stbi_set_flip_vertically_on_load(1);
	localBuffer = stbi_load(filepath.c_str(), &width, &height, &BPP, 4);

	callGL(glGenTextures(1, &rendererId));
	callGL(glBindTexture(GL_TEXTURE_2D, rendererId));

	callGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	callGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	callGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	callGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	callGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
	unBind();

	if (localBuffer)
		stbi_image_free(localBuffer);
}

Texture::~Texture(){
	callGL(glDeleteTextures(1, &rendererId));
}

void Texture::bind(unsigned int slot) const {
	callGL(glActiveTexture(GL_TEXTURE0 + slot));
	callGL(glBindTexture(GL_TEXTURE_2D, rendererId));
}

void Texture::unBind() const {
	callGL(glBindTexture(GL_TEXTURE_2D, 0));
}
