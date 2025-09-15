#include "layout.h"
#include "grid.h"
#include "settings.h"
#include <raygui.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

static int rates_per_sec = STARTING_RATES_PER_SEC;

void _layout_render() {
    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
    settings s = _settings_get();
    _grid_render();

    // Grid
    DrawTexture(_grid_get().texture, (int)s.grid_x, (int)s.grid_y, WHITE);

    // Step button
    if (GuiButton(
            (Rectangle){
                s.step_button_x,
                s.step_button_y,
                s.step_button_w,
                s.step_button_h,
            },
            GuiIconText(ICON_PLAYER_NEXT, s.step_button_text))) {
        TraceLog(LOG_INFO, "Step clicked");
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
    char rates_label[3];
    sprintf(rates_label, "%d", rates_per_sec);
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
        TraceLog(LOG_INFO, "Next clicked");
    }
    if (GuiButton(
            (Rectangle){
                s.prev_button_x,
                s.prev_button_y,
                s.prev_button_w,
                s.prev_button_h,
            },
            GuiIconText(ICON_ARROW_UP_FILL, s.prev_button_text))) {
        TraceLog(LOG_INFO, "Previous clicked");
    }

    EndDrawing();
}
