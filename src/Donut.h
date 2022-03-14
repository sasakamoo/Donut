#ifndef DONUT_H_DEF
#define DONUT_H_DEF

#define PI 3.14159265358979323846

#include "pge/olcPixelGameEngine.h"
#include "utils/utils.h"

class Donut : public olc::PixelGameEngine {
private:
    float theta_spacing;
    float phi_spacing;

    float R1;
    float R2;
    float K1;
    float K2;

    float* zBuffer;
    int* outputBuffer;

private:
    void CalculateDonut(float A, float B);
    void RenderDonut();

public:
    Donut();

public:
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    bool OnUserDestroy() override;
};

#endif