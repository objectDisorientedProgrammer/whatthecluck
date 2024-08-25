#include "input_device.h"

namespace wtc
{
    namespace ui
    {
        InputDevice::InputDevice(int initial_x, int initial_y)
        {
            x = initial_x >= 0 ? initial_x : 0;
            y = initial_y >= 0 ? initial_y : 0;
        }
    } // ui
} // wtc
