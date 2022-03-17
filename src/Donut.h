#ifndef DONUT_H_DEF
#define DONUT_H_DEF

#include <cmath>
#include "Terminal.h"

#define PI 3.14159265358979323846f

#define SCREENWIDTH 160
#define SCREENHEIGHT 20

class Donut {
private:
    float theta_spacing = 0.07f;
    float phi_spacing = 0.02f;

    float R1 = 1.0f;
    float R2 = 2.0f;
    float K2 = 5.0f;
    float K1 = SCREENWIDTH * K2 * 3.0f / (8.0f * (R1 + R2));

    float zBuffer[SCREENWIDTH * SCREENHEIGHT];
    char outputBuffer[SCREENWIDTH * SCREENHEIGHT];

    const char* brightness = ".,-~:;=!*#$@";

    Terminal terminal;

public:
    Donut() = default;

public:
    void CalculateDonut(float A, float B);
    void RenderDonut();
};

#endif