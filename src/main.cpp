#include "Window.h"
#include <glad/glad.h>

#include "Window.h"
#include <glad/glad.h>
#include <iostream>

int main()
{
    CreateWindow(800, 800, "Graphics 1 - Assignment 1");

    // STEP 1: Define triangle vertices
    float vertices[] = {
         0.0f,  0.1f, 0.0f,  // top
        -0.1f, -0.1f, 0.0f,  // bottom let
         0.1f, -0.1f, 0.0f   // bottom right
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO); // Bind VAO (hehehehe silksong)

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind VBO (https://www.youtube.com/watch?v=dQw4w9WgXcQ&list=RDdQw4w9WgXcQ&start_radio=1) I should go to sleep..... but im not...
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Tell OpenGL how to interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind (good practice... apprarantley)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main()
        {
            gl_Position = vec4(aPos, 1.0);
        }   
    )"; // Im suprised I even got this to work

    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(1.0, 1.0, 1.0, 1.0); // white
        }
    )"; // i am not going to remember any of this when I wake up tomorrow, but at least it works now.... I think

    // Compile Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Compile Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create Shader Program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Clean up shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Main render loop
    while (!WindowShouldClose())
    {
        // Background color
        float r = 239.0f / 255.0f;
        float g = 136.0f / 255.0f;
        float b = 190.0f / 255.0f;
        float a = 1.0f;

        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);

        // --- DRAW REGULAR TRIANGLE ---
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        Loop();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    DestroyWindow();
    return 0;
}

