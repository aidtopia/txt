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

        std::basic_ostream<char> &DrawArray(
            std::basic_ostream<char> &out,
            std::string_view text
        ) const {
            DrawSegmentedSpan(out, GridGlyphs::top, text.size());
            DrawSegmentedSpan(out, text);
            DrawSegmentedSpan(out, GridGlyphs::bottom, text.size());
            return out;
        }

        std::basic_ostream<char> &DrawSegmentedSpan(
            std::basic_ostream<char> &out,
            int row,
            std::size_t length
        ) const {
            out << m_glyphs(row + GridGlyphs::left);
            if (length-- > 0) {
                out << m_glyphs(row + GridGlyphs::col);
                while (length-- > 0) {
                    out << m_glyphs(row + GridGlyphs::colsep)
                        << m_glyphs(row + GridGlyphs::col);
                }
            }
            out << m_glyphs(row + GridGlyphs::right) << '\n';
            return out;
        }

        std::basic_ostream<char> &DrawSegmentedSpan(
            std::basic_ostream<char> &out,
            std::string_view text
        ) const {
            out << m_glyphs(GridGlyphs::row + GridGlyphs::left);
            if (!text.empty()) {
                out << text.front();
                for (std::string_view::size_type i = 1; i < text.size(); ++i) {
                    out << m_glyphs(GridGlyphs::row + GridGlyphs::colsep) << text[i];
                }
            }
            out << m_glyphs(GridGlyphs::row + GridGlyphs::right) << '\n';
            return out;
        }


    private:
        const GridGlyphs &m_glyphs;
};

int main() {
    EnableVirtualTerminal terminal;
    BasicBox box(UnicodeGridGlyphs);
    box.DrawArray(std::cout, "The TXT Project");
    return 0;
}
