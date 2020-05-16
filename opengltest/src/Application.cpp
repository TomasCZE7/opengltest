#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include "VertexBuffer.h"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

static const float WINDOW_WIDTH = 960.0f;
static const float WINDOW_HEIGHT = 540.0f;

int main(void){
    GLFWwindow* window;


    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        return -1;

    float positions[] = {
         -50.0f, -50.0f, 0.0f, 0.0f,
          50.0f, -50.0f, 1.0f, 0.0f,
          50.0f,  50.0f, 1.0f, 1.0f,
         -50.0f,  50.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    callGL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    callGL(glEnable(GL_BLEND));
    {
        VertexArray va;
        VertexBuffer vb(positions, sizeof(float) * 4 * 4);
        VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        va.addBuffer(vb, layout);
            
        IndexBuffer ib(indices, 2 * 3);

        glm::mat4 projectionMatrix = glm::ortho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, -1.0f, 1.0f);
        glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        
        Shader shader("resources/shader/Basic.shader");
        shader.bind();
        //shader.setUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);

        Texture dirt("resources/texture/grass_block.jpg");
        dirt.bind();
        shader.setUniform1i("textureUniform", 0);

        std::cout << glGetString(GL_VERSION) << std::endl;

        va.unBind();
        vb.unBind();
        ib.unBind();
        shader.unBind();

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        glm::vec3 translation1(200, 200, 0);
        glm::vec3 translation2(400, 200, 0);

        while (!glfwWindowShouldClose(window))
        {
            renderer.clear();

            ImGui_ImplGlfwGL3_NewFrame();
            
            shader.bind();
            //shader.setUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);
            {
                glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), translation1);
                glm::mat4 modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
                shader.setUniformMatrix4f("modelViewProjectionMatrix", modelViewProjectionMatrix);
                renderer.draw(va, ib, shader);
            }

            {
                glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), translation2);
                glm::mat4 modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
                shader.setUniformMatrix4f("modelViewProjectionMatrix", modelViewProjectionMatrix);
                renderer.draw(va, ib, shader);
            }
            
            {
                ImGui::SliderFloat3("Translation first", &translation1.x, 0.0f, WINDOW_WIDTH);
                ImGui::SliderFloat3("Translation second", &translation2.x, 0.0f, WINDOW_WIDTH);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

        }
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    
    glfwTerminate();
    return 0;
}