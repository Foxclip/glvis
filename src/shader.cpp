#include "shader.h"
#include "utils.h"
#include <glad/glad.h>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    unsigned int vertexShader = compileShader(VERTEX, vertexPath);
    unsigned int fragmentShader = compileShader(FRAGMENT, fragmentPath);
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    int success;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[8192];
        glGetProgramInfoLog(ID, 8192, NULL, infoLog);
        throw std::format("ERROR::SHADER::PROGRAM::LINKING_FAILED\n{}", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

int Shader::compileShader(ShaderType type, const std::string& path) {
    std::string source = file_to_str(path);
    const char* sourceCstr = source.c_str();
    unsigned int shader = glCreateShader(type == VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, &sourceCstr, NULL);
    glCompileShader(shader);
    int success;
    char infoLog[8192];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 8192, NULL, infoLog);
        std::string typeStr = type == VERTEX ? "VERTEX" : "FRAGMENT";
        throw std::format("ERROR::SHADER::{}::COMPILATION_FAILED: {}\n{}", typeStr, path, infoLog);
    }
    return shader;
}
