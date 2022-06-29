#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Screen.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Texture.h"
#include "Shader.h"
#include "Light.h"
#include "Renderer.h"
#include "Material.h"
#include "TLEngineCG.h"
#include "GameLoop.h"
#include "RenderSystem.h"
#include "Scene.h"
#include "TLEngineCG.h"



GLfloat lastX;
GLfloat lastY;
Camera camera;
GameObject cameraObject;

bool keys[1024];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();

int main()
{
	glfwSetKeyCallback(Screen::instance().window, key_callback);
	glfwSetCursorPosCallback(Screen::instance().window, mouse_callback);
	glfwSetScrollCallback(Screen::instance().window, scroll_callback);

	Renderer r;
	Scene s("Data/test.xml");
	cameraObject = *(s.Find("camera"));
	camera = *(cameraObject.GetComponent<Camera>());

	GameObject* object = s.Find("object");
	shared_ptr<Material> m = object->GetComponent<Renderer>()->material;
	m->SetRenderCallback([](Shader* shader, Material* mat)
		{
			/*glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture.texture);
			glUniform1i(glGetUniformLocation(shader->Program, "ourTexture"), 0);*/
			mat->renderQueueIndex = (int)RendererQueue::Background;
			Light* l = TLEngineCG::lights[0];

			shader->Use();
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glm::vec3 viewPos = cameraObject.GetComponent<Transform>()->position;
			
			glm::mat4 view = camera.GetViewMatrix();
			glm::mat4 projection = camera.GetProjMatrix();
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
			model = glm::rotate(model, 30.0f, glm::vec3(1.0f, 0.3f, 0.5f));
			
			glm::vec3 lightPos = l->gameobject->GetComponent<Transform>()->position;
			glm::vec3 lightColor = l->color;
			glm::vec3 objectColor(1.0f, 0.5f, 0.31f);

			SetUniformMat4(view, shader);
			SetUniformMat4(projection, shader);
			SetUniformMat4(model, shader);

			SetUniformVec3(lightPos, shader);
			SetUniformVec3(objectColor, shader);
			SetUniformVec3(lightColor, shader);
			SetUniformVec3(viewPos, shader);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		});

	GameLoop loop(60);
	loop.SetUpdateCallback([]()
		{
			Screen::instance().Display();
			RenderSystem::instance().Update();
			glfwSwapBuffers(Screen::instance().window);
		});
	loop.SetFixedUpdateCallback([]()
		{
			do_movement();
		});
	loop.StartLoop();
	glfwTerminate();
	return 0;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		cout << key << endl;
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement()
{
	if (keys[GLFW_KEY_W])
		cameraObject.transform->Translate(0.05f);
	if (keys[GLFW_KEY_S])
		cameraObject.transform->Translate(-0.05f);
	if (keys[GLFW_KEY_A])
		cameraObject.transform->Translate(cameraObject.transform->GetRight(), -0.05f);
	if (keys[GLFW_KEY_D])
		cameraObject.transform->Translate(cameraObject.transform->GetRight(), 0.05f);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
	lastX = xpos;
	lastY = ypos;

	GLfloat sensitivity = 0.05;	// Change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	cameraObject.transform->rotation.x += xoffset;
	cameraObject.transform->rotation.z += yoffset;
	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (cameraObject.transform->rotation.z > 89.0f)
		cameraObject.transform->rotation.z = 89.0f;
	if (cameraObject.transform->rotation.z < -89.0f)
		cameraObject.transform->rotation.z = -89.0f;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (camera.fov >= 1.0f && camera.fov <= 45.0f)
		camera.fov -= yoffset;
	if (camera.fov <= 1.0f)
		camera.fov = 1.0f;
	if (camera.fov >= 45.0f)
		camera.fov = 45.0f;
}