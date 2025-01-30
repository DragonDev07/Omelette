#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <ecs/Components/MeshComponent.hpp>
#include <ecs/Components/RigidBodyComponent.hpp>
#include <ecs/ECS.hpp>
#include <ecs/Entity.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <thread>
#include <utils/Shapes.hpp>
#include <utils/Vec3.hpp>

// Shader sources
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    void main() {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    }
)";

// Window dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Target frame rate
const float FRAME_RATE = 10.0f;
const std::chrono::milliseconds FRAME_DURATION(100); // 100ms = 10 FPS

// Function declarations
GLFWwindow* initializeGL();
unsigned int createShaderProgram();
void processInput(GLFWwindow* window);

int main() {
    // Initialize GLFW and OpenGL
    GLFWwindow* window = initializeGL();
    if (!window)
        return -1;

    // Create and compile shaders
    unsigned int shaderProgram = createShaderProgram();

    // Create ECS instance and entity
    omelette::ecs::ECS ecs;
    auto entity = std::make_unique<omelette::ecs::Entity>();
    auto entityPtr = entity.get();

    // Create cube shape
    auto [vertices, indices] =
        omelette::utils::Shapes::createCube(1.0f, 1.0f, 1.0f);

    // Create OpenGL buffers
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(omelette::utils::Vec3),
        vertices.data(),
        GL_DYNAMIC_DRAW
    );

    // Element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(uintptr_t),
        indices.data(),
        GL_STATIC_DRAW
    );

    // Set vertex attributes
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(omelette::utils::Vec3),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    // Create components
    auto meshComponent =
        std::make_unique<omelette::ecs::components::MeshComponent>(
            vertices,
            indices
        );
    auto meshComponentPtr = meshComponent.get();

    auto rigidBody =
        std::make_unique<omelette::ecs::components::RigidBodyComponent>(
            omelette::utils::Vec3(0, 0, 0), // position
            omelette::utils::Vec3(0, 0, 0), // velocity
            omelette::utils::Vec3(0, 0, 0), // acceleration
            1.0f, // mass
            meshComponentPtr // mesh component
        );
    auto rbPtr = rigidBody.get();

    // Add components to ECS
    ecs.addEntity(std::move(entity));
    ecs.addComponentToEntity(*entityPtr, std::move(meshComponent));
    ecs.addComponentToEntity(*entityPtr, std::move(rigidBody));

    // Set up camera
    glm::mat4 view = glm::lookAt(
        glm::vec3(3.0f, 3.0f, 5.0f), // Camera position
        glm::vec3(0.0f, 0.0f, 0.0f), // Look at point
        glm::vec3(0.0f, 1.0f, 0.0f) // Up vector
    );
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        (float)SCR_WIDTH / (float)SCR_HEIGHT,
        0.1f,
        100.0f
    );

    // Apply initial force
    omelette::utils::Vec3 force(2.0f, 0.0f, 0.0f);
    rbPtr->applyForce(force);

    // Enable depth testing and face culling
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Set polygon mode to render wireframe (for debugging)
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Simulation/render loop
    float deltaTime = 1.0f / FRAME_RATE;
    auto lastFrameTime = std::chrono::steady_clock::now();

    while (!glfwWindowShouldClose(window)) {
        auto currentFrameTime = std::chrono::steady_clock::now();
        auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            currentFrameTime - lastFrameTime
        );

        if (frameTime >= FRAME_DURATION) {
            lastFrameTime = currentFrameTime;

            // Process input
            processInput(window);

            // Clear buffers
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Use shader program
            glUseProgram(shaderProgram);

            // Update physics
            rbPtr->update(deltaTime);

            // Update vertex data
            const auto& updatedVertices = meshComponentPtr->getVertices();
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(
                GL_ARRAY_BUFFER,
                0,
                updatedVertices.size() * sizeof(omelette::utils::Vec3),
                updatedVertices.data()
            );

            // Set uniforms
            glUniformMatrix4fv(
                glGetUniformLocation(shaderProgram, "view"),
                1,
                GL_FALSE,
                glm::value_ptr(view)
            );
            glUniformMatrix4fv(
                glGetUniformLocation(shaderProgram, "projection"),
                1,
                GL_FALSE,
                glm::value_ptr(projection)
            );

            // Create and set model matrix
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(
                model,
                glm::vec3(
                    rbPtr->position.x,
                    rbPtr->position.y,
                    rbPtr->position.z
                )
            );
            glUniformMatrix4fv(
                glGetUniformLocation(shaderProgram, "model"),
                1,
                GL_FALSE,
                glm::value_ptr(model)
            );

            // Draw cube
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

            // Swap buffers and poll events
            glfwSwapBuffers(window);
            glfwPollEvents();

            // Print position for debugging
            std::cout << "Position: (" << rbPtr->position.x << ", "
                      << rbPtr->position.y << ", " << rbPtr->position.z
                      << ")\n";
        } else {
            // Sleep to prevent CPU from running at 100%
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

GLFWwindow* initializeGL() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window =
        glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cube Simulation", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return nullptr;
    }

    return window;
}

unsigned int createShaderProgram() {
    // Vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Clean up
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
