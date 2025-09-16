#include "conway.h"
#include "settings.h"
#include <raylib.h>
#include <raymath.h>

#define EXTRA_CELLS_FACTOR 2
#define TWO 2.0f

static RenderTexture2D conway = (RenderTexture2D){0};
static RenderTexture2D buffer = (RenderTexture2D){0};
static RenderTexture2D final = (RenderTexture2D){0};
static int cursor = 0;

static Shader rules_shader = (Shader){0};

void __init_pattern(int index) {
    settings s = _settings_get();

    Texture2D pattern = LoadTexture(s.pattern_paths[index]);
    Vector2 pattern_res =
        (Vector2){(float)pattern.width, (float)pattern.height};
    Vector2 buffer_size = Vector2Scale(pattern_res, EXTRA_CELLS_FACTOR);
    Vector2 conway_orig = (Vector2){(buffer_size.x - pattern_res.x) / TWO,
                                    (buffer_size.y - pattern_res.y) / TWO};

    conway = LoadRenderTexture((int)buffer_size.x, (int)buffer_size.y);
    buffer = LoadRenderTexture((int)buffer_size.x, (int)buffer_size.y);
    final = LoadRenderTexture((int)pattern_res.x, (int)pattern_res.y);

    BeginTextureMode(conway);
    ClearBackground(BLACK);
    DrawTexturePro(
        pattern,
        (Rectangle){0, 0, pattern_res.x, -pattern_res.y},
        (Rectangle){conway_orig.x, conway_orig.y, pattern_res.x, pattern_res.y},
        (Vector2){0, 0},
        0.0f,
        WHITE);
    EndTextureMode();

    BeginTextureMode(final);
    ClearBackground(BLACK);
    DrawTexturePro(pattern,
                   (Rectangle){0, 0, pattern_res.x, -pattern_res.y},
                   (Rectangle){0, 0, pattern_res.x, pattern_res.y},
                   (Vector2){0, 0},
                   0.0f,
                   WHITE);
    EndTextureMode();

    UnloadTexture(pattern);
    cursor = index;
}

void __load_pattern(int index) {
    UnloadRenderTexture(conway);
    UnloadRenderTexture(buffer);
    UnloadRenderTexture(final);
    __init_pattern(index);
}

void _conway_init() {
    rules_shader = LoadShader(0, "res/conway-rules.frag");
    __init_pattern(0);
}

void _conway_stop() {
    UnloadRenderTexture(conway);
    UnloadRenderTexture(buffer);
    UnloadRenderTexture(final);
    UnloadShader(rules_shader);
}

Vector2 _conway_get_size() {
    return (Vector2){(float) final.texture.width, (float) final.texture.height};
}

void _conway_step() {
    float buffer_size[2] = {(float)conway.texture.width,
                            (float)conway.texture.height};
    int loc = GetShaderLocation(rules_shader, "gridSize");
    SetShaderValue(rules_shader, loc, buffer_size, SHADER_UNIFORM_VEC2);

    BeginTextureMode(buffer);
    ClearBackground(BLACK);
    DrawTexture(conway.texture, 0, 0, WHITE);
    EndTextureMode();

    BeginTextureMode(conway);
    ClearBackground(BLACK);
    BeginShaderMode(rules_shader);
    DrawTexture(buffer.texture, 0, 0, WHITE);
    EndShaderMode();
    EndTextureMode();

    Vector2 final_size = _conway_get_size();
    Vector2 conway_orig = (Vector2){(buffer_size[0] - final_size.x) / TWO,
                                    (buffer_size[1] - final_size.y) / TWO};
    BeginTextureMode(final);
    ClearBackground(BLACK);
    DrawTexturePro(
        conway.texture,
        (Rectangle){conway_orig.x, conway_orig.y, final_size.x, -final_size.y},
        (Rectangle){0, 0, final_size.x, final_size.y},
        (Vector2){0, 0},
        0.0f,
        WHITE);
    EndTextureMode();
}

void _conway_next_pattern() {
    __load_pattern((cursor + 1) % _settings_get().patterns_count);
}

void _conway_prev_pattern() {
    settings s = _settings_get();
    __load_pattern((cursor + s.patterns_count - 1) % s.patterns_count);
}

Texture2D _conway_get_texture() {
    return final.texture;
}

void _conway_toggle_at(int x, int y) {
}
