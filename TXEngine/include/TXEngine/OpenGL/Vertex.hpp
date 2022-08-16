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
#include <TXEngine/Graphics/Color.hpp>

namespace tx
{

/**
 * 封装顶点（坐标、颜色、纹理坐标）
 */
struct TX_API Vertex {
    /**
     * 坐标
     */
    float x, y;
    /**
     * 颜色
     */
    Color color;
    /**
     * 顶点坐标
     */
    mutable float tex_x, tex_y;

    Vertex(float x = 0, float y = 0, Color color = Color::White, float tex_x = -1, float tex_y = -1);
};

}// namespace tx
