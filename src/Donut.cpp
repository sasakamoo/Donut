#include "Donut.h"
#include <iostream>

void Donut::CalculateDonut(float A, float B) {
    // Reset output buffers
    for (int i = 0; i < SCREENWIDTH * SCREENHEIGHT; i++) {
        zBuffer[i] = 0.0f;
        outputBuffer[i] = ' ';
    }

    // Precompute sin and cos of A and B
    float sinA = std::sin(A);
    float cosA = std::cos(A);
    float sinB = std::sin(B);
    float cosB = std::cos(B);

    // theta goes around the cross-sectional circle of a torus
    for (float theta = 0.0f; theta < 2.0f*PI; theta += theta_spacing) {
        // precompute sin and cos of theta
        float sinTheta = std::sin(theta);
        float cosTheta = std::cos(theta);

        // phi goes around the center of revolution of a torus
        for (float phi = 0.0f; phi < 2.0f*PI; phi += phi_spacing) {
            // precompute sin and cos of phi
            float sinPhi = std::sin(phi);
            float cosPhi = std::cos(phi);

            // X, Y coordinate of the circle, before revolving
            float circleX = R2 + R1 * cosTheta;
            float circleY = R1 * sinTheta;

            // Final 3D (X, Y, Z) coordinate after rotations
            float x = circleX*(cosB*cosPhi + sinA*sinB*sinPhi) - circleY*cosA*sinB;
            float y = circleX*(sinB*cosPhi - sinA*cosB*sinPhi) + circleY*cosA*cosB;
            float z = K2 + cosA*circleX*sinPhi + circleY*sinA;
            float ooz = 1.0f / z;

            // Project back into 2D space
            int xp = (int) (SCREENWIDTH/2.0f + K1*ooz*x);
            int yp = (int) (SCREENHEIGHT/2.0f - K1*ooz*y);

            // Calculate Luminance (L ranges [-sqrt(2), +sqrt(2)])
            float L = cosPhi*cosTheta*sinB - cosA*cosTheta*sinPhi - sinA*sinTheta + cosB*(cosA*sinTheta - cosTheta*sinA*sinPhi);
            if (L > 0.0f && xp >= 0 && xp < SCREENWIDTH && yp >= 0 && yp < SCREENHEIGHT) {
                // Test against the zBuffer
                if (ooz > zBuffer[xp + yp * SCREENWIDTH]) {
                    zBuffer[xp + yp * SCREENWIDTH] = ooz;
                    unsigned int luminance_index = L * 8;
                    outputBuffer[xp + yp * SCREENWIDTH] = brightness[luminance_index];
                }
            }
        }
    }
}

void Donut::RenderDonut() {
    // Clear terminal
    terminal.clearTerminal();

    for (int j = 0; j < SCREENHEIGHT; j++) {
        char rowBuffer[SCREENWIDTH+1];
        for (int i = 0; i < SCREENWIDTH; i++) {
            rowBuffer[i] = outputBuffer[i + j * SCREENWIDTH];
        }
        rowBuffer[SCREENWIDTH] = '\0';
        //terminal.print(rowBuffer);
        std::cout << rowBuffer;
    }
}
