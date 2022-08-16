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

#include <string>
#include <vector>

#include <TXEngine/Export.hpp>
#include <TXEngine/OpenGL/BufferBase.hpp>

namespace tx
{

/**
 * 纹理
 */
class TX_API Texture : public BufferBase
{
protected:
    void generateBuffer() override;

public:
    Texture();

    /**
     * 从文件中加载纹理
     * @param filename 文件路径
     */
    void loadFromFile(const std::string& filename);

    /**
     * 从void*中加载纹理
     */
    void loadFromMemory(const void* data, int width, int height);

    /**
     * 加载字符纹理
     */
    void loadCharTexture(const void* data, int width, int height);

    void bind() override;

    void unbind() override;
};

}// namespace tx
