#include "Shader.h"
#include "Renderer.h"
#include <GL/GL.h>
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& filepath) 
    :filepath(filepath), rendererId(0) {
    ShaderProgramSource source = parseShader(filepath);
    rendererId = createShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader(){
    callGL(glDeleteProgram(rendererId));
}

void Shader::bind() const {
    callGL(glUseProgram(rendererId));
}

void Shader::unBind() const {
    callGL(glUseProgram(0));
}

void Shader::setUniform4f(const std::string name, float v0, float v1, float v2, float v3){
    callGL(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

int Shader::getUniformLocation(const std::string& name){
    if (uniformLocations.find(name) != uniformLocations.end())
        return uniformLocations[name];

    callGL(int location = glGetUniformLocation(rendererId, name.c_str()));
    if (location == -1)
        std::cout << "Warning >> Uniform '" << name << "' doesn't exist!" << std::endl;
    
        uniformLocations[name] = location;
    return location;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    callGL(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    callGL(glShaderSource(id, 1, &src, nullptr));
    callGL(glCompileShader(id));

    int result;
    callGL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (!result) {
        int length;
        callGL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)_malloca(length * sizeof(char));
        callGL(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        callGL(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::createShader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) {
    unsigned int program = glCreateProgram();
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderCode);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

    callGL(glAttachShader(program, vertexShader));
    callGL(glAttachShader(program, fragmentShader));
    callGL(glLinkProgram(program));
    callGL(glValidateProgram(program));

    callGL(glDeleteShader(vertexShader));
    callGL(glDeleteShader(fragmentShader));

    return program;
}

ShaderProgramSource Shader::parseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    if (!stream.is_open()){
        std::cout << "Error >> Parse shader: File " << filepath << " wasn't found." << std::endl;
        return { "", "" };
    }

    enum class ShaderType {
        NONE = -1, VERTEX, FRAGMENT
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
}