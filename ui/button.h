#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include <string>

class MouseInfo
{
public:
    // MouseInfo();
    // ~MouseInfo();

    int x;
    int y;
    bool pressed_left;
    bool pressed_right;
    bool pressed_middle;

    //const MouseInfo& get() { return this; }
    void update()
    {
        x=GetMouseX();
        y=GetMouseY();
        pressed_left=IsMouseButtonPressed(MOUSE_BUTTON_LEFT)||IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        pressed_right=IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)||IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
        pressed_middle = IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)||IsMouseButtonDown(MOUSE_BUTTON_MIDDLE);
    }

    void draw()
    {
        // debugging info
        std::string dbg{std::string("x:")+std::to_string(x)+std::string(" y:")+std::to_string(y)+std::string(" ")};
        if (pressed_left)
        {
            dbg += std::string("LEFT");
        }
        else if (pressed_right)
        {
            dbg += std::string("RGHT");
        }
        else if (pressed_middle)
        {
            dbg += std::string("MIDL");
        }
        DrawText(dbg.c_str(), 5, 630, 16, BLACK);
    }
    
};



enum class btnstate
{
    none, idle, hover, press
};

class Button
{
public:
    Button() = default;
    Button(int x, int y, std::string text, int width, int height, bool enable);
    ~Button() {}
    
    btnstate update(MouseInfo& mouse) // TODO generalize as 'inputinfo' or similar...
    {
        unsigned char alpha;
        // mouse within button bounds
        if (bx < mouse.x && mouse.x < bx + bw && by < mouse.y && mouse.y < by + bh)
        {
            state = btnstate::hover;
            alpha = 150; // TODO change alpha reductions to RGB reductions
            if (mouse.pressed_left)
            {
                state = btnstate::press;
                alpha = 100;
            }
        }
        else
        {
            state = btnstate::idle;
            alpha = 200; // default for btnstate::idle/none
        }

        bcolor.a = alpha;

        return state;
    }
    void draw()
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
    bool is_pressed(int x, int y)
    {
        return (bx < x && x < bx + bw && by < y && y < by + bh);
    }
    void set_enabled(bool enable) { benabled = enable; }
    bool is_enabled() { return benabled; }

    int get_x() { return bx; }
    void set_x(int x) { bx = x; }
    int get_width() { return bw; }
    int get_height() { return bh; }
    void set_height(int h) { bh = h; }

    void set_color(CLITERAL(Color) color) { bcolor = color; }
    void set_color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
    {
        bcolor.r = red;
        bcolor.g = green;
        bcolor.b = blue;
        bcolor.a = alpha;
    }

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

#endif
