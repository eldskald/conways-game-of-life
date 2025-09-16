#version 100

precision mediump float;

varying vec2 fragTexCoord;
uniform sampler2D texture0;

uniform vec2 gridSize;

float Equal(float a, float b) {
    return step(0.1, abs(a - b));
}

float Evaluate(vec2 pixelOffset) {
    return texture2D(texture0, fragTexCoord + pixelOffset / gridSize).x;
}

float CountNeighbors() {
    return Evaluate(vec2(-1, 1)) +
           Evaluate(vec2(0, 1)) +
           Evaluate(vec2(1, 1)) +
           Evaluate(vec2(-1, 0)) +
           Evaluate(vec2(1, 0)) +
           Evaluate(vec2(-1, -1)) +
           Evaluate(vec2(0, -1)) +
           Evaluate(vec2(1, -1));
}

void main() {
    float res = 0.0;
    float live = Evaluate(vec2(0.0));
    float neighbors = CountNeighbors();

    // If is dead
    res += (1.0 - live) * Equal(neighbors, 3.0);

    // If is live
    res += live * (Equal(neighbors, 2.0) + Equal(neighbors, 3.0));

    gl_FragColor = vec4(res);
}
