#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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


Camera* camera;
GameObject* cameraObject;
GameObject* object;

bool keys[1024];
bool show_demo_window = false;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();
void fixedupdate()
{
	Screen::instance().Display();
	RenderSystem::instance().Update();

	// 开始渲染imgui
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(Screen::instance().window);
}


int main()
{
	GameLoop loop(60);

	// 场景初始化
	Scene s("Data/test.xml");
	cameraObject = s.Find("camera");
	object = s.Find("object");
	camera = cameraObject->GetComponent<Camera>();

	shared_ptr<Material> mat = object->GetComponent<Renderer>()->material;
	// 绑定回调函数
	//glfwSetKeyCallback(Screen::instance().window, key_callback);
	//glfwSetCursorPosCallback(Screen::instance().window, mouse_callback);
	//glfwSetScrollCallback(Screen::instance().window, scroll_callback);

	mat->SetRenderCallback([](GameObject* gameobject,Shader* shader, Material* mat)
		{
			mat->renderQueueIndex = (int)RendererQueue::Background;
			glm::vec3 viewPos = cameraObject->transform->position;
			
			glm::mat4 view = gameobject->owner->camera->GetViewMatrix();
			glm::mat4 projection = gameobject->owner->camera->GetProjMatrix();
			glm::mat4 model = object->transform->GetModel();

			Light* light = TLEngineCG::lights[0];
			glm::vec3 lightPos = light->gameobject->GetComponent<Transform>()->position;
			glm::vec3 lightColor = light->color;
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

	loop.SetUpdateCallback(fixedupdate);/*[]()
		{
			
		});*/

	loop.SetFixedUpdateCallback([]()
		{
			do_movement();
		});
	loop.StartLoop();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement()
{
	if (keys[GLFW_KEY_W])
		cameraObject->transform->Translate(0.05f);
	if (keys[GLFW_KEY_S])
		cameraObject->transform->Translate(-0.05f);
	if (keys[GLFW_KEY_A])
		cameraObject->transform->Translate(cameraObject->transform->GetRight(), -0.05f);
	if (keys[GLFW_KEY_D])
		cameraObject->transform->Translate(cameraObject->transform->GetRight(), 0.05f);
	if (keys[GLFW_KEY_RIGHT])
		object->transform->rotation.z += 0.05f;
	if (keys[GLFW_KEY_LEFT])
		object->transform->rotation.z -= 0.05f;	
	if (keys[GLFW_KEY_UP])
		object->transform->rotation.x += 0.05f;
	if (keys[GLFW_KEY_DOWN])
		object->transform->rotation.x -= 0.05f;
}

GLfloat lastX;
GLfloat lastY;
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

	cameraObject->transform->rotation.x += xoffset;
	cameraObject->transform->rotation.z += yoffset;
	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (cameraObject->transform->rotation.z > 89.0f)
		cameraObject->transform->rotation.z = 89.0f;
	if (cameraObject->transform->rotation.z < -89.0f)
		cameraObject->transform->rotation.z = -89.0f;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (camera->fov >= 1.0f && camera->fov <= 45.0f)
		camera->fov -= yoffset;
	if (camera->fov <= 1.0f)
		camera->fov = 1.0f;
	if (camera->fov >= 45.0f)
		camera->fov = 45.0f;
}