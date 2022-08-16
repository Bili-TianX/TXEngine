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

#include <TXEngine/Graphics/Font.hpp>
#include <TXEngine/Graphics/Texture.hpp>
#include <TXEngine/Graphics/RectangleShape.hpp>

namespace tx
{

/**
 * 文本（仅支持UTF-8编码）
 */
class TX_API Text : public Drawable
{
private:
    /**
     * 字符
     */
    struct Character {
        Texture* texture;
        RectangleShape *shape;
        float x, y;
        float width, height;
        Color color;

        Character(Texture* texture, float x, float y, float width, float height, Color color);

        void draw(Shader* shader) const;
        virtual ~Character();
    };

    Font *m_font = nullptr;
    std::wstring m_text;
    std::vector<Character*> m_characters;
    float m_x, m_y;
    Color m_color;

    void update();

public:
    Text(const std::wstring& text, float x, float y, Color color = Color::White);

    ~Text();

    void setFont(Font* font);

    void setPosition(float x, float y);
    void setColor(Color color);

    void draw(Shader* shader);
};

}// namespace tx