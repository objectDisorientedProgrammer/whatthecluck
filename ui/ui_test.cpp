#include "button.h"
#include "mouse_input.h"
#include "raylib.h"

#include <vector>

int main()
{
    std::string window_title{"UI testing"};
    InitWindow(1000, 650, window_title.c_str());

    constexpr int number_of_buttons{6};
    std::vector<wtc::ui::Button> btns;

    for (int i = 0; i < number_of_buttons; ++i)
    {
        btns.push_back(wtc::ui::Button(100+70*i, 100+40*i, std::to_string(i+1)));
    }

    wtc::ui::MouseInput m;

    SetTargetFPS(60);
    // main game loop
    while (!WindowShouldClose())
    {
        m.update();

        BeginDrawing();
        ClearBackground(WHITE);

        for (std::vector<wtc::ui::Button>::iterator i = btns.begin(); i != btns.end(); ++i)
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
