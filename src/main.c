#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f};

static const char *vertex_source =
    "#version 330 core\n"
    "layout (location = 0) in vec2 position;\n"
    "void main() {\n"
    "   gl_Position = vec4(position, 0.0f, 1.0f);\n"
    "}\n";

static const char *fragment_source =
    "#version 330 core\n"
    "out vec4 color;\n"
    "void main() {\n"
    "   color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n";

void glfw_error_callback(int _error, const char *description) {
    fprintf(stderr, "[ERROR] glfw: %s\n", description);
}

void glfw_window_size_callback(GLFWwindow *_window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main(void) {
    if (!glfwInit()) {
        fprintf(stderr, "failed to initialize glfw\n");
    }

    glfwSetErrorCallback(glfw_error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1280, 720, "Die Roller", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "failed to create window\n");
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, glfw_window_size_callback);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "failed to initialize glew\n");
    }

    GLuint va;
    glGenVertexArrays(1, &va);
    glBindVertexArray(va);

    GLuint vb;
    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);

    // TODO: Error checking

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);

    // TODO: Error checking

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glUseProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
