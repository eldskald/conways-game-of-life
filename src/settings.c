#include "settings.h"
#include <csvparse.h>
#include <raylib.h>
#include <stdlib.h>

static settings _settings;

void _settings_load(int *errors) {
    int csverror = 0;
    const char ***data = csvparse("data/settings.csv", &csverror);
    if (csverror != 0) {
        TraceLog(LOG_FATAL, "Failed to load project settings");
        errors++;
        return;
    }

    // NOLINTBEGIN
    TextCopy(_settings.window_title, data[0][1]);
    TextCopy(_settings.step_button_text, data[8][1]);
    TextCopy(_settings.play_button_text, data[11][1]);
    TextCopy(_settings.pause_button_text, data[12][1]);
    TextCopy(_settings.update_rate_text, data[17][1]);
    TextCopy(_settings.next_button_text, data[24][1]);
    TextCopy(_settings.prev_button_text, data[27][1]);

    _settings.window_res_x = atoi(data[1][1]);
    _settings.window_res_y = atoi(data[1][2]);
    _settings.window_target_fps = atoi(data[2][1]);
    _settings.grid_x = atoi(data[3][1]);
    _settings.grid_y = atoi(data[3][2]);
    _settings.grid_w = atoi(data[4][1]);
    _settings.grid_h = atoi(data[4][2]);
    _settings.step_button_x = atoi(data[6][1]);
    _settings.step_button_y = atoi(data[6][2]);
    _settings.step_button_w = atoi(data[7][1]);
    _settings.step_button_h = atoi(data[7][2]);
    _settings.play_button_x = atoi(data[9][1]);
    _settings.play_button_y = atoi(data[9][2]);
    _settings.play_button_w = atoi(data[10][1]);
    _settings.play_button_h = atoi(data[10][2]);
    _settings.plus_button_x = atoi(data[13][1]);
    _settings.plus_button_y = atoi(data[13][2]);
    _settings.plus_button_w = atoi(data[14][1]);
    _settings.plus_button_h = atoi(data[14][2]);
    _settings.minus_button_x = atoi(data[15][1]);
    _settings.minus_button_y = atoi(data[15][2]);
    _settings.minus_button_w = atoi(data[16][1]);
    _settings.minus_button_h = atoi(data[16][2]);
    _settings.rate_x = atoi(data[18][1]);
    _settings.rate_y = atoi(data[18][2]);
    _settings.min_rate = atoi(data[19][1]);
    _settings.max_rate = atoi(data[19][2]);
    _settings.rate_step = atoi(data[20][1]);
    _settings.starting_rate = atoi(data[21][1]);
    _settings.next_button_x = atoi(data[22][1]);
    _settings.next_button_y = atoi(data[22][2]);
    _settings.next_button_w = atoi(data[23][1]);
    _settings.next_button_h = atoi(data[23][2]);
    _settings.prev_button_x = atoi(data[25][1]);
    _settings.prev_button_y = atoi(data[25][2]);
    _settings.prev_button_w = atoi(data[26][1]);
    _settings.prev_button_h = atoi(data[26][2]);
    _settings.cursor_width = atoi(data[28][1]);

    _settings.patterns_count = csvrowlen(data[5]) - 1;
    for (int i = 0; i < _settings.patterns_count; i++) {
        TextCopy(_settings.pattern_paths[i], data[5][i + 1]);
    }
    // NOLINTEND

    csvfree(data);
    TraceLog(LOG_INFO, "Project settings loaded successfully");
}

settings _settings_get() {
    return _settings;
}
