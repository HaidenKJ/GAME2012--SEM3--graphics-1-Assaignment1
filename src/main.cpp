#include "Window.h"
#include <glad/glad.h>

#include "Window.h"
#include <glad/glad.h>
#include <iostream>

int main()
{
    CreateWindow(800, 800, "Graphics 1 - Assignment 1");

	// White Triangle
    float whiteVertices[] = {
         0.0f,  0.5f, 0.0f,  // top
        -0.5f, -0.5f, 0.0f,  // bottom left
         0.5f, -0.5f, 0.0f   // bottom right
    };

    unsigned int whiteVAO, whiteVBO;
    glGenVertexArrays(1, &whiteVAO);
    glGenBuffers(1, &whiteVBO);

    glBindVertexArray(whiteVAO);
    glBindBuffer(GL_ARRAY_BUFFER, whiteVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(whiteVertices), whiteVertices, GL_STATIC_DRAW);

    // position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Unbind (good practice... apprarantley)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

	// Rainbow Triangle - position and color
    float rainbowVertices[] = {
        //  position.x, position.y, position.z,   r,   g,   b
         0.4f,  0.1f, 0.0f,                 1.0f, 0.0f, 0.0f, // top - red
        -0.1f, -0.5f, 0.0f,                 0.0f, 1.0f, 0.0f, // bottom left - green
         0.9f, -0.5f, 0.0f,                 0.0f, 0.0f, 1.0f  // bottom right - blue
	};

	unsigned int rainbowVAO, rainbowVBO;
	glGenVertexArrays(1, &rainbowVAO);
	glGenBuffers(1, &rainbowVBO);

	glBindVertexArray(rainbowVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rainbowVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rainbowVertices), rainbowVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // position
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // color
	glEnableVertexAttribArray(1);

    // unbind
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
    // (Minimal error check)
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::VERTEX_SHADER_COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Compile Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::FRAGMENT_SHADER_COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Create Shader Program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM_LINK_FAILED\n" << infoLog << std::endl;
    }

    // Clean up shader objects; program is linked
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float whiteVerticesWithColor[] = {
         0.0f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f, // top      (white)
        -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f, // bottom Left (white)
         0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f  // bottom Right (white)
    };

    // Replace the white triangle VBO with interleaved data so it has color attribute
    // (We still keep the whiteVAO handle and such - we will rebind and upload a new buffer to it)
    glBindVertexArray(whiteVAO);
    glBindBuffer(GL_ARRAY_BUFFER, whiteVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(whiteVerticesWithColor), whiteVerticesWithColor, GL_STATIC_DRAW);
    // position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    while (!WindowShouldClose())
    {
        // Background color (your original variables remain)
        float r = 239.0f / 255.0f;
        float g = 136.0f / 255.0f;
        float b = 190.0f / 255.0f;
        float a = 1.0f;

        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use shader program
        glUseProgram(shaderProgram);

        // Draw white triangle (the white colors are supplied by the VBO)
        glBindVertexArray(whiteVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw rainbow triangle
        glBindVertexArray(rainbowVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Unbind
        glBindVertexArray(0);

        Loop();
    }

    // Cleanup (you had similar cleanup before)
    glDeleteVertexArrays(1, &whiteVAO);
    glDeleteBuffers(1, &whiteVBO);

    glDeleteVertexArrays(1, &rainbowVAO);
    glDeleteBuffers(1, &rainbowVBO);

    glDeleteProgram(shaderProgram);

    DestroyWindow();
    return 0;
}