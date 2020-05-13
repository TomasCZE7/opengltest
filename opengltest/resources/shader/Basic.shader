#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCorinateIn;

out vec2 texCoordinate;

void main() 
{
	gl_Position = position;
	texCoordinate = texCorinateIn;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 texCoordinate;

uniform vec4 u_Color;
uniform sampler2D textureUniform;

void main() 
{
	vec4 texColor = texture(textureUniform, texCoordinate);
	color = texColor;
};