#include "enablevirtualterminal.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

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

    protected:
        std::string_view Glyph(int index) const { return m_glyphs(index); }

    private:
        const GridGlyphs &m_glyphs;
};

class Array : public BasicBox {
    public:
        explicit Array(const GridGlyphs &glyphs = ASCIIGridGlyphs) :
            BasicBox(glyphs) {}
        Array(std::string_view text, const GridGlyphs &glyphs = ASCIIGridGlyphs) :
            BasicBox(glyphs)
        {
            SetElements(text);
        }
        ~Array() override = default;

        std::basic_ostream<char> &Draw(
            std::basic_ostream<char> &out
        ) const {
            DrawSegmentedSpan(out, GridGlyphs::top);
            DrawElements(out);
            DrawSegmentedSpan(out, GridGlyphs::bottom);
            return out;
        }

        std::basic_ostream<char> &DrawSegmentedSpan(
            std::basic_ostream<char> &out,
            int row
        ) const {
            out << Glyph(row + GridGlyphs::left);
            if (auto length = m_elements.size(); length-- > 0) {
                DrawN(out, Glyph(row + GridGlyphs::col), m_cell_width);
                while (length-- > 0) {
                    out << Glyph(row + GridGlyphs::colsep);
                    DrawN(out, Glyph(row + GridGlyphs::col), m_cell_width);
                }
            }
            out << Glyph(row + GridGlyphs::right) << '\n';
            return out;
        }

        std::basic_ostream<char> &DrawElements(
            std::basic_ostream<char> &out
        ) const {
            out << Glyph(GridGlyphs::row + GridGlyphs::left);
            if (!m_elements.empty()) {
                out << m_elements.front();
                for (std::size_t i = 1; i < m_elements.size(); ++i) {
                    out << Glyph(GridGlyphs::row + GridGlyphs::colsep)
                        << m_elements[i];
                }
            }
            out << Glyph(GridGlyphs::row + GridGlyphs::right) << '\n';
            return out;
        }

        static std::basic_ostream<char> &DrawN(
            std::basic_ostream<char> &out,
            std::string_view text, int n
        ) {
            while (n-- > 0) { out << text; }
            return out;
        }

        void SetElements(std::string_view text) {
            m_elements.clear();
            for (const auto ch : text) {
                m_elements.emplace_back(1, ch);
            }
            m_elements.push_back("NUL");
            m_cell_width = std::max(1, WidthOfWidestElement());
            PadElements(m_cell_width);
        }

        int WidthOfWidestElement() const {
            int widest = 0;
            for (const auto &e : m_elements) {
                widest = std::max(widest, MeasureWidth(e));
            }
            return widest;
        }

        void PadElements(int width) {
            const auto &pad = Glyph(GridGlyphs::row + GridGlyphs::col);
            for (auto &e : m_elements) {
                const int excess = width - MeasureWidth(e);
                if (excess > 0) {
                    auto left = (excess + 1) / 2;
                    auto right = excess - left;
                    std::string padded;
                    while (left-- > 0) padded += pad;
                    padded += e;
                    while (right-- > 0) padded += pad;
                    using std::swap;
                    swap(e, padded);
                }
            }
        }

    private:
        static int MeasureWidth(std::string_view text) {
            // TODO:  Handle multiple UTF-8 code units.
            // TODO:  Handle terminal escape sequences.
            // TODO:  Handle non-spacing Unicode characters.
            return static_cast<int>(text.size());
        }

        std::vector<std::string> m_elements;
        int m_cell_width = 1;
};

int main() {
    EnableVirtualTerminal terminal;
    Array title("The TXT Project", UnicodeGridGlyphs);
    title.Draw(std::cout);
    return 0;
}
