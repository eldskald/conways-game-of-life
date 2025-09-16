#pragma once
#include <raylib.h>

void _conway_init();
void _conway_stop();
RenderTexture2D _conway_get();
void _conway_tick();
void _conway_toggle_at(int x, int y);
void _conway_next_pattern();
void _conway_prev_pattern();
