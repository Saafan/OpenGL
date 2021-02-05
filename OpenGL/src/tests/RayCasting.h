#pragma once
#include "Renderer.h"
#include "Test.h"


namespace test
{

	class RayCasting : public Test
	{
	public:
		RayCasting() = default;
		RayCasting(GLFWwindow* window);
		~RayCasting();

		void OnLoad();
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
		GLFWwindow* window = nullptr;
	};

}
