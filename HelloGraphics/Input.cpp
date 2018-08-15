#include "Input.h"

std::vector<InputData> Input::inputData;

void Input::Register(std::string eventName, std::function<void()> func, SDL_Keycode keyCode)
{
	InputData data;
	data.eventName = eventName;
	data.func = func;
	data.keyCode = keyCode;

	inputData.push_back(std::move(data));
}

void Input::Update(SDL_Event event)
{
	for each (auto data in inputData)
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == data.keyCode)
			{
				data.func();

				return;
			}
		}
	}
}