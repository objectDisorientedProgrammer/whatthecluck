#include "button.h"

namespace wtc
{
    namespace ui
    {
        Button::Button(int x, int y, std::string text, int width, int height, bool enable) : bx(x), by(y), btext(text), bw(width), bh(height), benabled(enable)
        {
            // determine button text length
            bfontsize = 11;
            if (!btext.empty())
            {
                btextlength = MeasureText(btext.c_str(), bfontsize);
            }
            else
                btextlength = 0;

            state = btnstate::none;
            bcolor = CLITERAL(Color){ 102, 161, 205, 255 };
            bautomatic_resize = false;
        }

        btnstate Button::update(MouseInput& mouse)
        {
            unsigned char alpha;
            // mouse within button bounds
            if (is_selected(mouse.get_x(), mouse.get_y()))
            {
                state = btnstate::hover;
                alpha = 255;//200; // TODO change alpha reductions to RGB reductions
                bcolor.r = 102;//52;
                bcolor.g = 161;//141;
                bcolor.b = 225;
                if (mouse.is_left_pressed())
                {
                    state = btnstate::press;
                    alpha = 255;//150;
                    bcolor.r = 102;//2;
                    bcolor.g = 161;//91;
                    bcolor.b = 255;//155;
                }
            }
            else
            {
                state = btnstate::idle;
                alpha = 255; // default for btnstate::idle/none
                bcolor.r = 102;//102, 191, 255
                bcolor.g = 161;
                bcolor.b = 205;
            }

            bcolor.a = alpha;

            return state;
        }

        void Button::draw()
        {
            if (bautomatic_resize)
            {
                // resize button to fit text
                if (btextlength > bw)
                {
                    bw = btextlength + 5;
                }
                if (btextlength > bh)
                {
                    bh = btextlength + 5;
                }
            }

            // TODO color change for enabled/disabled

            DrawRectangleRounded({static_cast<float>(bx), static_cast<float>(by), static_cast<float>(bw), static_cast<float>(bh)}, 0.6f, 10, bcolor);
            if (!btext.empty())
                DrawText(btext.c_str(), bx + bw / 2 - btextlength / 2, by + bh / 3, bfontsize, BLACK);
        }

        bool Button::is_selected(int x, int y)
        {
            return (bx < x && x < bx + bw && by < y && y < by + bh);
        }

        void Button::set_color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
        {
            bcolor.r = red;
            bcolor.g = green;
            bcolor.b = blue;
            bcolor.a = alpha;
        }
    } // ui
} // wtc
