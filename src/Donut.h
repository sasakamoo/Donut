#ifndef DONUT_H_DEF
#define DONUT_H_DEF

#define PI 3.14159265358979323846

#define SCREENWIDTH 20
#define SCREENHEIGHT 5

class Donut {
private:
    float theta_spacing = 0.07f;
    float phi_spacing = 0.02f;

    float R1 = 1.0f;
    float R2 = 2.0f;
    float K2 = 5.0f;
    float K1 = SCREENWIDTH * K2 * 3 / (8 * (R1 + R2));

    float zBuffer[SCREENWIDTH * SCREENHEIGHT];
    char outputBuffer[SCREENWIDTH * SCREENHEIGHT];

    char brightness[13] = ".,-~:;=!*#$@";

public:
    Donut() = default;

public:
    void CalculateDonut(float A, float B);
    void RenderDonut();
};

#endif