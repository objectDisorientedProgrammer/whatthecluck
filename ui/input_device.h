#ifndef INPUT_DEVICE_H
#define INPUT_DEVICE_H

namespace wtc
{
    namespace ui
    {
        class InputDevice
        {
        public:
            virtual ~InputDevice() = default;

            int get_x() { return x; }
            int get_y() { return y; }

            virtual void update() = 0;

        protected:
            InputDevice(int initial_x, int initial_y);
            int x;
            int y;
        };
    } // ui
} // wtc

#endif
