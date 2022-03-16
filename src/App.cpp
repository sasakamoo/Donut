#include "App.h"
#include <iostream>

void App::start() {
	printf("Hello!\n");
	demo.CalculateDonut(0, 0);
	demo.RenderDonut();
	printf("Goodbye!\n");
}