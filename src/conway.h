#pragma once
#include <raylib.h>

void _conway_init();
void _conway_stop();

Vector2 _conway_get_size();
Texture2D _conway_get_texture();

void _conway_step();
void _conway_next_pattern();
void _conway_prev_pattern();

void _conway_toggle_at(int x, int y);
