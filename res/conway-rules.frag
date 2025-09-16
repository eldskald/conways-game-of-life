#version 100

precision mediump float;

varying vec2 fragTexCoord;
uniform sampler2D texture0;

uniform vec2 gridSize;

float Equal(float a, float b) {
    return step(abs(a - b), 0.01);
}

// Out of bounds pixels are always dead
float Evaluate(vec2 pixelOffset) {
    float res = 0.0;
    vec2 target = fragTexCoord + pixelOffset / gridSize;
    float sample = texture2D(texture0, target).x;

    float upperBound = min(1.0, step(1.0, target.x) + step(1.0, target.y));
    float lowerBound = min(1.0, step(target.x, 0.0) + step(target.y, 0.0));
    float bounded = 1.0 - min(1.0, upperBound + lowerBound);

    return bounded * sample;
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
    res += live * min(Equal(neighbors, 2.0) + Equal(neighbors, 3.0), 1.0);

    gl_FragColor = vec4(res);
}
