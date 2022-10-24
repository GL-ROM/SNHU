#include <iostream>         // cout, cerr
#include <cstdlib>          // EXIT_FAILURE
#include <GL/glew.h>        // GLEW library
#include <GLFW/glfw3.h>     // GLFW library
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>      // Image loading Utility functions
#include <camera.h>
#include <Cylinder.h>
#include <Cylinder.cpp>

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std; // Standard namespace

/*Shader program Macro*/
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif

// Unnamed namespace
namespace
{
    const char* const WINDOW_TITLE = "6-5 Milestone Gabriel Romero"; // Macro for window title

    // Variables for window width and height
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    // Stores the GL data relative to a given mesh
    struct GLMesh
    {
        GLuint vao;         // Handle for the vertex array object
        GLuint vbo;         // Handle for the vertex buffer object
        GLuint nVertices;    // Number of indices of the mesh
    };

    // Main GLFW window
    GLFWwindow* gWindow = nullptr;

    // Triangle mesh data
    GLMesh planeMesh;
    GLMesh cuttingBoardMesh;
    GLMesh carrotMesh;
    GLMesh saltBoxMesh;
    GLMesh knifeMesh;

    // Texture
    GLuint textureOne;
    GLuint textureTwo;
    GLuint textureThree;
    GLuint textureFour;
    glm::vec2 gUVScale(1.0f, 1.0f);
    GLint gTexWrapMode = GL_REPEAT;

    // Shader program
    GLuint gProgramId;
    GLuint gLampProgramId;

    // camera
    Camera gCamera(glm::vec3(0.0f, 0.0f, 5.0f));
    float gLastX = WINDOW_WIDTH / 2.0f;
    float gLastY = WINDOW_HEIGHT / 2.0f;
    bool gFirstMouse = true;

    // timing
    float gDeltaTime = 0.0f; // time between current frame and last frame
    float gLastFrame = 0.0f;

    // Pyramid and light color
    glm::vec3 gObjectColor(1.0f, 1.0f, 1.0f);
    glm::vec3 gLightColor(0.85f, 1.0f, 1.0f);

    // Light position and scale
    glm::vec3 gLightPosition(0.0f, 3.0f, 1.0f);
    glm::vec3 gLightScale(0.75f);

}

/* User-defined Function prototypes to:
 * initialize the program, set the window size,
 * redraw graphics on the window when resized,
 * and render graphics on the screen
 */
bool UInitialize(int, char* [], GLFWwindow** window);
void UResizeWindow(GLFWwindow* window, int width, int height);
void UProcessInput(GLFWwindow* window);
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void UCreateCuttingBoard(GLMesh& mesh);
void UCreatePlane(GLMesh& mesh);
void UCreateCarrot(GLMesh& mesh);
void UCreateSaltBox(GLMesh& mesh);
void UCreateKnife(GLMesh& mesh);
void UDestroyMesh(GLMesh& mesh);
bool UCreateTexture(const char* filename, GLuint& textureId);
void UDestroyTexture(GLuint textureId);
void URender();
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId);
void UDestroyShaderProgram(GLuint programId);


/* Vertex Shader Source Code*/
const GLchar* vertexShaderSource = GLSL(440,
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal; // VAP position 1 for normals
layout(location = 2) in vec2 textureCoordinate;

out vec2 vertexTextureCoordinate;
out vec3 vertexNormal; // For outgoing normals to fragment shader
out vec3 vertexFragmentPos; // For outgoing color / pixels to fragment shader

//Global variables for the transform matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f); // transforms vertices to clip coordinates
    vertexFragmentPos = vec3(model * vec4(position, 1.0f)); // Gets fragment / pixel position in world space only (exclude view and projection)
    vertexNormal = mat3(transpose(inverse(model))) * normal; // get normal vectors in world space only and exclude normal translation properties
    vertexTextureCoordinate = textureCoordinate;
}
);

/* Fragment Shader Source Code*/
const GLchar* fragmentShaderSource = GLSL(440,
    in vec2 vertexTextureCoordinate;
in vec3 vertexNormal; // For incoming normals
in vec3 vertexFragmentPos; // For incoming fragment position

out vec4 fragmentColor;

// Uniform / Global variables for object color, light color, light position, and camera/view position
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPosition;
uniform sampler2D uTexture; // Useful when working with multiple textures
uniform vec2 uvScale;

void main()
{
    /*Phong lighting model calculations to generate ambient, diffuse, and specular components*/

    //Calculate Ambient lighting*/
    float ambientStrength = 0.15f; // Set ambient or global lighting strength
    vec3 ambient = ambientStrength * lightColor; // Generate ambient light color

    //Calculate Diffuse lighting*/
    vec3 norm = normalize(vertexNormal); // Normalize vectors to 1 unit
    vec3 lightDirection = normalize(lightPos - vertexFragmentPos); // Calculate distance (light direction) between light source and fragments/pixels on cube
    float impact = max(dot(norm, lightDirection), 0.0);// Calculate diffuse impact by generating dot product of normal and light
    vec3 diffuse = impact * lightColor; // Generate diffuse light color

    //Calculate Specular lighting*/
    float specularIntensity = 1.0f; // Set specular light strength
    float highlightSize = 16.0f; // Set specular highlight size
    vec3 viewDir = normalize(viewPosition - vertexFragmentPos); // Calculate view direction
    vec3 reflectDir = reflect(-lightDirection, norm);// Calculate reflection vector
    //Calculate specular component
    float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), highlightSize);
    vec3 specular = specularIntensity * specularComponent * lightColor;

    // Texture holds the color to be used for all three components
    vec4 textureColor = texture(uTexture, vertexTextureCoordinate * uvScale);

    // Calculate phong result
    vec3 phong = (ambient + diffuse + specular) * textureColor.xyz;

    fragmentColor = vec4(phong, 1.0); // Send lighting results to GPU
}
);

/* Lamp Shader Source Code*/
const GLchar* lampVertexShaderSource = GLSL(440,

    layout(location = 0) in vec3 position; // VAP position 0 for vertex position data

    //Uniform / Global variables for the  transform matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates
}
);

/* Fragment Shader Source Code*/
const GLchar* lampFragmentShaderSource = GLSL(440,

    out vec4 fragmentColor; // For outgoing lamp color (smaller cube) to the GPU

void main()
{
    fragmentColor = vec4(1.0f); // Set color to white (1.0f,1.0f,1.0f) with alpha 1.0
}
);

// Images are loaded with Y axis going down, but OpenGL's Y axis goes up, so let's flip it
void flipImageVertically(unsigned char* image, int width, int height, int channels)
{
    for (int j = 0; j < height / 2; ++j)
    {
        int index1 = j * width * channels;
        int index2 = (height - 1 - j) * width * channels;

        for (int i = width * channels; i > 0; --i)
        {
            unsigned char tmp = image[index1];
            image[index1] = image[index2];
            image[index2] = tmp;
            ++index1;
            ++index2;
        }
    }
}


int main(int argc, char* argv[])
{
    if (!UInitialize(argc, argv, &gWindow))
        return EXIT_FAILURE;

    // Create the mesh
    UCreatePlane(planeMesh); // Calls the function to create the Vertex Buffer Object
    UCreateCuttingBoard(cuttingBoardMesh);
    UCreateCarrot(carrotMesh);
    UCreateSaltBox(saltBoxMesh);
    UCreateKnife(knifeMesh);

    // Create the shader program
    if (!UCreateShaderProgram(vertexShaderSource, fragmentShaderSource, gProgramId))
        return EXIT_FAILURE;

    if (!UCreateShaderProgram(lampVertexShaderSource, lampFragmentShaderSource, gLampProgramId))
        return EXIT_FAILURE;

    // texture 1
    // ---------
    glGenTextures(1, &textureOne);
    glBindTexture(GL_TEXTURE_2D, textureOne);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load("wooden_board_cut.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // texture two
    // ---------
    glGenTextures(1, &textureTwo);
    glBindTexture(GL_TEXTURE_2D, textureTwo);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // load image, create texture and generate mipmaps
    unsigned char* data2 = stbi_load("marble_top.jpg", &width, &height, &nrChannels, 0);
    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data2);

    // texture three
// ---------
    glGenTextures(1, &textureThree);
    glBindTexture(GL_TEXTURE_2D, textureThree);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // load image, create texture and generate mipmaps
    unsigned char* data3 = stbi_load("carrot.jpg", &width, &height, &nrChannels, 0);
    if (data3)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data3);

    // texture Four
// ---------
    glGenTextures(1, &textureFour);
    glBindTexture(GL_TEXTURE_2D, textureFour);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // load image, create texture and generate mipmaps
    unsigned char* data4 = stbi_load("mortons_salt.jpg", &width, &height, &nrChannels, 0);
    if (data4)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data4);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data4);

    glUseProgram(gProgramId);
    glUniform1i(glGetUniformLocation(gProgramId, "textureOne"), 0);
    glUniform1i(glGetUniformLocation(gProgramId, "textureTwo"), 1);
    glUniform1i(glGetUniformLocation(gProgramId, "textureThree"), 2);
    glUniform1i(glGetUniformLocation(gProgramId, "textureFour"), 3);

    // Sets the background color of the window to black (it will be implicitely used by glClear)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(gWindow))
    {
        // per-frame timing
        // --------------------
        float currentFrame = glfwGetTime();
        gDeltaTime = currentFrame - gLastFrame;
        gLastFrame = currentFrame;

        // input
        // -----
        UProcessInput(gWindow);

        // Render this frame
        URender();

        glfwPollEvents();
    }

    // Release mesh data
    UDestroyMesh(planeMesh);
    UDestroyMesh(cuttingBoardMesh);
    UDestroyMesh(carrotMesh);
    UDestroyMesh(saltBoxMesh);

    // Release texture
    UDestroyTexture(textureOne);
    UDestroyTexture(textureTwo);
    UDestroyTexture(textureThree);
    UDestroyTexture(textureFour);

    // Release shader program
    UDestroyShaderProgram(gProgramId);
    UDestroyShaderProgram(gLampProgramId);

    exit(EXIT_SUCCESS); // Terminates the program successfully
}


// Initialize GLFW, GLEW, and create a window
bool UInitialize(int argc, char* argv[], GLFWwindow** window)
{
    // GLFW: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // GLFW: window creation
    // ---------------------
    * window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (*window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(*window);
    glfwSetFramebufferSizeCallback(*window, UResizeWindow);
    glfwSetCursorPosCallback(*window, UMousePositionCallback);
    glfwSetScrollCallback(*window, UMouseScrollCallback);
    glfwSetMouseButtonCallback(*window, UMouseButtonCallback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // GLEW: initialize
    // ----------------
    // Note: if using GLEW version 1.13 or earlier
    glewExperimental = GL_TRUE;
    GLenum GlewInitResult = glewInit();

    if (GLEW_OK != GlewInitResult)
    {
        std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
        return false;
    }

    // Displays GPU OpenGL version
    cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << endl;

    return true;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void UProcessInput(GLFWwindow* window)
{
    static const float cameraSpeed = 2.5f;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        gCamera.ProcessKeyboard(FORWARD, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        gCamera.ProcessKeyboard(BACKWARD, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        gCamera.ProcessKeyboard(LEFT, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        gCamera.ProcessKeyboard(RIGHT, gDeltaTime);

    // Up down options for Q and E
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        gCamera.ProcessKeyboard(UP, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        gCamera.ProcessKeyboard(DOWN, gDeltaTime);
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void UResizeWindow(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (gFirstMouse)
    {
        gLastX = xpos;
        gLastY = ypos;
        gFirstMouse = false;
    }

    float xoffset = xpos - gLastX;
    float yoffset = gLastY - ypos; // reversed since y-coordinates go from bottom to top

    gLastX = xpos;
    gLastY = ypos;

    gCamera.ProcessMouseMovement(xoffset, yoffset);
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    gCamera.ProcessMouseScroll(yoffset);
}

// glfw: handle mouse button events
// --------------------------------
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
    {
        if (action == GLFW_PRESS)
            cout << "Left mouse button pressed" << endl;
        else
            cout << "Left mouse button released" << endl;
    }
    break;

    case GLFW_MOUSE_BUTTON_MIDDLE:
    {
        if (action == GLFW_PRESS)
            cout << "Middle mouse button pressed" << endl;
        else
            cout << "Middle mouse button released" << endl;
    }
    break;

    case GLFW_MOUSE_BUTTON_RIGHT:
    {
        if (action == GLFW_PRESS)
            cout << "Right mouse button pressed" << endl;
        else
            cout << "Right mouse button released" << endl;
    }
    break;

    default:
        cout << "Unhandled mouse button event" << endl;
        break;
    }
}


// Functioned called to render a frame
void URender()
{
    // Enable z-depth
    glEnable(GL_DEPTH_TEST);

    // Clear the frame and z buffers
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 1. Scales the object by 2
    glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f));
    // 2. Rotates shape by 15 degrees in the x axis
    glm::mat4 rotation = glm::rotate(200.0f, glm::vec3(1.0, 0.0f, 0.0f));
    glm::mat4 rotationTwo = glm::rotate(45.0f, glm::vec3(0.0, 0.0f, 1.0f));
    // 3. Place object at the origin
    glm::mat4 translation = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
    // Model matrix: transformations are applied right-to-left order
    glm::mat4 model = translation * rotation * rotationTwo * scale;

    // camera/view transformation
    glm::mat4 view = gCamera.GetViewMatrix();

    // Creates a perspective projection
    glm::mat4 projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);

    // Set the shader to be used
    glUseProgram(gProgramId);

    // Retrieves and passes transform matrices to the Shader program
    GLint modelLoc = glGetUniformLocation(gProgramId, "model");
    GLint viewLoc = glGetUniformLocation(gProgramId, "view");
    GLint projLoc = glGetUniformLocation(gProgramId, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Reference matrix uniforms from the Cube Shader program for the cub color, light color, light position, and camera position
    GLint objectColorLoc = glGetUniformLocation(gProgramId, "objectColor");
    GLint lightColorLoc = glGetUniformLocation(gProgramId, "lightColor");
    GLint lightPositionLoc = glGetUniformLocation(gProgramId, "lightPos");
    GLint viewPositionLoc = glGetUniformLocation(gProgramId, "viewPosition");

    // Pass color, light, and camera data to the Cube Shader program's corresponding uniforms
    glUniform3f(objectColorLoc, gObjectColor.r, gObjectColor.g, gObjectColor.b);
    glUniform3f(lightColorLoc, gLightColor.r, gLightColor.g, gLightColor.b);
    glUniform3f(lightPositionLoc, gLightPosition.x, gLightPosition.y, gLightPosition.z);
    const glm::vec3 cameraPosition = gCamera.Position;
    glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);

    GLint UVScaleLoc = glGetUniformLocation(gProgramId, "uvScale");
    glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

    // bind textures on corresponding texture units
    glBindTexture(GL_TEXTURE_2D, textureOne);
    glBindVertexArray(cuttingBoardMesh.vao);
    glDrawArrays(GL_TRIANGLES, 0, cuttingBoardMesh.nVertices);

    glBindTexture(GL_TEXTURE_2D, textureTwo);
    glBindVertexArray(planeMesh.vao);
    glDrawArrays(GL_TRIANGLES, 0, planeMesh.nVertices);

    glBindTexture(GL_TEXTURE_2D, textureThree);
    glBindVertexArray(carrotMesh.vao);
    glDrawArrays(GL_TRIANGLES, 0, carrotMesh.nVertices);

    glBindTexture(GL_TEXTURE_2D, textureFour);
    glBindVertexArray(saltBoxMesh.vao);
    glDrawArrays(GL_TRIANGLES, 0, saltBoxMesh.nVertices);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(gWindow);    // Flips the the back buffer with the front buffer every frame.
}


// Implements the UCreateMesh function
void UCreateCuttingBoard(GLMesh& mesh)
{
    // Vertex Data
    GLfloat verts[] = {

        // Cutting Board        //Normals                   //Textures
         -0.5f, -0.5f,  0.01f,   0.0f,  0.0f, -1.0f,        0.0f, 0.0f,
          0.5f, -0.5f,  0.01f,   0.0f,  0.0f, -1.0f,        1.0f, 0.0f,
          0.5f,  0.5f,  0.01f,   0.0f,  0.0f, -1.0f,        1.0f, 1.0f,
          0.5f,  0.5f,  0.01f,   0.0f,  0.0f, -1.0f,        1.0f, 1.0f,
         -0.5f,  0.5f,  0.01f,   0.0f,  0.0f, -1.0f,        0.0f, 1.0f,
         -0.5f, -0.5f,  0.01f,   0.0f,  0.0f, -1.0f,        0.0f, 0.0f,

         -0.5f, -0.5f,  0.15f,   0.0f,  0.0f,  1.0f,        0.0f, 0.0f,
          0.5f, -0.5f,  0.15f,   0.0f,  0.0f,  1.0f,        1.0f, 0.0f,
          0.5f,  0.5f,  0.15f,   0.0f,  0.0f,  1.0f,        1.0f, 1.0f,
          0.5f,  0.5f,  0.15f,   0.0f,  0.0f,  1.0f,        1.0f, 1.0f,
         -0.5f,  0.5f,  0.15f,   0.0f,  0.0f,  1.0f,        0.0f, 1.0f,
         -0.5f, -0.5f,  0.15f,   0.0f,  0.0f,  1.0f,        0.0f, 0.0f,

         -0.5f,  0.5f,  0.15f,  -1.0f,  0.0f,  0.0f,        1.0f, 0.0f,
         -0.5f,  0.5f,  0.01f,  -1.0f,  0.0f,  0.0f,        1.0f, 1.0f,
         -0.5f, -0.5f,  0.01f,  -1.0f,  0.0f,  0.0f,        0.0f, 1.0f,
         -0.5f, -0.5f,  0.01f,  -1.0f,  0.0f,  0.0f,        0.0f, 1.0f,
         -0.5f, -0.5f,  0.15f,  -1.0f,  0.0f,  0.0f,        0.0f, 0.0f,
         -0.5f,  0.5f,  0.15f,  -1.0f,  0.0f,  0.0f,        1.0f, 0.0f,

          0.5f,  0.5f,  0.15f,   1.0f,  0.0f,  0.0f,        1.0f, 0.0f,
          0.5f,  0.5f,  0.01f,   1.0f,  0.0f,  0.0f,        1.0f, 1.0f,
          0.5f, -0.5f,  0.01f,   1.0f,  0.0f,  0.0f,        0.0f, 1.0f,
          0.5f, -0.5f,  0.01f,   1.0f,  0.0f,  0.0f,        0.0f, 1.0f,
          0.5f, -0.5f,  0.15f,   1.0f,  0.0f,  0.0f,        0.0f, 0.0f,
          0.5f,  0.5f,  0.15f,   1.0f,  0.0f,  0.0f,        1.0f, 0.0f,

         -0.5f, -0.5f,  0.01f,   0.0f, -1.0f,  0.0f,        0.0f, 1.0f,
          0.5f, -0.5f,  0.01f,   0.0f, -1.0f,  0.0f,        1.0f, 1.0f,
          0.5f, -0.5f,  0.15f,   0.0f, -1.0f,  0.0f,        1.0f, 0.0f,
          0.5f, -0.5f,  0.15f,   0.0f, -1.0f,  0.0f,        1.0f, 0.0f,
         -0.5f, -0.5f,  0.15f,   0.0f, -1.0f,  0.0f,        0.0f, 0.0f,
         -0.5f, -0.5f,  0.01f,   0.0f, -1.0f,  0.0f,        0.0f, 1.0f,

         -0.5f,  0.5f,  0.01f,   0.0f,  1.0f,  0.0f,        0.0f, 1.0f,
          0.5f,  0.5f,  0.01f,   0.0f,  1.0f,  0.0f,        1.0f, 1.0f,
          0.5f,  0.5f,  0.15f,   0.0f,  1.0f,  0.0f,        1.0f, 0.0f,
          0.5f,  0.5f,  0.15f,   0.0f,  1.0f,  0.0f,        1.0f, 0.0f,
         -0.5f,  0.5f,  0.15f,   0.0f,  1.0f,  0.0f,        0.0f, 0.0f,
         -0.5f,  0.5f,  0.01f,   0.0f,  1.0f,  0.0f,        0.0f, 1.0f
         // End of Cutting Board
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    mesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

// Implements the UCreateMesh function
void UCreatePlane(GLMesh& mesh)
{
    GLfloat verts[] = {

        //Positions            //Normals            //Texture Coordinates
        // Plane underneath board
        -2.0f, -2.0f,  0.0f,   0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         2.0f, -2.0f,  0.0f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         2.0f,  2.0f,  0.0f,   0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         2.0f,  2.0f,  0.0f,   0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -2.0f,  2.0f,  0.0f,   0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -2.0f, -2.0f,  0.0f,   0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        // End of Plane underboard

    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    mesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

// Create Carrot
void UCreateCarrot(GLMesh& mesh)
{
    GLfloat verts[] = {

        //Positions                 //Normals            //Texture Coordinates
        // Carrot Middle Bottom
         0.02f,  0.0f,   0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,      // Top Left carrot
         0.02f, -0.4f,  0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 1.0f,       // Point of carrot
        -0.05f,  0.0f,   0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,      // Bottom Left of carrot

         0.02f, -0.4f,  0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 1.0f,       // Point of carrot
        -0.05f,  0.0f,   0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,      // Bottom Left of carrot
        -0.07f,  0.0f,   0.19f,   0.0f,  0.0f, 1.0f,   0.0f, 0.0f,    

        -0.07f,  0.0f,   0.19f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.02f, -0.4f,  0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 1.0f,       // Point of carrot
         0.02f,  0.0f,   0.21f,   0.0f, 0.0f, 1.0f,     0.0f, 0.0f,  

         0.02f,  0.0f,   0.21f,   0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
         0.02f,  0.0f,   0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,      // Top Left carrot
         0.02f, -0.4f,  0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 1.0f,       // Point of carrot
         
          0.02f,  0.0f,   0.21f,   0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
          0.02f,  0.0f,   0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,      // Top Left carrot
         -0.05f,  0.0f,   0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,      // Bottom Left of carrot
         -0.07f,  0.0f,   0.19f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         -0.05f,  0.0f,   0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,      // Bottom Left of carrot
         0.02f,  0.0f,   0.21f,   0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
          // End of Carrot

    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    mesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

// Create Saltbox
void UCreateSaltBox(GLMesh& mesh)
{
    GLfloat verts[] = {

        //Positions                 //Normals               //Texture Coordinates
        // Base of Box
        0.4f,   0.4f,  0.16f,      0.0f,  0.0f, 1.0f,       1.0f, 1.0f,  // Base Top Left
        0.4f,   0.05f,  0.16f,     0.0f,  0.0f, 1.0f,       0.0f, 0.0f,  // Base Top Right
        0.25f,  0.05f,  0.16f,     0.0f,  0.0f, 1.0f,       1.0f, 0.0f,  // Base Bottom Right

        0.4f,   0.4f,  0.16f,      0.0f,  0.0f, 1.0f,       1.0f, 1.0f,
        0.25f,  0.05f,  0.16f,    0.0f,  0.0f, 1.0f,        0.0f, 0.0f,
        0.25f,  0.4f,  0.16f,     0.0f,  0.0f, 1.0f,        1.0f, 0.0f,  // Base Bottom Left

        // Sides of Box
        // Left Side
        0.4f,   0.4f,  0.16f,      0.0f,  0.0f, 1.0f,       0.0f, 0.0f,
        0.25f,  0.4f,  0.16f,     0.0f,  0.0f, 1.0f,        0.0f, 0.0f,
        0.4f,   0.4f,  0.5f,       0.0f,  0.0f, 1.0f,       0.0f, 0.0f, // Top of Box Top Left

        0.4f,   0.4f,   0.5f,       0.0f,  0.0f, 1.0f,      0.0f, 0.0f, 
        0.25f,  0.4f,  0.16f,     0.0f,  0.0f, 1.0f,        0.0f, 0.0f,
        0.25f,  0.4f,  0.5f,      0.0f,  0.0f, 1.0f,        0.0f, 0.0f, // Top of Box Bottom Left

        // Right Side
        0.4f,   0.05f,  0.16f,     0.0f,  0.0f, 1.0f,       1.0f, 0.0f,
        0.25f,  0.05f,  0.16f,     0.0f,  0.0f, 1.0f,       1.0f, 1.0f,
        0.4f,   0.05f,   0.5f,     0.0f,  0.0f, 1.0f,       1.0f, 0.0f, // Top of Box Top Right

        0.4f,   0.05f,   0.5f,     0.0f,  0.0f, 1.0f,       1.0f, 0.0f,
        0.25f,  0.05f,  0.16f,     0.0f,  0.0f, 1.0f,       1.0f, 1.0f,
        0.25f,  0.05f,  0.5f,      0.0f,  0.0f, 1.0f,       1.0f, 1.0f,

        // Front Side
        0.25f,  0.4f,  0.5f,      1.0f,  0.0f, 1.0f,        0.0f, 1.0f,  // Top of Box Bottom Left
        0.25f,  0.4f,  0.16f,     1.0f,  0.0f, 1.0f,        0.0f, 0.0f,  // Base Bottom Left
        0.25f,  0.05f,  0.16f,    1.0f,  0.0f, 1.0f,        1.0f, 0.0f,  // Base Bottom Right

        0.25f,  0.05f,  0.5f,     1.0f,  0.0f, 1.0f,       1.0f, 1.0f,  // Top of Box Bottom Right
        0.25f,  0.05f,  0.16f,    1.0f,  0.0f, 1.0f,       1.0f, 0.0f,  // Base Bottom Right
        0.25f,  0.4f,  0.5f,      1.0f,  0.0f, 1.0f,       0.0f, 1.0f,  // Top of Box Bottom Left

        // Back  Side
        0.4f,   0.4f,  0.5f,       0.0f,  0.0f, 1.0f,       0.0f, 1.0f, // Top of Box Top Left
        0.4f,   0.4f,  0.16f,      0.0f,  0.0f, 1.0f,       0.0f, 0.0f,  // Base Top Left
        0.4f,   0.05f,  0.16f,     0.0f,  0.0f, 1.0f,       1.0f, 0.0f,  // Base Top Right

        0.4f,   0.4f,  0.5f,       0.0f,  0.0f, 1.0f,       0.0f, 1.0f, // Top of Box Top Left
        0.4f,   0.05f,   0.5f,     0.0f,  0.0f, 1.0f,       1.0f, 1.0f, // Top of Box Top Right
        0.4f,   0.05f,  0.16f,     0.0f,  0.0f, 1.0f,       1.0f, 0.0f,  // Base Top Right

        // Top Side
        0.25f,  0.4f,  0.5f,      -1.0f,  0.0f, 0.0f,       1.0f, 0.0f,  // Top of Box Bottom Left
        0.4f,   0.4f,  0.5f,       0.0f,  0.0f, 1.0f,       1.0f, 1.0f,  // Top of Box Top Left
        0.25f,  0.05f,  0.5f,     -1.0f,  0.0f, 0.0f,       1.0f, 0.0f,  // Top of Box Bottom Right

        0.25f,  0.05f,  0.5f,     -1.0f,  0.0f, 0.0f,       1.0f, 0.0f,  // Top of Box Bottom Right
        0.4f,   0.05f,   0.5f,     0.0f,  0.0f, 1.0f,       1.0f, 1.0f, // Top of Box Top Right
        0.4f,   0.4f,  0.5f,       0.0f,  0.0f, 1.0f,       1.0f, 1.0f,  // Top of Box Top Left

    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    mesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

// Create Saltbox
void UCreateKnife(GLMesh& mesh)
{
    GLfloat verts[] = {

        //Positions            //Normals            //Texture Coordinates
        // Carrot Middle Bottom
         0.4f,  0.0f,   0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        -0.3f,  0.0f,   0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.3f, -0.25f,  0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        -0.3f, -0.25f,  0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        -0.3f,  0.0f,   0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.3f, -0.25f,  0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,

         // Carrot Middle Sides
          0.3f,  0.0f,   0.16f,    0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
          0.3f, -0.25f,  0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
          0.5f, -0.25f,  0.20f,    0.0f,  0.0f, 1.0f,   1.0f, 0.0f,

          0.5f, -0.25f,  0.20f,    0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         -0.5f,  0.0f,   0.20f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
          0.3f, -0.25f,  0.16f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
          // End of Carrot

    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    mesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

void UDestroyMesh(GLMesh& mesh)
{
    glDeleteVertexArrays(1, &mesh.vao);
    glDeleteBuffers(1, &mesh.vbo);
}


/*Generate and load the texture*/
bool UCreateTexture(const char* filename, GLuint& textureId)
{
    int width, height, channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
    if (image)
    {
        flipImageVertically(image, width, height, channels);

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (channels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        else if (channels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        else
        {
            cout << "Not implemented to handle image with " << channels << " channels" << endl;
            return false;
        }

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(image);
        glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

        return true;
    }

    // Error loading the image
    return false;
}


void UDestroyTexture(GLuint textureId)
{
    glGenTextures(1, &textureId);
}


// Implements the UCreateShaders function
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId)
{
    // Compilation and linkage error reporting
    int success = 0;
    char infoLog[512];

    // Create a Shader program object.
    programId = glCreateProgram();

    // Create the vertex and fragment shader objects
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // Retrive the shader source
    glShaderSource(vertexShaderId, 1, &vtxShaderSource, NULL);
    glShaderSource(fragmentShaderId, 1, &fragShaderSource, NULL);

    // Compile the vertex shader, and print compilation errors (if any)
    glCompileShader(vertexShaderId); // compile the vertex shader
    // check for shader compile errors
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glCompileShader(fragmentShaderId); // compile the fragment shader
    // check for shader compile errors
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    // Attached compiled shaders to the shader program
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);

    glLinkProgram(programId);   // links the shader program
    // check for linking errors
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glUseProgram(programId);    // Uses the shader program

    return true;
}


void UDestroyShaderProgram(GLuint programId)
{
    glDeleteProgram(programId);
}
