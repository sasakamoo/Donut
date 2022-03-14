#include "Donut.h"

Donut::Donut() {
    sAppName = "DONUT TIME!!!";
}

void Donut::CalculateDonut(float A, float B) {
    // Reset output buffers
    for (int i = 0; i < ScreenWidth() * ScreenHeight(); i++) {
        zBuffer[i] = 0;
        outputBuffer[i] = 0;
    }

    // Precompute sin and cos of A and B
    float sinA = sin(A);
    float cosA = cos(A);
    float sinB = sin(B);
    float cosB = cos(B);

    // theta goes around the cross-sectional circle of a torus
    for (float theta = 0; theta < 2*PI; theta += theta_spacing) {
        // precompute sin and cos of theta
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);

        // phi goes around the center of revolution of a torus
        for (float phi = 0; phi < 2*PI; phi += phi_spacing) {
            // precompute sin and cos of phi
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            // X, Y coordinate of the circle, before revolving
            float circleX = R2 + R1 * cosTheta;
            float circleY = R1 * sinTheta;

            // Final 3D (X, Y, Z) coordinate after rotations
            float x = circleX*(cosB*cosPhi + sinA*sinB*sinPhi) - circleY*cosA*sinB;
            float y = circleX*(sinB*cosPhi - sinA*cosB*sinPhi) + circleY*cosA*cosB;
            float z = K2 + cosA*circleX*sinPhi + circleY*sinA;
            float ooz = 1 / z;

            // Project back into 2D space
            int xp = (int) (ScreenWidth()/2 + K1*ooz*x);
            int yp = (int) (ScreenHeight()/2 - K1*ooz*y);

            // Calculate Luminance (L ranges [-sqrt(2), +sqrt(2)])
            float L = cosPhi*cosTheta*sinB - cosA*cosTheta*sinPhi - sinA*sinTheta + cosB*(cosA*sinTheta - cosTheta*sinA*sinPhi);
            if (L > 0) {
                // Test against the zBuffer
                if (ooz > zBuffer[xp + yp * ScreenWidth()]) {
                    zBuffer[xp + yp * ScreenWidth()] = ooz;
                    int luminance_index = L * 8;
                    outputBuffer[xp + yp * ScreenWidth()] = luminance_index;
                }
            }
        }
    }
}

void Donut::RenderDonut() {
    for (int i = 0; i < ScreenWidth(); i++) {
        for (int j = 0; j < ScreenHeight(); j++) {
            int luminance = outputBuffer[i + j * ScreenWidth()];
            if (luminance > 0) {
                DrawCircle({ i, j }, luminance/8);
            }
        }
    }
}

bool Donut::OnUserCreate() {
    theta_spacing = 0.07f;
    phi_spacing = 0.02f;

    R1 = 1.0f;
    R2 = 2.0f;
    K2 = 5.0f;
    K1 = ScreenWidth() * K2 * 3 / (8 * (R1 + R2));

    zBuffer = new float[ScreenWidth() * ScreenHeight()]();
    outputBuffer = new int[ScreenWidth() * ScreenHeight()]();

    CalculateDonut(0, 0);
    
    return true;
}

bool Donut::OnUserUpdate(float fElapsedTime) {
    // float A = 0.0f, B = 0.0f;

    // if (A > 2*PI)
    //     A = 0;
    
    // if (B > 2*PI)
    //     B = 0;

    // CalculateDonut(A, B);

    // A += 0.1f;
    // B += 0.1f;

    Clear(olc::BLACK);
    RenderDonut();

    //std::this_thread::sleep_for(std::chrono::milliseconds(17));

    return true;
}

bool Donut::OnUserDestroy() {
    delete[] zBuffer;
    delete[] outputBuffer;

    return true;
}