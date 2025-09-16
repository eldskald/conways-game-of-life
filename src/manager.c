#include "manager.h"
#include "conway.h"
#include "grid.h"
#include "layout.h"
#include "settings.h"
#include <raygui.h>
#include <raylib.h>

int _manager_init() {
#ifndef DEV
    SetTraceLogLevel(LOG_NONE);
#endif
    int err = 0;
    _settings_load(&err);
    if (err != 0) return 1;

    InitWindow(_settings_get().window_res_x,
               _settings_get().window_res_y,
               _settings_get().window_title);
    SetExitKey(KEY_NULL);
    GuiLoadStyle("res/style_dark.rgs");
#ifndef WEB
    Image icon = LoadImage("res/icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);
    SetTargetFPS(_settings_get().window_target_fps);
#endif

    _grid_init();
    _conway_init();

    return 0;
}

void _manager_stop() {
    _grid_stop();
    _conway_stop();
    CloseWindow();
}

void _manager_tick() {
    _layout_render();
}
