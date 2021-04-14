#pragma once
#include "Renderer.h"
#include "Test.h"


namespace test
{

	class Instancing : public Test
	{
	public:
		Instancing() = default;
		Instancing(GLFWwindow* window);
		~Instancing();

		void OnLoad();
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
		GLFWwindow* window = nullptr;
	};

}

