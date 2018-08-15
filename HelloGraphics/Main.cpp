#include "Window.h"
#include "Scene.h"

int main(int argc, char* args[])
{
	Window window("My Window", 800, 600);
	Scene scene;

	window.Loop([&]() { scene.Render(); });

	return 0;
}