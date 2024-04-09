#pragma once
#include <iostream>
#include "game_object.h"
#include "window.h"

namespace VulkanGame
{
	class KeyboardController
	{
	public:
		struct Keys
		{
			int move_left = GLFW_KEY_A;
			int move_right = GLFW_KEY_D;
			int move_forward = GLFW_KEY_W;
			int move_back = GLFW_KEY_S;
		};

		void move(GLFWwindow* window, float dt, GameObject& gameObject);

		Keys keys{};
		float move_speed = 2.0f;
	};
}