#include "conway.h"
#include "settings.h"
#include <raylib.h>

static RenderTexture2D conway = (RenderTexture2D){0};
static int cursor = 0;

static Shader rules_shader = (Shader){0};

void __init_pattern(int index) {
    settings s = _settings_get();

    Texture2D pattern = LoadTexture(s.pattern_paths[index]);
    conway = LoadRenderTexture(pattern.width, pattern.height);

    BeginTextureMode(conway);
    ClearBackground(BLACK);
    DrawTexturePro(
        pattern,
        (Rectangle){0, 0, (float)pattern.width, -(float)pattern.height},
        (Rectangle){0, 0, (float)pattern.width, (float)pattern.height},
        (Vector2){0, 0},
        0.0f,
        WHITE);
    EndTextureMode();

    UnloadTexture(pattern);
    cursor = index;
}

void __load_pattern(int index) {
    UnloadRenderTexture(conway);
    __init_pattern(index);
}

void _conway_init() {
    rules_shader = LoadShader(0, "res/conway-rules.frag");
    __init_pattern(0);
}

void _conway_stop() {
    UnloadRenderTexture(conway);
    UnloadShader(rules_shader);
}

RenderTexture2D _conway_get() {
    return conway;
}

void _conway_tick() {
    float grid_size[2] = {(float)conway.texture.width,
                          (float)conway.texture.height};
    int loc = GetShaderLocation(rules_shader, "gridSize");
    SetShaderValue(rules_shader, loc, grid_size, SHADER_UNIFORM_VEC2);

    BeginTextureMode(conway);
    ClearBackground(BLACK);
    BeginShaderMode(rules_shader);
    DrawTexture(conway.texture, 0, 0, WHITE);
    EndShaderMode();
    EndTextureMode();
}

void _conway_next_pattern() {
    __load_pattern((cursor + 1) % _settings_get().patterns_count);
}

void _conway_prev_pattern() {
    settings s = _settings_get();
    __load_pattern((cursor + s.patterns_count - 1) % s.patterns_count);
}

void _conway_toggle_at(int x, int y) {
}
