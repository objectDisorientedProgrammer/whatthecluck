#include "button.h"

#define TESTING 0

Button::Button(int x, int y, std::string text=std::string(""), int width=60, int height=30, bool enable=true) : bx(x), by(y), btext(text), bw(width), bh(height), benabled(enable)
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
    bcolor = CLITERAL(Color){ 102, 191, 255, 200 };
    bautomatic_resize = false;
}

#if TESTING

#include <vector>

int main()
{
    std::string window_title{"UI testing"};
    InitWindow(1000, 650, window_title.c_str());

    constexpr int number_of_buttons{6};
    std::vector<Button> btns;

    for (int i = 0; i < number_of_buttons; ++i)
    {
        btns.push_back(Button(100+70*i, 100+40*i, std::to_string(i+1)));
    }

    MouseInfo m;

    SetTargetFPS(60);
    // main game loop
    while (!WindowShouldClose())
    {
        m.update();

        BeginDrawing();
        ClearBackground(WHITE);

        for (std::vector<Button>::iterator i = btns.begin(); i != btns.end(); ++i)
        {
            i->update(m);
            i->draw();
        }

        m.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
#endif
