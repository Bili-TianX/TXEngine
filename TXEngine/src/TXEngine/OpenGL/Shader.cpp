#include <fstream>
#include <stdexcept>
#include <sstream>
#include <memory>

#include <glad/glad.h>

#include <TXEngine/OpenGL/GLUtil.hpp>
#include <TXEngine/OpenGL/Shader.hpp>

namespace tx
{

Shader::Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    glCall(m_program = glCreateProgram());
    m_uniformMap = new std::map<std::string, int>();

    auto vertexShader   = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    auto fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glCall(glAttachShader(m_program, vertexShader));
    glCall(glAttachShader(m_program, fragmentShader));

    glCall(glLinkProgram(m_program));
    glCall(glValidateProgram(m_program));

    glCall(glDeleteShader(vertexShader));
    glCall(glDeleteShader(fragmentShader));
}

Shader::~Shader()
{
    delete m_uniformMap;
}

unsigned int Shader::compileShader(int type, const std::string& source)
{
    glCall(auto shader = glCreateShader(type));
    auto str = source.c_str();
    glCall(glShaderSource(shader, 1, &str, nullptr));
    glCall(glCompileShader(shader));

    int result;
    glCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        glCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*) calloc(length, sizeof(char));
        glCall(glGetShaderInfoLog(shader, length, &length, message));
        std::string s = message;
        free(message);
        throw std::runtime_error(s);
    }

    return shader;
}

void Shader::bind()
{
    glCall(glUseProgram(m_program));
}

int Shader::getUniform(const std::string& name)
{
    auto result = m_uniformMap->find(name);
    if (result == m_uniformMap->end()) {
        glCall(auto uniform = glGetUniformLocation(m_program, name.c_str()));
        (*m_uniformMap)[name] = uniform;
        return uniform;
    }
    else {
        return (*result).second;
    }
}

void Shader::unbind()
{
    glCall(glUseProgram(0));
}

Shader* loadShaderFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    std::ifstream vertexShaderFile(vertexShaderPath), fragmentShaderFile(fragmentShaderPath);
    std::stringstream vertexShaderSource, fragmentShaderSource;

    if (!vertexShaderFile.is_open()) {
        throw std::runtime_error("Unable to load vertex shader file");
    }
    if (!fragmentShaderFile.is_open()) {
        throw std::runtime_error("Unable to load fragment shader file");
    }

    std::string line;
    while (std::getline(vertexShaderFile, line)) {
        vertexShaderSource << line << '\n';
    }
    while (std::getline(fragmentShaderFile, line)) {
        fragmentShaderSource << line << '\n';
    }

    vertexShaderFile.close();
    fragmentShaderFile.close();

    return new Shader(vertexShaderSource.str(), fragmentShaderSource.str());
}

Shader* getDefaultShader()
{
    static const char* vertexShaderSource = R"(
#version 330 core

// 坐标
layout(location = 0) in vec2 txPosition;
// 颜色
layout(location = 1) in vec4 txColor;
// Texture坐标
layout(location = 2) in vec2 txTexCoord;

out vec4 txVertexColor;
out vec2 txVertexTexCoord;

// 窗口矩阵
uniform mat3 windowMatrix;

void main() {
    gl_Position = vec4(windowMatrix * vec3(txPosition, 1), 1);
    txVertexTexCoord = txTexCoord;
    txVertexColor = txColor;
}
    )";

    static const char* fragmentShaderSource = R"(
#version 330 core

out vec4 FragColor;

in vec4 txVertexColor;
in vec2 txVertexTexCoord;

uniform sampler2D txTexture;
uniform int isText;

void main() {
    if (isText == 1) {
        FragColor = txVertexColor * vec4(1, 1, 1, texture(txTexture, txVertexTexCoord).r);
    } else {
        if (txVertexTexCoord.x == -1 && txVertexTexCoord.y == -1) {
            FragColor = txVertexColor;
        } else {
            FragColor = txVertexColor * texture(txTexture, txVertexTexCoord);
        }
    }
}
    )";

    static auto shader = std::make_unique<Shader>(vertexShaderSource, fragmentShaderSource);

    return shader.get();
}

}// namespace tx
