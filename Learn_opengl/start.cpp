
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Screen.hpp"
#include "Camera.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Light.hpp"

// Set up vertex data (and buffer(s)) and attribute pointers
GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};
//GLuint indices[] = {  // Note that we start from 0!
//    0, 1, 3, // First Triangle
//    1, 2, 3  // Second Triangle
//};

Screen mainScreen(800, 600);

GameObject cameraObject;
Transform tr(&cameraObject);
Camera camera(&mainScreen, &cameraObject);
GameObject lightObject;
Transform tr2(&lightObject);
Light light(0.1f,glm::vec3(1,1,1),&lightObject);

GLfloat lastX; 
GLfloat lastY;

bool keys[1024];

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();


int main()
{
    cameraObject.AddComponent(&tr);
    cameraObject.AddComponent(&camera);
    glfwSetKeyCallback(mainScreen.window, key_callback);
    glfwSetCursorPosCallback(mainScreen.window, mouse_callback);
    glfwSetScrollCallback(mainScreen.window, scroll_callback);
    
    Shader myShader("vert.shader","frag.shader");
    cameraObject.transform->rotation.x = -90.0f;
    cameraObject.transform->position.z = 3.0f;
    Texture t("container.jpg");
    GLuint VBO;//顶点缓存
    glGenBuffers(1, &VBO);//设置缓存ID
    //GLuint EBO;
    //glGenBuffers(1, &EBO);
    GLuint VAO;//顶点数组对象
    glGenVertexArrays(1, &VAO);//设置缓存ID

    glBindVertexArray(VAO);//绑定顶点数组对象

    glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定缓存对象
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//复制数据到缓存
    
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);//设置解析顶点数据的方式
    glEnableVertexAttribArray(0);//启用顶点属性
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));//设置解析颜色数据的方式
    //glEnableVertexAttribArray(1);//启用顶点属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);//解绑VAO


    

    //显示窗口
    while (mainScreen.isClosed())
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        do_movement();

        mainScreen.Display();

        // Bind Texture
        glBindTexture(GL_TEXTURE_2D, t.texture);

        // Activate shader
        myShader.Use();
       
        // Camera/View transformation
        glm::mat4 view;
        glm::vec3 cameraPos = cameraObject.GetComponent<Transform>()->position;
        view = glm::lookAt(cameraPos, cameraPos + Transform::forward, Transform::up);
        glm::mat4 projection;

        view = cameraObject.GetComponent<Camera>()->GetViewMatrix(); 
        projection = cameraObject.GetComponent<Camera>()->GetProjMatrix(); 
        
        // Get their uniform location
        GLint modelLoc = glGetUniformLocation(myShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(myShader.Program, "view");
        GLint projLoc = glGetUniformLocation(myShader.Program, "projection");
        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        // Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        for (GLuint i = 0; i < 10; i++)
        {
            // Calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            GLfloat angle = 20.0f * i;
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(mainScreen.window);
    }

    //释放资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
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
    // Camera controls
    GLfloat cameraSpeed = 5.0f * deltaTime;
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