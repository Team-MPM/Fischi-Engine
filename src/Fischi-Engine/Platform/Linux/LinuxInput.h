#include "Core/Core.h"
#include "Core/KeyCodes.h"

namespace FischiEngine {
    class LinuxInput {
    public:
        static KeyCode ParseX11KeyCode(int code);
        static KeyCode ParseWaylandKeyCode(int code);
    };
}