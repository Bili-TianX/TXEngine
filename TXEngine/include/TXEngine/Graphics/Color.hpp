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
#include <TXEngine/Util/Vector.hpp>

namespace tx
{

/**
 * 颜色
 */
struct TX_API Color {
public:
    /**
     * 黑色
     */
    static const Color Black;
    /**
     * 白色
     */
    static const Color White;

    using Uint8 = unsigned char;

    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;

    Color(Uint8 r = 255, Uint8 g = 255, Uint8 b = 255, Uint8 a = 255);

    /**
     * 返回标准化之后的颜色 (0 &lt;= r, g, b, a &lt;= 1)<br/>
     * 用于OpenGL的绘制
     */
    [[nodiscard]] Vector4f normalize() const;
};

}// namespace tx
