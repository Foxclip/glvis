#include "shader.h"
#include "utils.h"
#include <glad/glad.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexShaderSource = file_to_str(vertexPath);
    std::string fragmentShaderSource = file_to_str(fragmentPath);
    const char* vertexShaderSourceCstr = vertexShaderSource.c_str();
    const char* fragmentShaderSourceCstr = fragmentShaderSource.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourceCstr, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[8192];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 8192, NULL, infoLog);
        throw std::format("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{}", infoLog);
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceCstr, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 8192, NULL, infoLog);
        throw std::format("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n{}", infoLog);
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
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
