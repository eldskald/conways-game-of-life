#include "manager.h"
#include <raylib.h>

#ifdef WEB
#include <emscripten/emscripten.h>
#endif

int main() {

    if (_manager_start() != 0) return 1;

#ifdef WEB
    emscripten_set_main_loop(_manager_tick, 0, 1);
#else
    while (!WindowShouldClose()) {
        _manager_tick();
    }
#endif

    _manager_end();

    return 0;
}
