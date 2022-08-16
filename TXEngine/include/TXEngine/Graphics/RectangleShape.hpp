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
#include <TXEngine/Graphics/Shape.hpp>
#include <TXEngine/Graphics/TextureTarget.hpp>

namespace tx
{

/**
 * 矩形
 */
class TX_API RectangleShape : public Shape
{
private:
    /**
     * 垂直、水平翻转
     */
    bool m_flipV = false, m_flipH = false;

    /**
     * 宽、高
     */
    float m_width, m_height;

public:
    RectangleShape(float x, float y, float width, float height, Color color = Color::White, Texture *texture = nullptr);

    void draw(Shader* shader) override;

    void setSize(float width, float height);

    void setTexture(Texture* texture) override;

    /**
     * 设置翻转
     * @param flipV 垂直翻转
     * @param flipH 水平翻转
     */
    void setFlip(bool flipV, bool flipH);

protected:
    void updateVertices() override;
};

}// namespace tx
