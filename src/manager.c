#include "manager.h"
#include "settings.h"
#include "layout.h"
#include <raylib.h>
#include <raygui.h>

int _manager_start() {
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

    return 0;
}

void _manager_end() {
    CloseWindow();
}

void _manager_tick() {
    _layout_render();
}
