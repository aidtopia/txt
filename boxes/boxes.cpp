#include "enablevirtualterminal.h"

#include <iostream>
#include <string_view>

struct GridGlyphs {
    // The glyphs are a 5x5 array that hold the characters necessary to
    // draw each part of a box or table.
    //
    //          left    rowhdr      col     colsep      right
    // top
    // colhdr
    // row
    // rowsep
    // bottom
    static constexpr int top    = 0;
    static constexpr int colhdr = 5;
    static constexpr int row    = 10;
    static constexpr int rowsep = 15;
    static constexpr int bottom = 20;
    static constexpr int left   = 0;
    static constexpr int rowhdr = 1;
    static constexpr int col    = 2;
    static constexpr int colsep = 3;
    static constexpr int right  = 4;

    const std::string_view &operator()(int index) const {
        return glyphs[index];
    }
    std::string_view glyphs[25];
};

constexpr GridGlyphs ASCIIGridGlyphs = {
    "+", "+", "-", "+", "+",
    "+", "+", "-", "+", "+",
    "|", "|", " ", "|", "|",
    "|", "+", "-", "+", "|",
    "+", "+", "-", "+", "+"
};

constexpr GridGlyphs UnicodeGridGlyphs = {
    "\xE2\x94\x8C", "\xE2\x94\xAC", "\xE2\x94\x80", "\xE2\x94\xAC", "\xE2\x94\x90",
    "\xE2\x94\x9C", "\xE2\x94\xBC", "\xE2\x94\x80", "\xE2\x94\xBC", "\xE2\x94\xA4",
    "\xE2\x94\x82", "\xE2\x94\x82", " ",            "\xE2\x94\x82", "\xE2\x94\x82",
    "\xE2\x94\x82", "\xE2\x94\xBC", "\xE2\x94\x80", "\xE2\x94\xBC", "\xE2\x94\x82",
    "\xE2\x94\x94", "\xE2\x94\xB4", "\xE2\x94\x80", "\xE2\x94\xB4", "\xE2\x94\x98"
};

class BasicBox {
    public:
        explicit BasicBox(const GridGlyphs &glyphs = ASCIIGridGlyphs) : m_glyphs(glyphs) {}
        virtual ~BasicBox() = default;

        std::basic_ostream<char> &Draw(
            std::basic_ostream<char> &out,
            std::string_view text
        ) const {
            out << m_glyphs(GridGlyphs::top + GridGlyphs::left);
            for (std::string_view::size_type i = 0; i < text.size(); ++i) {
                out << m_glyphs(GridGlyphs::top + GridGlyphs::col);
            }
            out << m_glyphs(GridGlyphs::top + GridGlyphs::right) << '\n';
            out << m_glyphs(GridGlyphs::row + GridGlyphs::left)
                << text
                << m_glyphs(GridGlyphs::row + GridGlyphs::right) << '\n';
            out << m_glyphs(GridGlyphs::bottom + GridGlyphs::left);
            for (std::string_view::size_type i = 0; i < text.size(); ++i) {
                out << m_glyphs(GridGlyphs::bottom + GridGlyphs::col);
            }
            out << m_glyphs(GridGlyphs::bottom + GridGlyphs::right) << '\n';
            return out;
        }

    private:
        const GridGlyphs &m_glyphs;
};

int main() {
    EnableVirtualTerminal terminal;
    BasicBox box(UnicodeGridGlyphs);
    box.Draw(std::cout, "Hello, World!");
    return 0;
}
