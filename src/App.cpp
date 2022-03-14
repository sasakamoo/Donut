#include "App.h"

void App::start() {
	if (demo.Construct(320, 240, 1, 1))
		demo.Start();
}