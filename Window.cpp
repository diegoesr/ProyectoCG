#include "Window.h"
#include <cstdlib>  // Para srand() y rand()

// Constructores
Window::Window()
{
    width = 800;
    height = 600;
    muevex = 2.0f;
    opcion = 0.0f;

    // Inicialización de variables de estado
    monedaInsertada = false;
    animacionDadosActiva = false;
    animTimeDados = 0.0f;
    orbePrendido = false;
    mouseFirstMoved = true;
    xChange = 0.0f;
    yChange = 0.0f;
    lastX = 0.0f;
    lastY = 0.0f;

    // Inicialización del array de teclas
    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }
}

Window::Window(GLint windowWidth, GLint windowHeight) : Window()
{
    width = windowWidth;
    height = windowHeight;
}

// Destructor
Window::~Window()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}

// Métodos públicos
int Window::Initialise()
{
    // Inicialización de GLFW
    if (!glfwInit())
    {
        printf("Falló inicializar GLFW");
        glfwTerminate();
        return 1;
    }

    // Configuración de ventana OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Creación de ventana
    mainWindow = glfwCreateWindow(width, height, "PROYECTO", NULL, NULL);

    if (!mainWindow)
    {
        printf("Fallo en crearse la ventana con GLFW");
        glfwTerminate();
        return 1;
    }

    // Configuración de buffers y contexto
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    glfwMakeContextCurrent(mainWindow);

    // Configuración de callbacks
    createCallbacks();

    // Inicialización de GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        printf("Falló inicialización de GLEW");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    // Configuración de OpenGL
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, bufferWidth, bufferHeight);
    glfwSetWindowUserPointer(mainWindow, this);


    return 0;
}

GLfloat Window::getXChange()
{
    GLfloat theChange = xChange;
    xChange = 0.0f;
    return theChange;
}

GLfloat Window::getYChange()
{
    GLfloat theChange = yChange;
    yChange = 0.0f;
    return theChange;
}

// Métodos privados
void Window::createCallbacks()
{
    glfwSetKeyCallback(mainWindow, ManejaTeclado);
    glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}

// Funciones estáticas de callback
void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    // Manejo general de teclas
    if (key >= 0 && key < 1024)
    {
        theWindow->keys[key] = (action == GLFW_PRESS);
    }

    // Salir de la aplicación
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }



    // Control de luz del orbe
    if (key == GLFW_KEY_O && action == GLFW_PRESS)
    {
        theWindow->orbePrendido = !theWindow->orbePrendido;
    }

    // Cambio de vista de cámara
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS && theWindow->camera)
    {
        theWindow->camera->toggleThirdPerson();
    }

    // Animación de dados
    if (key == GLFW_KEY_M && action == GLFW_PRESS)
    {
        srand(static_cast<unsigned int>(glfwGetTime() * 1000));
        theWindow->animacionDadosActiva = true;
    }

}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (theWindow->mouseFirstMoved)
    {
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mouseFirstMoved = false;
    }

    theWindow->xChange = xPos - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - yPos;

    theWindow->lastX = xPos;
    theWindow->lastY = yPos;
}