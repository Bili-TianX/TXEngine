#include <stdexcept>

#include <glad/glad.h>
#include <freetype/freetype.h>

#include <TXEngine/Graphics/Text.hpp>

namespace tx
{

Text::Text(const std::wstring& text, float x, float y, Color color)
    : m_text(text)
    , m_x(x)
    , m_y(y)
    , m_color(color)
{
}

void Text::setFont(Font* font)
{
    m_font = font;

    update();
}

void Text::update()
{
    if (m_font == nullptr)
        return;

    if (!m_characters.empty()) {
        for (const auto& item : m_characters) {
            delete item;
        }

        m_characters.clear();
    }

    auto face = reinterpret_cast<FT_Face>(m_font->getFace());

    double x = m_x;
    float y  = m_y;
    int size = m_font->getSize();

    for (const auto& item : m_text) {
        if (item == '\n') {
            x = m_x;
            y += size;

            continue;
        }
        else if (item == '\t') {
            if (FT_Load_Char(face, ' ', FT_LOAD_RENDER))
                throw std::runtime_error("ERROR::FREETYTPE: Failed to load Glyph");
            const auto& bitmap = face->glyph->bitmap;

            x += (face->glyph->advance.x >> 6) * 4;
            continue;
        }

        if (FT_Load_Char(face, item, FT_LOAD_RENDER))
            throw std::runtime_error("ERROR::FREETYTPE: Failed to load Glyph");
        const auto& bitmap = face->glyph->bitmap;

        // Texture
        auto* texture = new Texture();
        texture->loadCharTexture(bitmap.buffer, bitmap.width, bitmap.rows);

        // Char
        auto* c = new Character(texture, x + face->glyph->bitmap_left, size + y - face->glyph->bitmap_top, bitmap.width,
                                bitmap.rows, m_color);
        m_characters.push_back(c);

        x += (face->glyph->advance.x >> 6);
    }
}

Text::~Text()
{
    for (const auto& item : m_characters) {
        delete item->texture;
    }
}

void Text::draw(Shader* shader)
{
    glUniform1i(shader->getUniform("isText"), 1);
    for (const auto& item : m_characters) {
        item->draw(shader);
    }
    glUniform1i(shader->getUniform("isText"), 0);
}
void Text::setPosition(float x, float y)
{
    m_x = x;
    m_y = y;
    update();
}

void Text::setColor(Color color)
{
    m_color = color;
    update();
}

Text::Character::Character(Texture* texture, float x, float y, float width, float height, Color color)
    : texture(texture)
    , x(y)
    , y(y)
    , width(width)
    , height(height)
    , color(color)
{
    shape = new RectangleShape(x, y, width, height, color, texture);
}

void Text::Character::draw(Shader* shader) const
{
    texture->bind();

    shape->draw(shader);

    texture->unbind();
}

Text::Character::~Character()
{
    delete texture;
    delete shape;
}

}// namespace tx
