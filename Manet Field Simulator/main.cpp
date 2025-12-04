#include <GLFW/glfw3.h>
#include <cubicmagnet.h>
#include <cylindermagnet.h>
#include <sensor.h>
#include <stdio.h>


#define GLAD_GL_IMPLEMENTATION
// #include <gl.h>
#define GLFW_INCLUDE_NONE

static void error_callback (int error, const char* description)
{
    fprintf (stderr, "Error: %s\n", description);
}

static void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose (window, GLFW_TRUE);
}

int main ()
{
    glfwSetErrorCallback (error_callback);

    if (!glfwInit ())
        exit (EXIT_FAILURE);

    GLFWwindow* window = glfwCreateWindow (650, 650, "Kur za Kaloqn", NULL, NULL);

    if (!window) {
        glfwTerminate ();
        exit (EXIT_FAILURE);
    }

    glfwSetKeyCallback (window, key_callback);

    // glfwMakeContextCurrent (window);
    // gladLoadGL (glfwGetProcAddress);
    // glfwSwapInterval (1);

    // CubicMagnet cube (0, 0, 0, 5, 12);
    // printf ("Cubic magnet created at position x: %f, y: %f, z: %f",
    // cube.position ()[0], cube.position ()[1], cube.position ()[2]);

    while (!glfwWindowShouldClose (window)) {
    }

    glfwDestroyWindow (window);

    glfwTerminate ();
    exit (EXIT_SUCCESS);
    return 0;
}