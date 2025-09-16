#include "grid.h"
#include "conway.h"
#include "settings.h"
#include <raygui.h>
#include <raylib.h>

static RenderTexture2D grid = (RenderTexture2D){0};
static Shader shader = (Shader){0};

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
    Texture2D conway = _conway_get().texture;
    float grid_size[2] = {(float)conway.width, (float)conway.height};
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
        conway,
        (Rectangle){0, 0, (float)conway.width, -(float)conway.height},
        (Rectangle){
            0, 0, (float)grid.texture.width, (float)grid.texture.height},
        (Vector2){0, 0},
        0.0f,
        WHITE);
    EndShaderMode();
    EndTextureMode();
}
