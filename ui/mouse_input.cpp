#include "mouse_input.h"

namespace wtc
{
    namespace ui
    {
        MouseInput::MouseInput() : InputDevice{0, 0}
        {
            pressed_left = false;
            pressed_right = false;
            pressed_middle = false;
        }

        void MouseInput::update()
        {
            x = GetMouseX();
            y = GetMouseY();
            pressed_left = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_LEFT);
            pressed_right = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
            pressed_middle = IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) || IsMouseButtonDown(MOUSE_BUTTON_MIDDLE);
        }

        bool MouseInput::is_left_pressed()
        {
            return pressed_left;
        }

        bool MouseInput::is_right_pressed()
        {
            return pressed_right;
        }

        bool MouseInput::is_middle_pressed()
        {
            return pressed_middle;
        }
    } // ui
} // wtc
