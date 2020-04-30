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

int main(void){
    GLFWwindow* window;


    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(700, 500, "Hello World", NULL, NULL);
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
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f, 
        -0.5f,  0.5f
    };

    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0
    };
    {
        VertexArray va;
        VertexBuffer vb(positions, sizeof(float) * 4 * 2);
        VertexBufferLayout layout;
        layout.push<float>(2);
        va.addBuffer(vb, layout);
        IndexBuffer ib(indicies, 6);

        Shader shader("resources/shader/Basic.shader");
        shader.bind();
        shader.setUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);

        std::cout << glGetString(GL_VERSION) << std::endl;

        va.unBind();
        vb.unBind();
        ib.unBind();
        shader.unBind();

        Renderer renderer;
        
        while (!glfwWindowShouldClose(window))
        {
            renderer.clear();

            shader.bind();
            shader.setUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);

            renderer.draw(va, ib, shader);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}