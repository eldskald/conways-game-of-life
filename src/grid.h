#pragma once
#include <raylib.h>
#include <stdbool.h>

void _grid_init();
void _grid_stop();
RenderTexture2D _grid_get();
void _grid_render();
void _grid_tick();

float _grid_get_ticks_per_sec();
void _grid_increase_ticks_per_sec();
void _grid_decrease_ticks_per_sec();
bool _grid_is_playing();
void _grid_toggle_playing();

Vector2 _grid_get_cell_size();
Vector2 _grid_get_cursor();
