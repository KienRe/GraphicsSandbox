#include "Window.h"
#include "Renderer.h"
#include "Scene.h"

int main(int argc, char* args[])
{
	Window window("My Window", 800, 600);
	Renderer renderer(window.sdlWindow);
	Scene scene;
	Camera camera;

	window.Loop([&]() { renderer.RenderScene(scene,camera); });

	return 0;
}