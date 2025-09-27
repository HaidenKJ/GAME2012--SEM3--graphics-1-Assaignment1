#include "Window.h"
#include <glad/glad.h>
#include <iostream>
#include <chrono> // That is a cool name, I like it

int main()
{
    CreateWindow(800, 800, "Graphics 1 - Assignment 1");
    auto startTime = std::chrono::high_resolution_clock::now();

    //// WHITE TRIANGLE - original positions (kept intact)
    //float vertices[] = {
    //     0.0f,  0.1f, 0.0f,  // top
    //    -0.1f, -0.1f, 0.0f,  // bottom left
    //     0.1f, -0.1f, 0.0f   // bottom right
    //};

    // WHITE TRIANGLE - position + color 
    float whiteVerticesWithColor[] = {
        // pos.x, pos.y, pos.z,   r,   g,   b
         0.0f,  0.1f, 0.0f,     1.0f,1.0f,1.0f,
        -0.1f, -0.1f, 0.0f,     1.0f,1.0f,1.0f,
         0.1f, -0.1f, 0.0f,     1.0f,1.0f,1.0f
    };

    unsigned int whiteVAO, whiteVBO;
    glGenVertexArrays(1, &whiteVAO);
    glGenBuffers(1, &whiteVBO);

    glBindVertexArray(whiteVAO);
    glBindBuffer(GL_ARRAY_BUFFER, whiteVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(whiteVerticesWithColor), whiteVerticesWithColor, GL_STATIC_DRAW);

    // position attribute (location = 0) -> 3 floats, stride = 6 floats
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute (location = 1) -> next 3 floats
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // A rainbow triangle (using vertex colour attributes).
    float rainbowVertices[] = {
        //  position.x, position.y, position.z,   r,   g,   b
         0.3f,  0.1f, 0.0f,   1.0f, 0.0f, 0.0f, // top - red
         0.2f, -0.1f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom left - greeen
         0.4f, -0.1f, 0.0f,   0.0f, 0.0f, 1.0f  // bottom righ - blue
    };

    unsigned int rainbowVAO, rainbowVBO;
    glGenVertexArrays(1, &rainbowVAO);
    glGenBuffers(1, &rainbowVBO);

    glBindVertexArray(rainbowVAO);
    glBindBuffer(GL_ARRAY_BUFFER, rainbowVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rainbowVertices), rainbowVertices, GL_STATIC_DRAW);

    // position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // A triangle who’s colour changes over time (using uniforms).
    float ColorChangingVertices[] = {
        //  position.x, position.y, position.z,   r,   g,   b
         -0.3f,  0.1f, 0.0f,   1.0f, 0.0f, 0.0f, // top - red
         -0.2f, -0.1f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom left - greeen
         -0.4f, -0.1f, 0.0f,   0.0f, 0.0f, 1.0f  // bottom righ - blue
    };

    unsigned int CCVAO, CCVBO;
    glGenVertexArrays(1, &CCVAO);
    glGenBuffers(1, &CCVBO);

    glBindVertexArray(CCVAO);
    glBindBuffer(GL_ARRAY_BUFFER, CCVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ColorChangingVertices), ColorChangingVertices, GL_STATIC_DRAW);

    // position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //  A triangle that translates back and forth from x = 1 to x = -1.
    float TranslatingVertices[] = {
        //  position.x, position.y, position.z,   r,   g,   b
     0.0f, -0.2f, 0.0f,  1.0f, 1.0f, 0.0f, // top
    -0.1f, -0.4f, 0.0f,  1.0f, 1.0f, 0.0f, // bottom left
     0.1f, -0.4f, 0.0f,  1.0f, 1.0f, 1.0f  // bottom right
    };

    unsigned int movingVAO, movingVBO;
    glGenVertexArrays(1, &movingVAO);
    glGenBuffers(1, &movingVBO);

    glBindVertexArray(movingVAO);
    glBindBuffer(GL_ARRAY_BUFFER, movingVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TranslatingVertices), TranslatingVertices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // ------------------------------

    const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;

    out vec3 vertexColor;

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
        vertexColor = aColor;
    }
)";
    const char* fragmentShaderSource = R"(
    #version 330 core
    in vec3 vertexColor;
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(vertexColor, 1.0);
    }
)";

    const char* fragmentShaderSourceCHANGING = R"(
    #version 330 core
    in vec3 vertexColor;
    out vec4 FragColor;

    uniform float uTime; // the time uniform passed from C++

    void main()
    {
        // Animate colors using time
        vec3 animatedColor;
        animatedColor.r = abs(sin(uTime + vertexColor.r));
        animatedColor.g = abs(sin(uTime + vertexColor.g));
        animatedColor.b = abs(sin(uTime + vertexColor.b));

        FragColor = vec4(animatedColor, 1.0);
    }
)";

    const char* vertexShaderSourceMOVING = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec3 aColor;

    out vec3 vertexColor;

    uniform vec2 uTranslation; // x and y offset

    void main()
    {
        gl_Position = vec4(aPos.xy + uTranslation, aPos.z, 1.0);
        vertexColor = aColor;
    }
)";

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

    // Ones below are for the animated triangle
    unsigned int vertexShaderAnimated = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderAnimated, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderAnimated);

    unsigned int fragmentShaderAnimated = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderAnimated, 1, &fragmentShaderSourceCHANGING, NULL);
    glCompileShader(fragmentShaderAnimated);

    unsigned int shaderProgramAnimated = glCreateProgram();
    glAttachShader(shaderProgramAnimated, vertexShaderAnimated);
    glAttachShader(shaderProgramAnimated, fragmentShaderAnimated);
    glLinkProgram(shaderProgramAnimated);

    GLint timeLocAnimated = glGetUniformLocation(shaderProgramAnimated, "uTime");

    // Ones below are for the left-right moving triangle
    unsigned int vertexShaderMoving = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderMoving, 1, &vertexShaderSourceMOVING, NULL);
    glCompileShader(vertexShaderMoving);

    unsigned int fragmentShaderMoving = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderMoving, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaderMoving);

    unsigned int movingShaderProgram = glCreateProgram();
    glAttachShader(movingShaderProgram, vertexShaderMoving);
    glAttachShader(movingShaderProgram, fragmentShaderMoving);
    glLinkProgram(movingShaderProgram);

    GLint translationLoc = glGetUniformLocation(movingShaderProgram, "uTranslation"); // this is incredibly scuffed.

    glDeleteShader(vertexShaderMoving);
    glDeleteShader(fragmentShaderMoving);
    glDeleteShader(vertexShaderAnimated);
    glDeleteShader(fragmentShaderAnimated);

    // Main render loop
    while (!WindowShouldClose())
    {
        auto now = std::chrono::high_resolution_clock::now();
        float tt = std::chrono::duration<float>(now - startTime).count();

        float speed = 1.0f; // speed of translation
        float xOffset = sin(tt * speed); // oscillates between -1 and 1

        // Background color
        float r = 239.0f / 255.0f;
        float g = 136.0f / 255.0f;
        float b = 190.0f / 255.0f;
        float a = 1.0f;

        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw static white and rainbow triangles
        glUseProgram(shaderProgram);
        glBindVertexArray(whiteVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(rainbowVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw moving triangle
        glUseProgram(movingShaderProgram); // MUST use moving shader
        glUniform2f(translationLoc, xOffset, 0.0f); // yOffset = 0 for horizontal movement
        glBindVertexArray(movingVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw color-changing triangle
        glUseProgram(shaderProgramAnimated);
        glUniform1f(timeLocAnimated, tt);
        glBindVertexArray(CCVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        Loop();
    }

    // Cleanup
    glDeleteVertexArrays(1, &whiteVAO);
    glDeleteBuffers(1, &whiteVBO);

    glDeleteVertexArrays(1, &rainbowVAO);
    glDeleteBuffers(1, &rainbowVBO);

    glDeleteVertexArrays(1, &CCVAO);
    glDeleteBuffers(1, &CCVBO);

    glDeleteVertexArrays(1, &movingVAO);
    glDeleteBuffers(1, &movingVBO);

    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgramAnimated);
    glDeleteProgram(movingShaderProgram);

    DestroyWindow();
    return 0;
}
