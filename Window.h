#pragma once
#include "Camera.h"
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
    // Constructores y destructor
    Window();
    Window(GLint windowWidth, GLint windowHeight);
    ~Window();

    // Inicialización
    int Initialise();

    // Getters para la ventana GLFW
    GLFWwindow* getWindow() { return mainWindow; }

    // Configuración de cámara
    void setCamera(Camera* cam) { camera = cam; }

    // Getters para dimensiones del buffer
    GLfloat getBufferWidth() { return bufferWidth; }
    GLfloat getBufferHeight() { return bufferHeight; }

    // Getters para movimiento del mouse
    GLfloat getXChange();
    GLfloat getYChange();
    GLfloat getmuevex() { return muevex; }
    GLfloat getmuevey() { return muevey; }



    // Cámara
    GLfloat getopcion() { return opcion; }

    // Orbe
    GLfloat getOrbePrendido() { return orbePrendido; }

    // Control de ventana
    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }
    bool* getsKeys() { return keys; }
    void swapBuffers() { glfwSwapBuffers(mainWindow); }

    // Variables para animación de dados
    bool monedaInsertada;
    bool animacionDadosActiva;
    float animTimeDados;
    static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);

private:
    // Referencia a la cámara
    Camera* camera;

    // Ventana GLFW
    GLFWwindow* mainWindow;

    // Dimensiones
    GLint width, height;
    GLint bufferWidth, bufferHeight;

    // Control de teclado
    bool keys[1024];

    // Control de mouse
    GLfloat lastX;
    GLfloat lastY;
    GLfloat xChange;
    GLfloat yChange;
    GLfloat muevex;
    GLfloat muevey;
    bool mouseFirstMoved;

    // Cámara opción
    GLfloat opcion;

    // Estado del orbe
    bool orbePrendido = true; // el orbe comienza prendido

    // Métodos privados
    void createCallbacks();
    static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);
};