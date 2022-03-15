#include "App.h"
#include <iostream>

void App::start() {
	std::cout << "Hello!\n";
	demo.CalculateDonut(0, 0);
	demo.RenderDonut();
	std::cout << "Goodbye!\n";
}