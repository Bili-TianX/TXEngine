#pragma once

#include <map>
#include <string>

#include <TXEngine/Export.hpp>
#include <TXEngine/OpenGL/IBind.hpp>

namespace tx
{

/**
 * 封装OpenGL着色器
 */
class TX_API Shader : public IBind
{
private:
    /**
     * Uniform位置的缓冲
     */
    std::map<std::string, int>* m_uniformMap;
    /**
     * 着色器ID
     */
    int m_program;

    /**
     * 编译着色器
     * @param type 着色器类型
     * @param source 着色器源码
     * @return 着色器ID
     */
    unsigned int compileShader(int type, const std::string& source);

public:
    /**
     * @param vertexShaderSource 顶点着色器的源码
     * @param fragmentShaderSource 片段着色器的源码
     */
    Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

    ~Shader();

    void bind() override;

    void unbind() override;

    /**
     * 返回着色器中的Uniform的位置
     * @param name
     * @return
     */
    int getUniform(const std::string& name);
};

/**
 * 从文件中加载Shader
 * @param vertexShaderPath 顶点着色器文件的路径
 * @param fragmentShaderPath 片段着色器文件的路径
 * @return 着色器
 */
TX_API Shader* loadShaderFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

/**
 * 获取默认着色器
 */
TX_API Shader* getDefaultShader();

}// namespace tx