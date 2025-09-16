#include "layout.h"
#include "conway.h"
#include "grid.h"
#include "settings.h"
#include <raygui.h>
#include <raylib.h>
#include <raymath.h>

void _layout_render() {
    _grid_tick();
    _grid_render();
    RenderTexture2D grid = _grid_get();

    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
    settings s = _settings_get();

    // Grid
    DrawRectangle(s.grid_x,
                  s.grid_y,
                  s.grid_w + 1,
                  s.grid_h + 1,
                  GetColor(GuiGetStyle(DEFAULT, LINE_COLOR)));
    DrawTexture(grid.texture, s.grid_x, s.grid_y, WHITE);

    // Step button
    if (GuiButton(
            (Rectangle){
                s.step_button_x,
                s.step_button_y,
                s.step_button_w,
                s.step_button_h,
            },
            GuiIconText(ICON_PLAYER_NEXT, s.step_button_text))) {
        _conway_step();
    }

    // Play/Pause button
    const char *play_pause =
        _grid_is_playing() ? GuiIconText(ICON_PLAYER_PAUSE, s.pause_button_text)
                           : GuiIconText(ICON_PLAYER_PLAY, s.play_button_text);
    if (GuiButton(
            (Rectangle){
                s.play_button_x,
                s.play_button_y,
                s.play_button_w,
                s.play_button_h,
            },
            play_pause)) {
        _grid_toggle_playing();
    }

    // Update rate
    const float text_h = 32;
    const float text_w = 96;
    const float rates_h = 24;
    const float rates_w = 16;
    const char *rates_label = TextFormat("%.0f", _grid_get_ticks_per_sec());
    if (GuiButton(
            (Rectangle){
                s.plus_button_x,
                s.plus_button_y,
                s.plus_button_w,
                s.plus_button_h,
            },
            GuiIconText(ICON_ARROW_RIGHT, ""))) {
        _grid_increase_ticks_per_sec();
    }
    if (GuiButton(
            (Rectangle){
                s.minus_button_x,
                s.minus_button_y,
                s.minus_button_w,
                s.minus_button_h,
            },
            GuiIconText(ICON_ARROW_LEFT, ""))) {
        _grid_decrease_ticks_per_sec();
    }
    GuiLabel((Rectangle){s.rate_x, s.rate_y, text_w, text_h},
             s.update_rate_text);
    GuiLabel(
        (Rectangle){
            (s.minus_button_x + s.minus_button_w + s.plus_button_x - rates_w) /
                2,
            s.minus_button_y,
            rates_w,
            rates_h,
        },
        rates_label);

    // Patterns
    if (GuiButton(
            (Rectangle){
                s.next_button_x,
                s.next_button_y,
                s.next_button_w,
                s.next_button_h,
            },
            GuiIconText(ICON_ARROW_RIGHT_FILL, s.next_button_text))) {
        _conway_next_pattern();
        if (_grid_is_playing()) _grid_toggle_playing();
    }
    if (GuiButton(
            (Rectangle){
                s.prev_button_x,
                s.prev_button_y,
                s.prev_button_w,
                s.prev_button_h,
            },
            GuiIconText(ICON_ARROW_LEFT_FILL, s.prev_button_text))) {
        _conway_prev_pattern();
        if (_grid_is_playing()) _grid_toggle_playing();
    }

    EndDrawing();
}
