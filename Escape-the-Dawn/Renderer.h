#ifndef Renderer_h__
#define Renderer_h__

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <glext.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "glerror.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "Model.h"

class Renderer
{
public:
	ShaderProgram m_ShaderProgram;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	int HEIGHT, WIDTH;

	struct ModelData
	{
		Model* model;
		glm::mat4 ModelMatrix;
		ModelData(Model* _model, glm::mat4 _modelMatrix) : model(_model), ModelMatrix(_modelMatrix)
		{}
	};

	std::vector<ModelData*> ModelsToRender;

	Renderer();

	void Initialize();
	void Draw(double dt);
	void DrawText();

	void AddModelToDraw(Model*, glm::vec3, glm::quat);
	void AddTextToDraw();

	void LoadContent();

	GLFWwindow* GetWindow() const { return m_Window; }
	std::shared_ptr<Camera> GetCamera() const { return m_Camera; }

private:
	GLFWwindow* m_Window;
	GLint m_glVersion[2];
	GLchar* m_glVendor;

	std::shared_ptr<Camera> m_Camera;

	GLuint vertexArrayObject;
};

#endif // Renderer_h__