#include "keyboard_controller.h"

void VulkanGame::KeyboardController::move(GLFWwindow* window, float dt, GameObject& gameObject)
{
	glm::vec2 moveDir{ 0.f };
	float yaw = gameObject.transform.rotation;
	const glm::vec2 forward_dir{ sin(yaw), cos(yaw) };
	const glm::vec2 right_dir{ forward_dir.y, 0.f};

	if (glfwGetKey(window, keys.move_right) == GLFW_PRESS) moveDir += right_dir;
	if (glfwGetKey(window, keys.move_left) == GLFW_PRESS) moveDir -= right_dir;
	if (glfwGetKey(window, keys.move_forward) == GLFW_PRESS) moveDir -= forward_dir;
	if (glfwGetKey(window, keys.move_back) == GLFW_PRESS) moveDir += forward_dir;

	if (glm::dot(moveDir, moveDir) > std::numeric_limits<float>::epsilon()) 
	{
		gameObject.transform.translation += move_speed * dt * glm::normalize(moveDir);
	}
}
