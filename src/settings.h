#pragma once

#define TITLE_MAX_SIZE 64
#define BTNSTR_MAX_SIZE 32
#define TXTSTR_MAX_SIZE 64
#define MAX_PATTERN_COUNT 8

typedef struct {
    char window_title[TITLE_MAX_SIZE + 1];
    int window_res_x;
    int window_res_y;
    int window_target_fps;
    char pattern_paths[MAX_PATTERN_COUNT + 1][TXTSTR_MAX_SIZE + 1];
    int patterns_count;
    int grid_x;
    int grid_y;
    int grid_w;
    int grid_h;
    float step_button_x;
    float step_button_y;
    float step_button_w;
    float step_button_h;
    char step_button_text[BTNSTR_MAX_SIZE + 1];
    float play_button_x;
    float play_button_y;
    float play_button_w;
    float play_button_h;
    char play_button_text[BTNSTR_MAX_SIZE + 1];
    char pause_button_text[BTNSTR_MAX_SIZE + 1];
    float plus_button_x;
    float plus_button_y;
    float plus_button_w;
    float plus_button_h;
    float minus_button_x;
    float minus_button_y;
    float minus_button_w;
    float minus_button_h;
    char update_rate_text[TXTSTR_MAX_SIZE + 1];
    float rate_x;
    float rate_y;
    float max_rate;
    float min_rate;
    float rate_step;
    float next_button_x;
    float next_button_y;
    float next_button_w;
    float next_button_h;
    char next_button_text[BTNSTR_MAX_SIZE + 1];
    float prev_button_x;
    float prev_button_y;
    float prev_button_w;
    float prev_button_h;
    char prev_button_text[BTNSTR_MAX_SIZE + 1];
} settings;

void _settings_load(int *errors);
settings _settings_get();
