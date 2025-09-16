#include "grid.h"
#include "conway.h"
#include "settings.h"
#include <raygui.h>
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

static RenderTexture2D grid = (RenderTexture2D){0};
static Shader shader = (Shader){0};

static float time = 0.0f;
static float ticks_per_sec = STARTING_TICKS_PER_SEC;
static bool is_playing = false;

void _grid_init() {
    settings s = _settings_get();
    grid = LoadRenderTexture(s.grid_w, s.grid_h);
    shader = LoadShader(0, "res/grid.frag");
}

void _grid_stop() {
    UnloadRenderTexture(grid);
    UnloadShader(shader);
}

RenderTexture2D _grid_get() {
    return grid;
}

void _grid_render() {
    Vector2 conway_res = _conway_get_size();
    float grid_size[2] = {conway_res.x, conway_res.y};
    int loc = GetShaderLocation(shader, "gridSize");
    SetShaderValue(shader, loc, grid_size, SHADER_UNIFORM_VEC2);

    float texture_size[2] = {(float)grid.texture.width,
                             (float)grid.texture.height};
    loc = GetShaderLocation(shader, "textureSize");
    SetShaderValue(shader, loc, texture_size, SHADER_UNIFORM_VEC2);

    const float max_col = 255.0f;
    Color line_c = GetColor(GuiGetStyle(DEFAULT, LINE_COLOR));
    Color text_c = GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL));
    float grid_arr[4] = {(float)line_c.r / max_col,
                         (float)line_c.g / max_col,
                         (float)line_c.b / max_col,
                         (float)line_c.a / max_col};
    float dead_arr[4] = {(float)text_c.r / max_col,
                         (float)text_c.g / max_col,
                         (float)text_c.b / max_col,
                         (float)text_c.a / max_col};
    float live_arr[4] = {0.0f};

    loc = GetShaderLocation(shader, "gridColor");
    SetShaderValue(shader, loc, grid_arr, SHADER_UNIFORM_VEC4);
    loc = GetShaderLocation(shader, "liveColor");
    SetShaderValue(shader, loc, live_arr, SHADER_UNIFORM_VEC4);
    loc = GetShaderLocation(shader, "deadColor");
    SetShaderValue(shader, loc, dead_arr, SHADER_UNIFORM_VEC4);

    BeginTextureMode(grid);
    BeginShaderMode(shader);
    ClearBackground(BLACK);
    DrawTexturePro(
        _conway_get_texture(),
        (Rectangle){0, 0, conway_res.x, -conway_res.y},
        (Rectangle){
            0, 0, (float)grid.texture.width, (float)grid.texture.height},
        (Vector2){0, 0},
        0.0f,
        WHITE);
    EndShaderMode();
    EndTextureMode();
}

float _grid_get_ticks_per_sec() {
    return ticks_per_sec;
}

void _grid_increase_ticks_per_sec() {
    settings s = _settings_get();
    ticks_per_sec = Clamp(ticks_per_sec + s.rate_step, s.min_rate, s.max_rate);
}

void _grid_decrease_ticks_per_sec() {
    settings s = _settings_get();
    ticks_per_sec = Clamp(ticks_per_sec - s.rate_step, s.min_rate, s.max_rate);
}

bool _grid_is_playing() {
    return is_playing;
}

void _grid_toggle_playing() {
    is_playing = !is_playing;
}

void _grid_tick() {
    if (!is_playing) return;

    time += GetFrameTime();
    if (time >= 1.0f / ticks_per_sec) {
        _conway_step();
        time -= 1.0f / ticks_per_sec;
    }
}

Vector2 _grid_get_cell_size() {
    settings s = _settings_get();
    Vector2 conway_size = _conway_get_size();
    return (Vector2){(float)s.grid_w / conway_size.x,
                     (float)s.grid_h / conway_size.y};
}

Vector2 _grid_get_cursor() {
    settings s = _settings_get();
    Vector2 cursor = GetMousePosition();
    int x = (int)cursor.x;
    int y = (int)cursor.y;
    bool is_on_grid = (x >= s.grid_x) && (x <= s.grid_x + s.grid_w) &&
                      (y >= s.grid_y) && (y <= s.grid_y + s.grid_h);
    if (is_on_grid) {
        Vector2 cell_size = _grid_get_cell_size();
        int coords_x = ((int)cursor.x - s.grid_x) / (int)cell_size.x;
        int coords_y = ((int)cursor.y - s.grid_y) / (int)cell_size.y;
        return (Vector2){(float)coords_x, (float)coords_y};
    }
    return (Vector2){-1.0f, -1.0f};
}
