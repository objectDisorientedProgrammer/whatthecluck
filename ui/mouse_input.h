#ifndef MOUSE_INPUT_H
#define MOUSE_INPUT_H

#define DEBUG_TESTING 1

#include "input_device.h"
#include "raylib.h"
#if DEBUG_TESTING
#include <string>
#endif

namespace wtc
{
    namespace ui
    {
        class MouseInput : public InputDevice
        {
        public:
            MouseInput();
            void update() override;

            bool is_left_pressed();
            bool is_right_pressed();
            bool is_middle_pressed();
            
            #if DEBUG_TESTING
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
            #endif
        private:
            bool pressed_left;
            bool pressed_right;
            bool pressed_middle;
        };
    } // ui
} // wtc

#endif
