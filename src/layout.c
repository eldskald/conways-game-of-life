#include "layout.h"
#include "conway.h"
#include "grid.h"
#include "settings.h"
#include <raygui.h>
#include <raylib.h>
#include <raymath.h>

static int rates_per_sec = STARTING_RATES_PER_SEC;

void _layout_render() {
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
        _conway_tick();
    }

    // Play button
    if (GuiButton(
            (Rectangle){
                s.play_button_x,
                s.play_button_y,
                s.play_button_w,
                s.play_button_h,
            },
            GuiIconText(ICON_PLAYER_PLAY, s.play_button_text))) {
        TraceLog(LOG_INFO, "Play clicked");
    }

    // Update rate
    const float text_h = 32;
    const float text_w = 96;
    const float rates_h = 24;
    const float rates_w = 16;
    const char *rates_label = TextFormat("%d", rates_per_sec);
    if (GuiButton(
            (Rectangle){
                s.plus_button_x,
                s.plus_button_y,
                s.plus_button_w,
                s.plus_button_h,
            },
            GuiIconText(ICON_ARROW_RIGHT, ""))) {
        rates_per_sec = (int)Clamp((float)(rates_per_sec + s.rate_step),
                                   (float)s.min_rate,
                                   (float)s.max_rate);
    }
    if (GuiButton(
            (Rectangle){
                s.minus_button_x,
                s.minus_button_y,
                s.minus_button_w,
                s.minus_button_h,
            },
            GuiIconText(ICON_ARROW_LEFT, ""))) {
        rates_per_sec = (int)Clamp((float)(rates_per_sec - s.rate_step),
                                   (float)s.min_rate,
                                   (float)s.max_rate);
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
            GuiIconText(ICON_ARROW_DOWN_FILL, s.next_button_text))) {
        _conway_next_pattern();
    }
    if (GuiButton(
            (Rectangle){
                s.prev_button_x,
                s.prev_button_y,
                s.prev_button_w,
                s.prev_button_h,
            },
            GuiIconText(ICON_ARROW_UP_FILL, s.prev_button_text))) {
        _conway_prev_pattern();
    }

    EndDrawing();
}
