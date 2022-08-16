// MIT License
//
// Copyright (c) 2022 Bili-TianX
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <TXEngine/Export.hpp>
#include <TXEngine/OpenGL/Vertex.hpp>
#include <TXEngine/OpenGL/VertexArrayBuffer.hpp>

namespace tx
{

/**
 * 顶点缓冲对象
 */
class TX_API VertexBuffer : public BufferBase
{
private:
    VertexArrayBuffer* m_vertexArrayBuffer;

public:
    VertexBuffer();

    ~VertexBuffer();

    void bind() override;

    void unbind() override;

    /**
     * 向OpenGL添加数据
     * @param data 数据
     * @param length 数据个数
     */
    void attachData(float data[], int length);

    /**
     * 向OpenGL添加顶点数据
     * @param vertices 顶点数组
     * @param length 顶点个数
     */
    void attachData(Vertex vertices[], int length);

    /**
     * 准备好绘制对象
     */
    void setupDraw();

    /**
     * 完成绘制
     */
    void finishDraw();

protected:
    void generateBuffer() override;
};

}// namespace tx
