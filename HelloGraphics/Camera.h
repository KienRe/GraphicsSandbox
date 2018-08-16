#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Input.h"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 0.05f;
const float SENSIVITY = 0.05f;
const float FOV = 45.0f;

class Camera
{
private:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensivity;
	float Fov;


public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
		: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensivity(SENSIVITY), Fov(FOV)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;

		updateCameraVectors();

		//Register Inputs
		Input::Register("CAMERA_MOVE_UP", [=]() { Position += MovementSpeed * Front; }, SDLK_w);
		Input::Register("CAMERA_MOVE_DOWN", [=]() { Position -= MovementSpeed * Front; }, SDLK_s);
		Input::Register("CAMERA_MOVE_LEFT", [=]() { Position -= MovementSpeed * Right; }, SDLK_a);
		Input::Register("CAMERA_MOVE_RIGHT", [=]() { Position += MovementSpeed * Right; }, SDLK_d);
		Input::Register("ESCAPE MOUSE", []() {SDL_SetRelativeMouseMode(SDL_GetRelativeMouseMode() == SDL_TRUE ? SDL_FALSE : SDL_TRUE); }, SDLK_ESCAPE);

		SDL_SetRelativeMouseMode(SDL_TRUE);
	}

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

	void Update()
	{
		Yaw += Input::mouseData.relX * MouseSensivity;
		Pitch += Input::mouseData.relY * MouseSensivity * -1;

		//Pitch Constraints
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

private:
	void updateCameraVectors()
	{
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
	}
};