#pragma once

#include <string>

enum ShaderType {
    VERTEX,
    FRAGMENT
};

class Shader
{
public:
    unsigned int ID;
  
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    void use();
    void setBool(const std::string& name, bool value) const;  
    void setInt(const std::string& name, int value) const;   
    void setFloat(const std::string& name, float value) const;

private:
    int compileShader(ShaderType type, const std::string& path);

};
