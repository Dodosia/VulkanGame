#include "first_app.h"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <array>
#include <chrono>
#include <cassert>
#include <stdexcept>


namespace VulkanGame
{
    FirstApp::FirstApp() 
    {
        loadGameObjects();
    }
    
    FirstApp::~FirstApp() { }
    
    void FirstApp::run() 
    {
        RenderSystem renderSystem{ lveDevice, lveRenderer.getSwapChainRenderPass() };
        auto currentTime = std::chrono::high_resolution_clock::now();

        KeyboardController playerController;
        float yaw = 1;
        int speed = 1.5;
        while (!lveWindow.shouldClose()) {
            glfwPollEvents();
            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;
            
            glm::vec2 forward_dir{ sin(yaw), cos(yaw) };

            enemies[0].transform.rotation += 0.001f;
            enemies[0].transform.translation += forward_dir * glm::vec2(speed) * frameTime;

            if (enemies[0].transform.translation.y > 1.f || enemies[0].transform.translation.y < -1.f || enemies[0].transform.translation.x < -1.f || enemies[0].transform.translation.x > 1.f)
            {
                yaw += 0.5f;
                speed *= -1;
            }

            if (enemies[0].transform.translation.x == gameObjects[0].transform.translation.x && enemies[0].transform.translation.x == gameObjects[0].transform.translation.x)
            {
                enemies[0].color *= glm::vec3({ -1.f, -1.f, -1.f });
            }
           
            playerController.move(lveWindow.getWindow(), frameTime, gameObjects[0]);

            if (gameObjects[0].transform.translation.x > 1.f)
            {
                gameObjects[0].transform.translation.x = 1.f;
            }
            if (gameObjects[0].transform.translation.x < -1.f)
            {
                gameObjects[0].transform.translation.x = -1.f;
            }

            if (auto commandBuffer = lveRenderer.beginFrame()) 
            {
                lveRenderer.beginSwapChainRenderPass(commandBuffer);
                renderSystem.renderGameObjects(commandBuffer, gameObjects);
                renderSystem.renderGameObjects(commandBuffer, enemies);
                lveRenderer.endSwapChainRenderPass(commandBuffer);
                lveRenderer.endFrame();
            }
        }
    
      vkDeviceWaitIdle(lveDevice.device());
    }
    
    void FirstApp::loadGameObjects() 
    {
        std::vector<Model::Vertex> vertices
        {
          {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
          {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
          {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
    
          {{-0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}},
          {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
          {{0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},
        };

        auto model = std::make_shared<Model>(lveDevice, vertices);
        GameObject cube = GameObject::createGameObject();
        cube.model = model;
        cube.color = { 1.f, 1.f, 1.f };
        cube.transform.scale = { 0.5f, 0.5f };
        gameObjects.push_back(std::move(cube));

        std::vector<Model::Vertex> vertices2
        {
          {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
          {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
          {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},

          {{-0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}},
          {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
          {{0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},
        };

        auto model2 = std::make_shared<Model>(lveDevice, vertices2);
        GameObject rect = GameObject::createGameObject();
        rect.model = model2;
        rect.color = { 0.1f, 1.f, 1.f };
        rect.transform.scale = { 0.1f, 0.1f };
        enemies.push_back(std::move(rect));

        auto model3 = std::make_shared<Model>(lveDevice, vertices2);
        GameObject rect2 = GameObject::createGameObject();
        rect2.model = model3;
        rect2.transform.translation.x = .5f;
        rect2.color = { 0.1f, 1.f, 1.f };
        rect2.transform.scale = { 0.1f, 0.1f };
        enemies.push_back(std::move(rect2));
    }
}
