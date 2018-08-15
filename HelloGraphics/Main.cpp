#include "Window.h"
#include "Scene.h"

int main(int argc, char* args[])
{
	Window window("My Window", 800, 600);
	Scene scene;

	Input::Register("debug", []() {std::cout << "DEBUG"; }, SDLK_e);

	window.Loop([&]() { scene.Render(); });

	return 0;
}