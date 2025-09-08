#include "settings.h"
#include <csvparse.h>
#include <raylib.h>
#include <stdlib.h>
#include <string.h>

static settings _settings;

void _settings_load(int *errors) {
    int csverror = 0;
    const char ***data = csvparse("data/settings.csv", &csverror);
    if (csverror != 0) {
        TraceLog(LOG_FATAL, "Failed to load project settings");
        errors++;
        return;
    }

    strlcpy(_settings.window_title, data[0][1], WINDOW_TITLE_MAX_SIZE);
    _settings.window_res_x = atoi(data[1][1]);
    _settings.window_res_y = atoi(data[1][2]);
    _settings.window_target_fps = atoi(data[2][1]);

    csvfree(data);
    TraceLog(LOG_INFO, "Project settings loaded successfully");
}

settings _settings_get() {
    return _settings;
}
