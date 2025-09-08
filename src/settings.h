#pragma once

#define WINDOW_TITLE_MAX_SIZE 64

typedef struct {
    char window_title[WINDOW_TITLE_MAX_SIZE + 1];
    int window_res_x;
    int window_res_y;
    int window_target_fps;
} settings;

void _settings_load(int *errors);
settings _settings_get();
