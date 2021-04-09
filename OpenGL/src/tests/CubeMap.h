#pragma once
#include "Renderer.h"
#include "Test.h"


namespace test
{

	class CubeMap : public Test
	{
	public:
		CubeMap() = default;
		CubeMap(GLFWwindow* window);
		~CubeMap();

		void OnLoad();
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
		GLFWwindow* window = nullptr;
	};

}

