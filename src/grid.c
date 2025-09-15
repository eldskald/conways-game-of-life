#include "grid.h"
#include "conway.h"
#include "settings.h"
#include <raylib.h>
#include <raygui.h>

static RenderTexture2D grid = (RenderTexture2D){0};
static Shader shader = (Shader){0};

void _grid_init() {
    settings s = _settings_get();
    TraceLog(LOG_INFO, "bosta fezes %d, %d", s.grid_w, s.grid_h);
    grid = LoadRenderTexture((int)s.grid_w, (int)s.grid_h);
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

    Color grid_color = GetColor(GuiGetStyle(DEFAULT, LINE_COLOR));
    Color live_color = GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL));
    Color dead_color = BLANK;
    loc = GetShaderLocation(shader, "gridColor");
    SetShaderValue(shader, loc, &grid_color, SHADER_UNIFORM_VEC4);
    loc = GetShaderLocation(shader, "liveColor");
    SetShaderValue(shader, loc, &live_color, SHADER_UNIFORM_VEC4);
    loc = GetShaderLocation(shader, "deadColor");
    SetShaderValue(shader, loc, &dead_color, SHADER_UNIFORM_VEC4);

    BeginTextureMode(grid);
    BeginShaderMode(shader);
    DrawTexturePro(
        conway,
        (Rectangle){0, 0, (float)conway.width, (float)conway.height},
        (Rectangle){
            0, 0, (float)grid.texture.width, (float)grid.texture.height},
        (Vector2){0, 0},
        0.0f,
        WHITE);
    EndShaderMode();
    EndTextureMode();
}
