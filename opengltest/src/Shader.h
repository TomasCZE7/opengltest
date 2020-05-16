#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader {
private:
	int rendererId;
	std::string filepath;
	std::unordered_map<std::string, int> uniformLocations;
public:
	Shader(const std::string& filepath);
	~Shader();

	void bind() const;
	void unBind() const;
	
	//Setting uniforms
	void setUniform1i(const std::string name, int v);
	void setUniform1f(const std::string name, float v);
	void setUniform4f(const std::string name, float v0, float v1, float v2, float v3);
	void setUniformMatrix4f(const std::string name, glm::mat4 matrix);
private:
	int getUniformLocation(const std::string& name);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
	ShaderProgramSource parseShader(const std::string& filepath);

};