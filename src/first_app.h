#pragma once
#include "keyboard_controller.h"
#include "render_system.h"
#include "device.h"
#include "game_object.h"
#include "renderer.h"
#include "model.h"
#include "window.h"
#include <memory>
#include <vector>

namespace VulkanGame
{
	class FirstApp {
		public:
		static constexpr int WIDTH = 1000;
		static constexpr int HEIGHT = 1000;
	
		FirstApp();
		~FirstApp();
	
		FirstApp(const FirstApp &) = delete;
		FirstApp &operator=(const FirstApp &) = delete;
	
		void run();
	
	private:
		void loadGameObjects();
	
		Window lveWindow{WIDTH, HEIGHT, "Game"};
		Device lveDevice{lveWindow};
		Renderer lveRenderer{ lveWindow, lveDevice };
		std::vector<GameObject> gameObjects;
		std::vector<GameObject> enemies;
	};	
}
