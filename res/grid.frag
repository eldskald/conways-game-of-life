#version 100

precision mediump float;

varying vec2 fragTexCoord;
uniform sampler2D texture0;

uniform vec2 gridSize;
uniform vec2 textureSize;
uniform vec4 gridColor;
uniform vec4 liveColor;
uniform vec4 deadColor;

float IsGridLine() {
    vec2 cellSize = textureSize / gridSize;
    vec2 pixCoords = floor(fragTexCoord * textureSize);
    vec2 cellCoords = mod(pixCoords, cellSize);
    return 1.0 - min(cellCoords.x * cellCoords.y, 1.0);
}

void main() {
    vec4 col = vec4(0.0);
    float live = texture2D(texture0, fragTexCoord).x;
    float grid = IsGridLine();

    col += grid * gridColor;
    col += (1.0 - grid) * live * liveColor;
    col += (1.0 - grid) * (1.0 - live) * deadColor;

    gl_FragColor = col;
}
