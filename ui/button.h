#ifndef BUTTON_H
#define BUTTON_H

#include "mouse_input.h"
#include "raylib.h"
#include <string>

namespace wtc
{
    namespace ui
    {

        enum class btnstate
        {
            none, idle, hover, press
        };

        class Button
        {
        public:
            Button() = default;
            Button(int x, int y, std::string text=std::string(""), int width=60, int height=30, bool enable=true);
            ~Button() {}

            btnstate update(MouseInput& mouse);

            void draw();

            bool is_selected(int x, int y);
            void set_enabled(bool enable) { benabled = enable; }
            bool is_enabled() { return benabled; }

            int get_x() { return bx; }
            void set_x(int x) { bx = x; }
            int get_width() { return bw; }
            int get_height() { return bh; }
            void set_height(int h) { bh = h; }

            void set_color(CLITERAL(Color) color) { bcolor = color; }
            void set_color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

        private:
            bool benabled;
            int bx, by, bw, bh;
            bool bautomatic_resize; // resize button dimensions to fit text
            std::string btext;
            int bfontsize; // font size (e.g. 10pt, 14pt, 26pt)
            int btextlength; // length of button text in pixels
            btnstate state;
            CLITERAL(Color) bcolor;
        };
    } // ui
} // wtc

#endif
