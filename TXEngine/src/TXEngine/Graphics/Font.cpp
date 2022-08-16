#include <stdexcept>
#include <memory>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <TXEngine/Graphics/Font.hpp>

namespace tx
{

struct T {
    FT_Library ft;

    T()
    {
        if (FT_Init_FreeType(&ft))
            throw std::runtime_error("ERROR::FREETYPE: Could not init FreeType Library");
    }

    ~T()
    {
        FT_Done_FreeType(ft);
    }
};

static auto t = std::make_unique<T>();

Font::Font(int size)
    : m_size(size)
{
}

void Font::loadFromFile(const std::string& filename)
{
    FT_Face face;

    if (FT_New_Face(t->ft, filename.c_str(), 0, &face))
        throw std::runtime_error("ERROR::FREETYPE: Failed to load font");

    m_face = face;

    update();
}

void Font::setSize(int size)
{
    m_size = size;

    update();
}

void Font::update()
{
    if (m_face != nullptr) {
        FT_Set_Pixel_Sizes(reinterpret_cast<FT_Face>(m_face), 0, m_size);
    }
}

void* Font::getFace()
{
    return m_face;
}

Font::~Font()
{
    FT_Done_Face(static_cast<FT_Face>(m_face));
}

int Font::getSize()
{
    return m_size;
}

}// namespace tx
