#pragma once
#include "Renderer.h"
#include "Test.h"


namespace test
{

	class GeometryShader : public Test
	{
	public:
		GeometryShader() = default;
		GeometryShader(GLFWwindow* window);
		~GeometryShader();

		void OnLoad();
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
		GLFWwindow* window = nullptr;
	};

}

