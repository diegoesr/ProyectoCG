/*
Animación:
Sesión 1:
Simple o básica:Por banderas y condicionales (más de 1 transformación geométrica se ve modificada
Sesión 2
Compleja: Por medio de funciones y algoritmos.
Textura Animada
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h> 

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

//Music
#include<iostream>
#include <irrKlang.h>
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")

// Punteros a las pistas
ISound* mainMusic = nullptr;
ISound* areaMusic = nullptr;
int currentZoneM = -1;  // -1 = ninguna zona activa

ISoundEngine* soundEngine = createIrrKlangDevice();



struct Zone {
	glm::vec3 min;
	glm::vec3 max;
	std::string musicPath;
};

std::vector<Zone> zones = {
	// Piso Finn
	{ {-278.06f, -0.99f, 269.844f}, {-258.06f, 22.01f, 289.844f}, "Music/finn.mp3" },

	// Piso Invencible
	{ {259.04f, -0.99f, 269.844f}, {279.04f, 22.01f, 289.844f}, "Music/invencible.mp3" },

	// Piso Bob
	{ {259.04f, -0.99f, -291.909f}, {279.04f, 22.01f, -271.909f}, "Music/bob.mp3" },

	// Piso Phineas
	{ {-279.04f, -0.99f, -291.844f}, {-259.04f, 22.01f, -271.844f}, "Music/phineas.mp3" }
};





const float toRadians = 3.14159265f / 180.0f;

//Variables Camera
glm::vec3 characterPosition(0.0f, -1.0f, 0.0f);
GLfloat lastX = 400.0f;  // Centro de pantalla inicial (ancho ventana / 2)
GLfloat lastY = 300.0f;  // Centro de pantalla inicial (alto ventana / 2)
bool firstMouse = true;  // Para evitar un salto enorme la primera vez
float turnSpeed = 1.0f;
bool* keys;
float characterYaw = 0.0f; // ángulo horizontal (en grados)

//Variable juegos
std::vector<glm::vec3> minigameCenters = {
	glm::vec3(10.0f, -1.0f, 10.0f),
	glm::vec3(0.0f, -1.0f, 10.0f),
	glm::vec3(10.0f, -1.0f, 50.0f)
};
bool isInMinigame = false;
bool blockMovement = false;
float minigameRadius = 1.0f;
int currentZone = -1;

//Variables Globos
std::vector<glm::vec3> globoPositions = {
	{280.0f, 17.0f, -340.0f},
	{270.0f, 17.0f, -340.0f},
	{290.0f, 17.0f, -340.0f},	
	{280.0f, 22.0f, -340.0f},
	{270.0f, 22.0f, -340.0f},
	{290.0f, 22.0f, -340.0f},
	{280.0f, 12.0f, -340.0f},
	{270.0f, 12.0f, -340.0f},
	{290.0f, 12.0f, -340.0f}
};
std::vector<bool> globoAlive(globoPositions.size(), true); // Todos vivos al principio
float reventarRadio = 0.5f; // Radio para explotar globos


//Variables animacion
bool isThrowing = false;
bool wasEPressed = true;
glm::vec3 throwPosition;
glm::vec3 throwDirection;
float throwRotation = 0.0f;
float throwSpeed = 0.5f;       // velocidad de movimiento
float throwRotationSpeed = 15.0f; // grados por segundo
float maxThrowDistance = 10.0f; // distancia máxima
glm::vec3 startThrowPosition;   // dónde empezó
bool isStuck = false;
glm::vec3 stuckPosition;
glm::vec3 stuckNormal;  // La normal de la superficie donde se clava
float pickupDistance = 11.0f; // Distancia máxima para recoger el hacha


//variables para animación
float movCoche;
//float movOffset;
float rotllanta;
float rotllantaOffset;
float toffsetflechau = 0.0f;
float toffsetflechav = 0.0f;
float toffsetnumerou = 0.0f;
float toffsetnumerov = 0.0f;
float toffsetnumerocambiau = 0.0;
float angulovaria = 0.0f;
bool avanza;

//Variables ejercicio 1
float tiempoAcumulado = 0.0f;  // Acumula el tiempo transcurrido
float intervalo = 50.0f;       // Intervalo

//**********************VARIABLES KAREN**********************//
glm::vec3 posicion;
float rotManos;
float rotManosOffset;
bool manos;

//////////////////////////////////////////////////////////////////////////
//Variables
float terceraBmo = 25.0f;				// Distancia de camara
float terceraFinn = 20.0f;			// Distancia de camara

int numAni = 3;							//Animales por conjunto
float anguloEntreAni = 90.0f;			//Giro de animales


//Variables animacion 
//Animacion compleja pelota
float movZigZag = 0.0f;
float movVert = 0.0f;
float movOffset;
bool dir = true;						//Para cambiar la direccion en el eje y

//Animacion Bote
float movBote;							//Movimiento en el eje x de Vocho
float movBoteOffset;
float giraBote;							//Para dar un giro de 180�
float rotllBote;						//Para las llantas
float rotllBoteOffset;
bool dirBote = true;					//Para cambiar la direccion en el eje x

//Animacion Bus
float movBus;							//Movimiento en el eje x de bus
float movBusOffset;
float giraBus;							//Para dar un giro de 180�
float rotllBus;							//Para las llantas
float rotllBusOffset;
bool dirBus = true;						//Para cambiar la direccion en el eje x



//Ciclos automaticos
//Ciclo automatico Luz Moto
float contaLuzMoto;						//Animacion de prendido y apagado Luz moto
float contaLuzMotoOffset;
bool prendeLuzMoto;						//Para definir si esta prendida o apagada

//Ciclo dia y noche
float solDirZ;							//Direccion en Z del sol
float solDirY;							//Direccion en Y del sol
float solDirYOffset;
bool invierteCiclo;						//Para cambiar entre noche y dia
bool esDeDia;							//Verificar si es de dia


//Animacion Doctor-Perry
float velocidadAnimacion = 0.1f; // Velocidad general
float distanciaRecorrida = 0.0f; // Para controlar el desplazamiento
float distanciaMaxima = 200.0f; // Límite del recorrido
bool avanzando = true; // Dirección del movimiento
float rotacionPersonajes; // Rotación inicial (90 grados)

// Animación del caminar
float faseDoctor = 0.0f;
float fasePerry = glm::pi<float>();
float velocidadPasos = 0.2f;
float amplitudPiernasDoctor = 0.09f;
float amplitudBrazosDoctor = 0.9f;
float amplitudPiernasPerry = 0.9f;
float amplitudBrazosPerry = 0.9;

//Animacion para DADOS
float animDurationDados = 0.2f;
float velocidadRotacion = 90.0f;  //  Una rotación más controlada
float alturaMaxima = 1.5f;        // Salto más pequeño

// Posiciones fijas de los dados sobre la mesa (ajustadas para que estén centradas)
const glm::vec3 posDado1 = glm::vec3(-113.755f, 0.0f, -400.0f);
const glm::vec3 posDado2 = glm::vec3(-113.755f, 0.0f, -400.0f);

// Rotaciones finales
static glm::vec3 rotFinalDado1 = glm::vec3(0.0f);
static glm::vec3 rotFinalDado2 = glm::vec3(0.0f);
float animTimeDados = 0.0f;    // Tiempo acumulado de animación
float alturaDados = 0.0f;

//Animacion para Phineas
float animTimePhineas = 0.0f;
float animDurationPhineas = 30.0f; // Duración de un ciclo completo (2 segundos)
float alturaMaximaPhineas = 1.0f; // Altura máxima del salto
float rotacionBrazo = 0.0f; // Rotación del brazo para saludar

// Animación del humo
float humoTime = 0.0f;
float humoDuration = 80.0f; // Duración de un ciclo completo de humo
float humoScale = 12.0f; // Escala inicial del humo
float humoMaxScale = 12.0f; // Escala máxima del humo
float humoHeight = 90.0f; // Altura inicial del humo
float humoMaxHeight = 90.0f; // Altura máxima del humo
float humoOpacity = 0.7f; // Opacidad inicial

// Animación burbuja de diálogo
float burbujaTime = 0.0f;
float burbujaDuration = 30.0f; // Duración de un ciclo completo
float burbujaOffsetY = 0.0f; // Desplazamiento vertical para efecto de flotación
float burbujaMaxOffset = 0.2f; // Máximo desplazamiento vertical

//VARIABLES INVINCIBLE
//Animacion para Mark
float animTimeMark = 0.0f;
float animDurationMark = 30.0f;
float alturaMaximaMark = 10.0f;
float rotacionBrazoMark = 0.0f;


Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

//Texturas a utilizar en entorno opengl
Texture pisoTexture;
Texture piso;
Texture HumoTexture;
Texture FrasePhineas;


//Modelos a utilizar en entorno opengl
Model Arbol;
Model Arbusto;


//Mundo Finn
Model Prismo;
Model Enchiridion;
Model Topo;
Model Banca;
Model Pizza;
Model Picnic;
Model TiroBlanco;
Model FaroLuz;


//Mundo Invencible
Model Regalos;
Model Bateo;
Model Nave;
Model Baloncesto;
Model Casa_arbol;
Model Faro2;

Model Invencible;
Model Inv_PIzq;
Model Inv_PDer;
Model Inv_BIzq;
Model Inv_BDer;

Model pelota;

//Mundo Bob Esponja

Model PHachas;
Model Hacha;
Model MonedaBob;
Model GloboBob;

//MODELOS ESTATICOS
Model CasaCalamardo;
Model CasaPatricio;
Model PuestoHachas;
Model LamparaBob;
Model PBoliche;
Model Boliche;
Model PGlobos;
Model PTacos;
Model PHamburguesas;
Model PHotdogs;
Model MesaBob;

//NPC PATRICIO
Model Patricio;
Model OjosPatricio;
Model CaballoPatricio;
Model BasePatricio;

//NPC KAREN
Model BaseKaren;
Model CabezaKaren;
Model BDerechoKaren;
Model BIzquierdoKaren;


//Mundo Phineas 
Model Phineas_Cuerpo;
Model Phineas_BrazoDerecho;
Model Phineas_BrazoIzquierdo;
Model Phineas_PiernaDerecha;
Model Phineas_PiernaIzquierda;
Model Banca_M;
Model Laboratorio_M;
Model Escaleras_M;
Model Peluches_M;
Model Limonada_M;
Model Hamburguesa_M;
Model Puesto_dados;
Model Dado1_M;
Model Dado2_M;
Model Mesa_M;
Model Inator_M;
Model Cuerpo_Doctor;
Model PiernaDerecha_Doc;
Model PiernaIzquierda_Doc;
Model Cuerpo_Perry;
Model PiernaD_Perry;
Model PiernaI_Perry;
Model BrazoD_Perry;
Model BrazoI_Perry;
Model Cuerpo_ferb;
Model Brazode_ferb;
Model Brazoizq_ferb;
Model Pieder_ferb;
Model Pieizq_ferb;


//Vehiculos
//Autobus
Model ACha;
Model ALlDDe;
Model ALlDIz;
Model ALlTDe;
Model ALlTIz;
Model BoteBob;

//Personaje
//Finn
Model FCu;
Model FBDe;
Model FBIz;
Model FPDe;
Model FPIz;
Model Mochila;


//Skybox a utilizar en entorno opengl
//Dos tipos para el dia y la noche
Skybox skybox;
Skybox skybox2;

//materiales
Material Material_brillante;
Material Material_opaco;
Material Material_piso;
Material Material_Finn;
Material Material_Enchiridion;
Material Material_Topo;
Material Material_Pizza;
Material Material_Tiro_blanco;
Material Material_Prismo;
Material Material_Banca;
Material Material_Picnic;
Material Material_Arbol;
Material Material_Poste;

Material Material_Peluches;
Material Material_Nave;
Material Material_Bateo;
Material Material_Baloncesto;
Material Material_Casa_eve;
Material Material_Invencible;

Material Material_Puestos;
Material Material_Roca;
Material Material_Hachas;
Material Material_Calamardo;
Material Material_Vehiculos;
Material Material_Boliche;
Material Material_Mesas;
Material Material_Arbusto;

Material Material_Phineas;
Material Material_Ferb;
Material Material_Perry;
Material Material_Doctor;
Material Material_Edificio;
Material Material_Dados;



//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";



//cálculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};
	unsigned int floorIndicesM[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVerticesM[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,
	};

	unsigned int dialogoIndices[] = {
   0, 1, 2,
   0, 2, 3,

	};

	GLfloat dialogoVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f
	};


	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(floorVerticesM, floorIndicesM, 32, 6);
	meshList.push_back(obj5);

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(dialogoVertices, dialogoIndices, 32, 6);
	meshList.push_back(obj6);


	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);



}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


void UpdateCharacterRotationFromCamera(Camera camera)
{
	// Solo copiar el yaw de la cámara al personaje
	characterYaw = -camera.getYaw();
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	static float xChange = 0.0f;
	static float yChange = 0.0f;

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	xChange = xpos - lastX;
	yChange = lastY - ypos; // Invertido: el eje Y de OpenGL va para arriba

	lastX = xpos;
	lastY = ypos;

	camera.mouseControl(xChange, yChange);  // Para la cámara
	UpdateCharacterRotationFromCamera(camera);       // Para el personaje

}

void doMovement(GLfloat deltaTime, Camera& camera)
{


	if (blockMovement)
		return; //No mueve al personaje


	GLfloat velocity = 2.5f * deltaTime;

	// 1. Tomamos el frente de la cámara, pero solo el plano XZ (horizontal)
	glm::vec3 cameraFront = camera.getCameraDirection();
	cameraFront.y = 0.0f;
	cameraFront = glm::normalize(cameraFront);

	// 2. Calculamos izquierda y derecha
	glm::vec3 left = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraFront));
	glm::vec3 right = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));

	// 3. Movimiento
	if (keys[GLFW_KEY_W]) // Adelante
		characterPosition += cameraFront * velocity;
	if (keys[GLFW_KEY_S]) // Atrás
		characterPosition -= cameraFront * velocity;
	if (keys[GLFW_KEY_A]) // Izquierda
		characterPosition += left * velocity;
	if (keys[GLFW_KEY_D]) // Derecha
		characterPosition += right * velocity;
}



void update()
{
	int newZone = -1;

	for (size_t i = 0; i < minigameCenters.size(); ++i)
	{
		float distance = glm::distance(characterPosition, minigameCenters[i]);
		if (distance <= minigameRadius)
		{
			newZone = i;
			break;
		}
	}

	// Si estamos en una nueva zona
	if (newZone != -1 && !isInMinigame)
	{
		isInMinigame = true;
		blockMovement = true;
		currentZone = newZone;
		camera.setFirstPerson();
		// printf("Entraste a la zona %d\n", currentZone);
	}

	if (isInMinigame && keys[GLFW_KEY_Q])
	{
		isInMinigame = false;
		blockMovement = false;
		currentZone = -1;
		camera.setThirdPerson();
		for (size_t i = 0; i < globoPositions.size(); ++i)
		{
			globoAlive[i] = true; // Globo explotado
		}
		//printf("Saliste del minijuego presionando Q\n");
	}

	if (keys[GLFW_KEY_E] && !wasEPressed) { // Solo se activa al presionar (no al mantener)
		if (!isThrowing && !isStuck) {
			// Lanzar el hacha
			isThrowing = true;
			startThrowPosition = camera.getCameraPosition();
			throwPosition = startThrowPosition + camera.getCameraFront() * 1.0f;
			throwDirection = glm::normalize(camera.getCameraFront());
			throwRotation = 0.0f;
			wasEPressed = true;
		}
		else if (isStuck) {
			// Recuperar el hacha si está cerca
			float distanceToAxe = glm::distance(characterPosition, stuckPosition);
			if (distanceToAxe <= pickupDistance) {
				isStuck = false;
				isThrowing = false;
				throwRotation = 0.0f;
				wasEPressed = true;
			}
		}
	}
	else if (!keys[GLFW_KEY_E]) {
		wasEPressed = false; // Resetear al soltar la tecla
	}

	// --- Lógica de movimiento del hacha ---
	if (isThrowing) {
		float distanceTravelled = glm::distance(startThrowPosition, throwPosition);
		if (distanceTravelled >= maxThrowDistance) {
			// Clavar el hacha al alcanzar distancia máxima
			isThrowing = false;
			isStuck = true;
			stuckPosition = throwPosition;
		}
		else {
			// Mover el hacha en vuelo
			throwPosition += throwDirection * throwSpeed * deltaTime;
			throwRotation += throwRotationSpeed * deltaTime;
		}
	}


	for (size_t i = 0; i < globoPositions.size(); ++i)
	{
		if (globoAlive[i]) // Solo globos vivos
		{
			float distance = glm::distance(throwPosition, globoPositions[i]);
			if (distance <= reventarRadio)
			{
				globoAlive[i] = false; // Globo explotado
			}
		}
	}

}


int getCurrentZoneM(glm::vec3 pos) {
	for (int i = 0; i < zones.size(); ++i) {
		const Zone& z = zones[i];
		if (pos.x >= z.min.x && pos.x <= z.max.x &&
			pos.y >= z.min.y && pos.y <= z.max.y &&
			pos.z >= z.min.z && pos.z <= z.max.z) {
			return i;
		}
	}
	return -1; // no estás en ninguna zona
}

void updateMusicByZone(glm::vec3 characterPos) {
	int zoneIndex = getCurrentZoneM(characterPos);

	if (zoneIndex != currentZoneM) {
		// Cambió de zona

		// Detener música anterior
		if (mainMusic && !mainMusic->isFinished()) {
			mainMusic->stop();
			mainMusic->drop();
			mainMusic = nullptr;
		}
		if (areaMusic && !areaMusic->isFinished()) {
			areaMusic->stop();
			areaMusic->drop();
			areaMusic = nullptr;
		}

		if (zoneIndex != -1) {
			// Entró a una zona especial
			areaMusic = soundEngine->play2D(zones[zoneIndex].musicPath.c_str(), true, false, true);
		}
		else {
			// Regresó fuera de las zonas, reproducir música principal
			mainMusic = soundEngine->play2D("Music/finn.mp3", true, false, true);
		}

		currentZoneM = zoneIndex;
	}
}





int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();
	//CAMARA
	mainWindow.setCamera(&camera);
	glfwSetCursorPosCallback(mainWindow.getWindow(), mouse_callback);
	glfwSetKeyCallback(mainWindow.getWindow(), mainWindow.ManejaTeclado);
	glfwSetInputMode(mainWindow.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	CreateObjects();
	CreateShaders();

	//Comprobacion Audio
	if (!soundEngine) {
		printf("No se pudo inicializar irrKlang.\n");
		return 0;
	}

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);
	camera.enableThirdPerson(&characterPosition, glm::vec3(0.0f, 100.0f, 60.0f));

	//********************************CARGA DE TEXTURAS*************************************
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	piso = Texture("Textures/PisoBob.png");
	piso.LoadTextureA();
	HumoTexture = Texture("Textures/humo.png");
	HumoTexture.LoadTextureA();
	FrasePhineas = Texture("Textures/phineas_frase.png");
	FrasePhineas.LoadTextureA();


	//********************************CARGA DE MODELOS*************************************
//Entorno
	FaroLuz = Model();
	FaroLuz.LoadModel("Models/entorno/faroLuz.obj");
	Faro2 = Model();
	Faro2.LoadModel("Models/entorno/faro.obj");


	//FLORA
	Arbol = Model();
	Arbol.LoadModel("Models/entorno/arbol.obj");
	Arbusto = Model();
	Arbusto.LoadModel("Models/entorno/arbusto.obj");

	//Vehiculos
	//Autobus
	ACha = Model();
	ACha.LoadModel("Models/ACha.obj");
	ALlDDe = Model();
	ALlDDe.LoadModel("Models/ALlDDe.obj");
	ALlDIz = Model();
	ALlDIz.LoadModel("Models/ALlDIz.obj");
	ALlTDe = Model();
	ALlTDe.LoadModel("Models/ALlTDe.obj");
	ALlTIz = Model();
	ALlTIz.LoadModel("Models/ALlTIz.obj");

	//Bote
	BoteBob = Model();
	BoteBob.LoadModel("Models/WorldBob/BoteBob.obj");


	//Personajes
	//Finn
	FCu = Model();
	FCu.LoadModel("Models/finn/Cuerpo_finn.obj");
	FBDe = Model();
	FBDe.LoadModel("Models/finn/Bder.obj");
	FBIz = Model();
	FBIz.LoadModel("Models/finn/BIzq.obj");
	FPDe = Model();
	FPDe.LoadModel("Models/finn/PDer.obj");
	FPIz = Model();
	FPIz.LoadModel("Models/finn/PIzq.obj");
	Mochila = Model();
	Mochila.LoadModel("Models/finn/mochila.obj");

	//Mundo Finn
	Prismo = Model();
	Prismo.LoadModel("Models/finn/prismo.obj");
	Enchiridion = Model();
	Enchiridion.LoadModel("Models/finn/enchiridion.obj");
	Topo = Model();
	Topo.LoadModel("Models/finn/topo.obj");
	Banca = Model();
	Banca.LoadModel("Models/finn/Banca.obj");
	Pizza = Model();
	Pizza.LoadModel("Models/finn/pizza.obj");
	Picnic = Model();
	Picnic.LoadModel("Models/finn/picnic.obj");
	TiroBlanco = Model();
	TiroBlanco.LoadModel("Models/finn/tiro_al_blanco.obj");


	//Mundo Invencible
	Regalos = Model();
	Regalos.LoadModel("Models/Invencible/regalos.obj");
	Bateo = Model();
	Bateo.LoadModel("Models/Invencible/bateo.obj");
	Nave = Model();
	Nave.LoadModel("Models/Invencible/nave.obj");
	Baloncesto = Model();
	Baloncesto.LoadModel("Models/Invencible/baloncesto.obj");
	Casa_arbol = Model();
	Casa_arbol.LoadModel("Models/Invencible/casa_eve.obj");

	pelota = Model();
	pelota.LoadModel("Models/Invencible/pelota.obj");

	//Mundo Invencible
	Invencible = Model();
	Invencible.LoadModel("Models/Invencible/mark.obj");
	Inv_PIzq = Model();
	Inv_PIzq.LoadModel("Models/Invencible/mark_PIzq.obj");
	Inv_PDer = Model();
	Inv_PDer.LoadModel("Models/Invencible/mark_PDer.obj");
	Inv_BIzq = Model();
	Inv_BIzq.LoadModel("Models/Invencible/mark_BIzq.obj");
	Inv_BDer = Model();
	Inv_BDer.LoadModel("Models/Invencible/mark_BDer.obj");

	//---------Mundo Bob Esponja----------
	//MODELOS ESTATICOS
	CasaCalamardo = Model();
	CasaCalamardo.LoadModel("Models/WorldBob/Squidwards House.obj");
	CasaPatricio = Model();
	CasaPatricio.LoadModel("Models/WorldBob/CasaPatricio.obj");
	PuestoHachas = Model();
	PuestoHachas.LoadModel("Models/WorldBob/CabinaHacha.obj");
	BoteBob = Model();
	BoteBob.LoadModel("Models/WorldBob/BoteBob.obj");
	LamparaBob = Model();
	LamparaBob.LoadModel("Models/WorldBob/Lampara.obj");
	PBoliche = Model();
	PBoliche.LoadModel("Models/WorldBob/PuestoFeria.obj");
	Boliche = Model();
	Boliche.LoadModel("Models/WorldBob/Boliche.obj");
	PGlobos = Model();
	PGlobos.LoadModel("Models/WorldBob/PuestoFeria.obj");
	PTacos = Model();
	PTacos.LoadModel("Models/WorldBob/PTacosBob.obj");
	PHotdogs = Model();
	PHotdogs.LoadModel("Models/WorldBob/PHotdogsBob.obj");
	PHamburguesas = Model();
	PHamburguesas.LoadModel("Models/WorldBob/PHamburBob.obj");
	MesaBob = Model();
	MesaBob.LoadModel("Models/WorldBob/MesaBob.obj");

	//OBJETOS BOB ESPONJA
	Hacha = Model();
	Hacha.LoadModel("Models/WorldBob/HachaBob.obj");
	MonedaBob = Model();
	MonedaBob.LoadModel("Models/WorldBob/DardoBob.obj");
	GloboBob = Model();
	GloboBob.LoadModel("Models/WorldBob/GloboBob.obj");

	//NPC Patricio
	Patricio = Model();
	Patricio.LoadModel("Models/WorldBob/Patricio/Patricio.obj");
	OjosPatricio = Model();
	OjosPatricio.LoadModel("Models/WorldBob/Patricio/OjosPatricio.obj");
	CaballoPatricio = Model();
	CaballoPatricio.LoadModel("Models/WorldBob/Patricio/CaballoPatricio.obj");
	BasePatricio = Model();
	BasePatricio.LoadModel("Models/WorldBob/Patricio/BasePatricio.obj");

	//NPC KAREN
	BaseKaren = Model();
	BaseKaren.LoadModel("Models/WorldBob/Karen/Base.obj");
	CabezaKaren = Model();
	CabezaKaren.LoadModel("Models/WorldBob/Karen/Cabeza.obj");
	BDerechoKaren = Model();
	BDerechoKaren.LoadModel("Models/WorldBob/Karen/BrazoDerecho.obj");
	BIzquierdoKaren = Model();
	BIzquierdoKaren.LoadModel("Models/WorldBob/Karen/BrazoIzquierdo.obj");


	//---------Mundo Phineas----------

	Phineas_Cuerpo = Model();
	Phineas_Cuerpo.LoadModel("Models/Phineas/Phineas_cuerpo.obj");
	Phineas_BrazoDerecho = Model();
	Phineas_BrazoDerecho.LoadModel("Models/Phineas/Brazo_derecho.obj");
	Phineas_BrazoIzquierdo = Model();
	Phineas_BrazoIzquierdo.LoadModel("Models/Phineas/Brazo_izquierdo.obj");
	Phineas_PiernaDerecha = Model();
	Phineas_PiernaDerecha.LoadModel("Models/Phineas/Pie_derecho.obj");
	Phineas_PiernaIzquierda = Model();
	Phineas_PiernaIzquierda.LoadModel("Models/Phineas/Pie_izquierdo.obj");
	Banca_M = Model();
	Banca_M.LoadModel("Models/Phineas/Banca.obj");
	Laboratorio_M = Model();
	Laboratorio_M.LoadModel("Models/Phineas/laboratorio.obj");
	Escaleras_M = Model();
	Escaleras_M.LoadModel("Models/Phineas/escalera.obj");
	Peluches_M = Model();
	Peluches_M.LoadModel("Models/Phineas/peluches.obj");
	Limonada_M = Model();
	Limonada_M.LoadModel("Models/Phineas/Puesto_limonada.obj");
	Hamburguesa_M = Model();
	Hamburguesa_M.LoadModel("Models/Phineas/Puesto_hamburguesa.obj");
	Dado1_M = Model();
	Dado1_M.LoadModel("Models/Phineas/dado1.obj");
	Dado2_M = Model();
	Dado2_M.LoadModel("Models/Phineas/dado2.obj");
	Puesto_dados = Model();
	Puesto_dados.LoadModel("Models/Phineas/puesto_dados.obj");
	Mesa_M = Model();
	Mesa_M.LoadModel("Models/Phineas/mesa.obj");
	Inator_M = Model();
	Inator_M.LoadModel("Models/Phineas/inator.obj");
	Cuerpo_Doctor = Model();
	Cuerpo_Doctor.LoadModel("Models/Phineas/Cuerpo_doctor.obj");
	PiernaDerecha_Doc = Model();
	PiernaDerecha_Doc.LoadModel("Models/Phineas/PiernaDer_Doctor.obj");
	PiernaIzquierda_Doc = Model();
	PiernaIzquierda_Doc.LoadModel("Models/Phineas/PiernaIzq_Doctor.obj");
	Cuerpo_Perry = Model();
	Cuerpo_Perry.LoadModel("Models/Phineas/Cuerpo_Perry.obj");
	PiernaD_Perry = Model();
	PiernaD_Perry.LoadModel("Models/Phineas/Pie_derechoPerry.obj");
	PiernaI_Perry = Model();
	PiernaI_Perry.LoadModel("Models/Phineas/Pie_izquierdoPerry.obj");
	BrazoD_Perry = Model();
	BrazoD_Perry.LoadModel("Models/Phineas/Brazo_derechoPerry.obj");
	BrazoI_Perry = Model();
	BrazoI_Perry.LoadModel("Models/Phineas/Brazo_izquierdoPerry.obj");
	Cuerpo_ferb = Model();
	Cuerpo_ferb.LoadModel("Models/Phineas/Ferb_Cuerpo.obj");
	Brazode_ferb = Model();
	Brazode_ferb.LoadModel("Models/Phineas/Brazo_derechoFerb.obj");
	Brazoizq_ferb = Model();
	Brazoizq_ferb.LoadModel("Models/Phineas/Brazo_izquierdoFerb.obj");
	Pieder_ferb = Model();
	Pieder_ferb.LoadModel("Models/Phineas/Pie_derechoFerb.obj");
	Pieizq_ferb = Model();
	Pieizq_ferb.LoadModel("Models/Phineas/Pie_izquierdoFerb.obj");



	std::vector<std::string> skyboxFaces;
	std::vector<std::string> skyboxFaces2;

	skyboxFaces.push_back("Textures/Skybox/skybox_3.tga"); //right
	skyboxFaces.push_back("Textures/Skybox/skybox_1.tga"); //left
	skyboxFaces.push_back("Textures/Skybox/skybox_6.tga"); //down
	skyboxFaces.push_back("Textures/Skybox/skybox_5.tga"); //up
	skyboxFaces.push_back("Textures/Skybox/skybox_2.tga"); //front
	skyboxFaces.push_back("Textures/Skybox/skybox_4.tga"); //bh

	skyboxFaces2.push_back("Textures/Skybox/skybox_3_noche.tga"); //right
	skyboxFaces2.push_back("Textures/Skybox/skybox_1_noche.tga"); //left
	skyboxFaces2.push_back("Textures/Skybox/skybox_6_noche.tga"); //down
	skyboxFaces2.push_back("Textures/Skybox/skybox_5_noche.tga"); //up
	skyboxFaces2.push_back("Textures/Skybox/skybox_2_noche.tga"); //front
	skyboxFaces2.push_back("Textures/Skybox/skybox_4_noche.tga"); //bh

	skybox = Skybox(skyboxFaces);
	skybox2 = Skybox(skyboxFaces2);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);
	Material_piso = Material(0.05f, 10);
	Material_Finn = Material(0.0f, 0);
	Material_Enchiridion = Material(1.5f, 40);
	Material_Topo = Material(4.0f, 128);
	Material_Pizza = Material(0.4f, 16);
	Material_Tiro_blanco = Material(4.0f, 128);
	Material_Prismo = Material(1.5f, 64);
	Material_Banca = Material(0.4f, 16);
	Material_Picnic = Material(0.4f, 16);
	Material_Arbol = Material(0.6f, 16);
	Material_Poste = Material(2.0f, 128);
	
	Material_Peluches = Material(4.0f, 128);
	Material_Nave = Material(3.0f, 128);
	Material_Bateo = Material(2.0f, 64);
	Material_Baloncesto = Material(1.0f, 20);
	Material_Casa_eve = Material(0.2f, 10);
	Material_Invencible = Material(8.0f, 200);
	
	Material_Puestos = Material(5.0f, 100);
	Material_Roca = Material(0.1f, 5);
	Material_Hachas = Material(0.4f, 16);
	Material_Calamardo = Material(0.1f, 8);
	Material_Vehiculos = Material(12.0f, 250);
	Material_Boliche = Material(0.4f, 16);
	Material_Mesas = Material(3.0f, 70);
	Material_Arbusto = Material(0.1f, 15);
	
	Material_Edificio = Material(6.0f, 120);
	Material_Phineas = Material(2.0f, 50);
	Material_Ferb = Material(2.0f, 50);
	Material_Perry = Material(2.0f, 50);
	Material_Doctor = Material(2.0f, 50);
	Material_Dados = Material(6.0f, 180);

	//luz direccional, solo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);

	//LUCES PUNTUALES
	//Contador de luces puntuales
	unsigned int pointLightCount = 0;

	//*********************************+***LUZ DE FARO (MUNDO FINN) — más alcance e intensidad*************************************
	pointLights[1] = PointLight(0.99f, 0.99f, 0.10f,     // color amarillo cálido
		10.9f, 9.8f,
		-422.45f, 80.0f, 440.747f,                       // posición
		0.75f, 0.005f, 0.01f);
	pointLightCount++;

	//*********************************+***LUZ DE FARO 2(MUNDO INVINCIBLE)*************************************
	pointLights[0] = PointLight(0.99f, 0.99f, 0.10f,
		10.9f, 9.8f,
		369.329f, 74.0f, 379.272f,
		0.75f, 0.005f, 0.01f);
	pointLightCount++;



	//LUCES SPOTLIGHT
	//Contador de luces spotlight
	unsigned int spotLightCount = 0;



	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	//Variables para animacion de vehiculos
	movBote = 0.0f;
	movBoteOffset = 0.7f;
	rotllBote = 0.0f;
	rotllBoteOffset = 3.5f;

	movBus = 0.0f;
	movBusOffset = 0.7f;
	rotllBus = 0.0f;
	rotllBusOffset = 3.5f;

	//Variable animacion Orbe
	movOffset = 0.05f;


	//ciclo de dia y de noche
	solDirZ = -1.0f;
	solDirY = 0.0f;
	solDirYOffset = 0.1f;
	invierteCiclo = true;
	esDeDia = true;

	lastTime = glfwGetTime(); //Para empezar lo m�s cercano posible a 0

	//Variables Iniciales KAREN
	rotManos = 0.0f;
	rotManosOffset = 0.8f;
	manos = true;

	keys = mainWindow.getsKeys();



	// Reproducir sonido (loop = true)
	//soundEngine->play2D("Music/Island Song.mp3", true);

	mainMusic = soundEngine->play2D("Music/finn.mp3", true, false, true);



	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//luz del sol
		if (esDeDia == true) { //es de d�a 
			if (invierteCiclo == true)
			{
				solDirY -= solDirYOffset * deltaTime;
				solDirZ = -1 - (solDirY / 100);
				if (solDirY <= -100.0f)
				{
					invierteCiclo = false;
				}
			}
			else
			{
				solDirY += solDirYOffset * deltaTime;
				solDirZ = (-1 - (solDirY / 100)) * -1;
				if (solDirY >= 0.0f)
				{
					invierteCiclo = true;
					esDeDia = false;
				}
			}
		}
		else { //es de noche
			if (invierteCiclo == true)
			{
				solDirY += solDirYOffset * deltaTime;
				solDirZ = 1 - (solDirY / 100);
				if (solDirY >= 100.0f)
				{
					invierteCiclo = false;
				}
			}
			else
			{
				solDirY -= solDirYOffset * deltaTime;
				solDirZ = (1 - (solDirY / 100)) * -1;
				if (solDirY <= 0.0f)
				{
					invierteCiclo = true;
					esDeDia = true;
				}
			}
		}


		//Animacion Vehiculos
		//Bote
		if (dirBote == true)
		{
			movBote -= movBoteOffset * deltaTime;
			rotllBote += rotllBoteOffset * deltaTime;
			if (movBote <= -130.0f)
			{
				dirBote = false;
				giraBote = 180.0f;
			}
		}
		else
		{
			movBote += movBoteOffset * deltaTime;
			rotllBote += rotllBoteOffset * deltaTime;
			if (movBote >= 160.0f)
			{
				dirBote = true;
				giraBote = 0.0f;
			}
		}

		//Bus
		if (dirBus == true)
		{
			movBus -= movBusOffset * deltaTime;
			rotllBus += rotllBusOffset * deltaTime;
			if (movBus <= -320.0f)
			{
				dirBus = false;
				giraBus = 180.0f;
			}
		}
		else
		{
			movBus += movBusOffset * deltaTime;
			rotllBus += rotllBusOffset * deltaTime;
			if (movBus >= 250.0f)
			{
				dirBus = true;
				giraBus = 0.0f;
			}
		}


		//Animacion Doctor_Perry
		float desplazamiento = velocidadAnimacion * 10.0f * deltaTime;

		if (avanzando) {
			distanciaRecorrida += desplazamiento;
			if (distanciaRecorrida >= distanciaMaxima) {
				avanzando = false;
				rotacionPersonajes += 180.0f;
			}
		}
		else {
			distanciaRecorrida -= desplazamiento;
			if (distanciaRecorrida <= 0.0f) {
				avanzando = true;
				rotacionPersonajes -= 180.0f;
			}
		}

		faseDoctor += velocidadAnimacion * velocidadPasos * deltaTime;
		fasePerry += velocidadAnimacion * velocidadPasos * deltaTime;


		//Animacion Dados
		if (mainWindow.animacionDadosActiva) {
			animTimeDados += deltaTime;

			if (animTimeDados <= animDurationDados) {
				float progress = animTimeDados / animDurationDados;

				// Movimiento vertical suave 
				alturaDados = sin(progress * 3.14159265f) * alturaMaxima;
			}
			else {
				// Finalizar animación
				mainWindow.animacionDadosActiva = false;
				animTimeDados = 0.0f;
				alturaDados = -1.0f;  // Volver a la altura de la mesa

				// Rotaciones finales aleatorias (múltiplos de 90°)
				rotFinalDado1.x = 0.0f;                    // Sin rotación en X
				rotFinalDado1.y = 90.0f * (rand() % 4);    // Rotación en Y 
				rotFinalDado1.z = 0.0f;                    // Sin rotación en Z

				rotFinalDado2.x = 0.0f;
				rotFinalDado2.y = 90.0f * (rand() % 4);
				rotFinalDado2.z = 0.0f;
			}
		}

		//Caminata Phineas

		animTimePhineas += deltaTime;
		if (animTimePhineas > animDurationPhineas) {
			animTimePhineas -= animDurationPhineas; // Mantiene la suavidad al reiniciar
		}

		// Calcular progreso normalizado 
		float progress = animTimePhineas / animDurationPhineas;

		// Movimiento de salto 
		float alturaPhineas = sin(progress * 3.14159265f) * alturaMaximaPhineas;

		// Rotación del brazo 
		rotacionBrazo = 45.0f * sin(progress * 2 * 3.14159265f); // Saludar dos veces por ciclo

		//Caminata Mark

		animTimeMark += deltaTime;
		if (animTimeMark > animDurationMark) {
			animTimeMark -= animDurationMark; // Mantiene la suavidad al reiniciar
		}

		// Calcular progreso normalizado 
		float progress2 = animTimeMark / animDurationMark;

		// Movimiento de salto 
		float alturaMark = sin(progress * 3.14159265f) * alturaMaximaMark;

		// Rotación del brazo 
		rotacionBrazoMark = 45.0f * sin(progress * 2 * 3.14159265f); // Saludar dos veces por ciclo

		//Animacion Humo
		humoTime += deltaTime;
		if (humoTime > humoDuration) {
			humoTime = 0.0f;
		}


		//Animacion Compleja pelota
		movZigZag += 5.0f * deltaTime;
		if (dir == true)
		{
			movVert += movOffset * deltaTime;

			if (movVert > 8.0f)
			{
				dir = false;
			}
		}
		else if (dir == false)
		{
			movVert -= movOffset * deltaTime;
			if (movVert < 0.0f)
			{
				dir = true;
			}
		}


		float humoProgress = humoTime / humoDuration;

		// Interpolación no lineal 
		humoScale = humoMaxScale * (1.0f - pow(1.0f - humoProgress, 2.0f));
		humoHeight = humoMaxHeight * humoProgress;
		humoOpacity = 0.7f * (1.0f - humoProgress * 0.8f); // El humo se desvanece



		// Animación de flotación de la burbuja

		burbujaTime += deltaTime;
		if (burbujaTime > burbujaDuration) {
			burbujaTime = 0.0f;
		}

		burbujaOffsetY = sin(burbujaTime * 2.0f * 3.14159265f / burbujaDuration) * burbujaMaxOffset;


		//CAMARA
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		doMovement(deltaTime, camera);
		UpdateCharacterRotationFromCamera(camera);
		updateMusicByZone(characterPosition);
		update();


		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (esDeDia) {
			skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		}
		else {
			skybox2.DrawSkybox(camera.calculateViewMatrix(), projection);
		}
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//glm::vec3 lowerLight = camera.getCameraPosition();
		//lowerLight.y -= 0.3f;
		//spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		//shaderList[0].SetDirectionalLight(&mainLight);
		//shaderList[0].SetPointLights(pointLights, pointLightCount);
		//shaderList[0].SetSpotLights(spotLights, spotLightCount);
				//Movimiento de las luces
		//Luces Bus
		if (dirBus) {
			spotLights[0].SetFlash(glm::vec3(movBus - 169.0f, 3.0f, 16.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
		}
		else {
			spotLights[0].SetFlash(glm::vec3(movBus - 109.0f, 3.0f, 16.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		}

		//Luces del Vocho
		if (dirBote) {
			spotLights[1].SetFlash(glm::vec3(movBote - 366.0f, 3.0f, -42.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
		}
		else {
			spotLights[1].SetFlash(glm::vec3(movBote - 346.0f, 3.0f, -42.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		}


		//Establecer direccion del sol 
		mainLight.SetDir(glm::vec3(0.0f, solDirY / 100, solDirZ));

		//movimiento de la luz del orbe
		pointLights[2].SetPLPos(glm::vec3(479.0f, 4.0f + movVert, -22.0f + 3.5 * sin(glm::radians(movZigZag))));

		//informaci�n al shader de fuentes de iluminaci�n
		shaderList[0].SetDirectionalLight(&mainLight);
		if (mainWindow.getOrbePrendido()) {
			shaderList[0].SetPointLights(pointLights, pointLightCount);
		}
		else {
			shaderList[0].SetPointLights(pointLights, pointLightCount - 1);
		}


		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

		//**************************************************************************PISO**************************************************************************

		//Piso 
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));

		model = glm::mat4(1.0);
		modelaux = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(50.0f, 1.0f, 50.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		piso.UseTexture();
		Material_piso.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();


		//****************************************************MundoFinn**************************************************************************

		// Prismo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-268.737f, 0.0f, 155.656f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Prismo.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Prismo.RenderModel();

		// Enchiridion
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-422.45f, 0.0f, 155.656f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Enchiridion.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Enchiridion.RenderModel();

		// Topo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-422.45f, 0.0f, 283.712f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Topo.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Topo.RenderModel();

		// Banca
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-367.979f, 0.0f, 393.627f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Banca.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Banca.RenderModel();

		// Pizzas Jake
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-268.911, 0.0f, 393.627f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Pizza.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Pizza.RenderModel();

		// Picnic
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-159.316f, 0.0f, 393.627f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Picnic.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Picnic.RenderModel();

		// Tiro al blanco
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-113.755f, 0.0f, 283.472f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Tiro_blanco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TiroBlanco.RenderModel();

		// Árbol
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-113.44f, 0.0f, 440.747f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Arbol.RenderModel();

		// Faro de luz
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-422.45f, 0.0f, 440.747f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		FaroLuz.RenderModel();

		

		//**********************************************************Mundo Invencible**************************************************************************
		// --------------------------------------------------

		// Nave
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(111.268f, 0.0f, 155.656f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Nave.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Nave.RenderModel();

		// Regalos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(111.268f, 0.0f, 280.636f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Peluches.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Regalos.RenderModel();

		// Bateo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(268.887f, 0.0f, 384.216f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Bateo.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bateo.RenderModel();

		// Baloncesto
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(394.841f, 0.0f, 280.636f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Baloncesto.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Baloncesto.RenderModel();

		// Casa de Eve
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(394.841f, 0.0f, 155.656f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Casa_eve.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Casa_arbol.RenderModel();

		// Faro de luz 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(397.329f, 0.0f, 396.272f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Poste.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Faro2.RenderModel();

		//Pelota de beisbol
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(269.079f, 12.676f + movVert, 386.221f + 3.5 * sin(glm::radians(movZigZag))));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pelota.RenderModel();


		//------------Invencible----------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(262.718, 0.0f + alturaMark, 218.565f));

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		modelaux = model;
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Invencible.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Invencible.RenderModel();

		//Mark brazo derecho
		model = modelaux;
		model = glm::rotate(model, rotacionBrazoMark * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Invencible.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Inv_BDer.RenderModel();

		//Mark brazo izquierdo
		model = modelaux;
		model = glm::rotate(model, rotacionBrazoMark * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Invencible.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Inv_BIzq.RenderModel();


		//Mark pierna derecha
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Invencible.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Inv_PDer.RenderModel();


		//Mark pierna izquierda
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Invencible.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Inv_PIzq.RenderModel();



		// Mundo Bob Esponja - Renderizado de objetos
		// --------------------------------------------------

		// Casa Patricio
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(394.841f, 0.0f, -386.870f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Roca.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CasaPatricio.RenderModel();

		// Puesto de hachas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(394.841f, 0.0f, -309.245f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Hachas.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuestoHachas.RenderModel();

		// Casa de Calamardo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(394.841f, 0.0f, -226.859f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Calamardo.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CasaCalamardo.RenderModel();		
		
		//Lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(320.0f, 0.0f, -215.859f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Poste.UseMaterial(uniformSpecularIntensity, uniformShininess);
		FaroLuz.RenderModel();

		// Puesto de boliche
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(280.856f, 0.0f, -328.076f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Boliche.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PBoliche.RenderModel();

		// Boliche
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(210.856f, 0.0f, -175.923f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Boliche.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Boliche.RenderModel();

		// Bancas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(340.79f, 0.0f, -181.312f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Banca.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Banca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(198.779f, 0.0f, -181.312f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Banca.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Banca.RenderModel();

		// Mesas Bob (1-3)
		for (const auto& pos : { glm::vec3(190.241f, 0.0f, -242.044f),
								glm::vec3(190.241f, 0.0f, -288.345f),
								glm::vec3(190.241f, 0.0f, -334.314f) }) {
			model = glm::mat4(1.0);
			model = glm::translate(model, pos);
			model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_Mesas.UseMaterial(uniformSpecularIntensity, uniformShininess);
			MesaBob.RenderModel();
		}

		// Botes Bob (1-2)
		for (const auto& pos : { glm::vec3(324.807f, 0.0f, -386.229f),
							   glm::vec3(198.779f, 0.0f, -386.229f) }) {
			model = glm::mat4(1.0);
			model = glm::translate(model, pos);
			model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_Vehiculos.UseMaterial(uniformSpecularIntensity, uniformShininess);
			BoteBob.RenderModel();
		}

		// Puestos de comida
		struct FoodStand {
			glm::vec3 position;
			Model& modelRef;
		};

		std::vector<FoodStand> foodStands = {
			{glm::vec3(161.714f, 0.0f, -387.062f), PHotdogs},
			{glm::vec3(161.714f, 0.0f, -241.536f), PHotdogs},
			{glm::vec3(161.714f, 0.0f, -201.391f), PHotdogs},
			{glm::vec3(161.714f, 0.0f, -287.359f), PTacos},
			{glm::vec3(161.714f, 0.0f, -335.05f), PHamburguesas}
		};

		for (const auto& stand : foodStands) {
			model = glm::mat4(1.0);
			model = glm::translate(model, stand.position);
			model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_Puestos.UseMaterial(uniformSpecularIntensity, uniformShininess);
			stand.modelRef.RenderModel();
		}

		// Arbustos (1-4)
		for (const auto& pos : { glm::vec3(198.779f, 0.0f, -452.841f),
								glm::vec3(172.626f, 0.0f, -452.841f),
								glm::vec3(145.044f, 0.0f, -452.841f),
								glm::vec3(119.41f, 0.0f, -452.841f) }) {
			model = glm::mat4(1.0);
			model = glm::translate(model, pos);
			model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_Arbusto.UseMaterial(uniformSpecularIntensity, uniformShininess);
			Arbusto.RenderModel();
		}


		//Mundo Finn
		// Mundo Phineas - Renderizado de objetos y personajes
				//****************************************************MundoPhineas**************************************************************************
		//---------------Phineas---------

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-220.0, 0.0f + alturaPhineas, -200.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		modelaux = model;
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Phineas.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Phineas_Cuerpo.RenderModel();

		//---------------Phineas brazo derecho---------
		model = modelaux;
		model = glm::rotate(model, rotacionBrazo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Phineas.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Phineas_BrazoDerecho.RenderModel();

		//---------------Phineas brazo izquierdo---------
		model = modelaux;
		model = glm::rotate(model, rotacionBrazo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Phineas.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Phineas_BrazoIzquierdo.RenderModel();


		//---------------Phineas Pierna derecha---------
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Phineas.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Phineas_PiernaDerecha.RenderModel();


		//---------------Phineas pierna izquierda---------
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Phineas.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Phineas_PiernaIzquierda.RenderModel();

		//--------------- Burbuja de diálogo de Phineas ---------

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(
			-215.0f, // A la derecha de Phineas
			alturaPhineas + 25.0f + burbujaOffsetY, // Por encima de su cabeza
			-200.0f)); // Un poco hacia la cámara

		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f)); // Ajusta la forma de la burbuja


		model = glm::rotate(model, sin(burbujaTime * 3.14159265f / burbujaDuration) * 5.0f * toRadians,
			glm::vec3(0.0f, 0.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(uniformColor, 1.0f, 1.0f, 1.0f); // Color blanco
		glUniform1f(uniformSpecularIntensity, 0.3f); // Un poco de brillo
		glUniform1f(uniformShininess, 8.0f);

		FrasePhineas.UseTexture();
		meshList[5]->RenderMesh();

		glDisable(GL_BLEND);


		//---------------FERB---------

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, 9.0f, -370.0f));
		model = glm::scale(model, glm::vec3(14.0f, 14.0f, 14.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Ferb.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Cuerpo_ferb.RenderModel();

		//---------------FERB brazo derecho---------
		model = modelaux;

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		model = glm::rotate(model, rotacionBrazo * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		Material_Ferb.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Brazode_ferb.RenderModel();

		//---------------FERB brazo izquierdo---------
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		model = glm::rotate(model, rotacionBrazo * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		Material_Ferb.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Brazoizq_ferb.RenderModel();


		//--------------FERB Pierna derecha---------
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Ferb.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Pieder_ferb.RenderModel();


		//---------------FERB pierna izquierda---------
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Ferb.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Pieizq_ferb.RenderModel();

		//---------------Banca---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-250, 0.0f, -210.0f));
		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Banca.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Banca_M.RenderModel();

		//---------------Laboratorio---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-422.45, 0.0f, -250.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.6f, 1.6f, 1.6f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Edificio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Laboratorio_M.RenderModel();

		//---------------Laboratorio_Escaleras---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-406.2, 0.0f, -265.4f));
		model = glm::scale(model, glm::vec3(2.2f, 1.6f, 2.2f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Edificio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Escaleras_M.RenderModel();

		//---------------Inator---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-410.5, 67.2f, -258.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Edificio.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Inator_M.RenderModel();

		//---------------Puesto de peluches---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-113.755f, 0.0f, -250.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Peluches.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Peluches_M.RenderModel();

		//---------------Puesto de Limonada---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-250.0f, 0.0f, -430.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Puestos.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Limonada_M.RenderModel();

		//---------------Puesto de hamburguesa---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-422.45, 0.0f, -420.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Puestos.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Hamburguesa_M.RenderModel();

		//--------------- Humo del puesto de hamburguesas ---------
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-422.45, humoHeight, -433.0f)); // Misma posición que el puesto
		model = glm::scale(model, glm::vec3(humoScale, humoScale, humoScale));
		model = glm::rotate(model, (float)glfwGetTime() * 0.5f, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotación lenta
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(uniformSpecularIntensity, 0.1f); // Bajo brillo
		glUniform1f(uniformShininess, 4.0f);
		HumoTexture.UseTexture();
		meshList[3]->RenderMesh(); // Usa el mesh de vegetación que ya tienes


		glDisable(GL_BLEND);

		//---------------Mesa de Hamburguesa---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-370.0, 0.0f, -420.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Mesas.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Mesa_M.RenderModel();

		//---------------Mesa de Hamburguesa---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-370.0, 0.0f, -340.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Mesas.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Mesa_M.RenderModel();

		//---------------Mesa de Hamburguesa---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-422.5, 0.0f, -340.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Mesas.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Mesa_M.RenderModel();


		//---------------Aatraccion de Dados---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-113.755f, 0.0f, -400.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Puestos.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Puesto_dados.RenderModel();


		//--------------- Dado1---------
		model = glm::mat4(1.0f);
		model = glm::translate(model, posDado1); // Posición FIJA

		if (mainWindow.animacionDadosActiva) {
			float angulo = animTimeDados * velocidadRotacion;
			model = glm::rotate(model, angulo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f)); // Solo rotar en Y
		}
		else {
			model = glm::rotate(model, rotFinalDado1.y * toRadians, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotación final en Y
		}

		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Dados.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Dado1_M.RenderModel();

		//--------------- Dado2---------
		model = glm::mat4(1.0f);
		model = glm::translate(model, posDado2); // Posición FIJA

		if (mainWindow.animacionDadosActiva) {
			float angulo = animTimeDados * velocidadRotacion * 1.2f;
			model = glm::rotate(model, angulo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f)); // Solo rotar en Y
		}
		else {
			model = glm::rotate(model, rotFinalDado2.y * toRadians, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotación final en Y
		}

		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Dados.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Dado2_M.RenderModel();


		//--------------- Doctro---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-420.0f, 3.0f, -430.0f + distanciaRecorrida));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, rotacionPersonajes * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		// Rotación inicial + balanceo al caminar
		model = glm::rotate(model, (90.0f + sin(faseDoctor)) * 5.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Doctor.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Cuerpo_Doctor.RenderModel();

		//--------------- Piernas_Doctor---------
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, (sin(faseDoctor) * amplitudPiernasDoctor)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiernaDerecha_Doc.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, sin(faseDoctor + glm::pi<float>()) * amplitudPiernasDoctor));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Doctor.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernaIzquierda_Doc.RenderModel();

		//--------------- Perry---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-313.0f, 4.0f, -415.0f + distanciaRecorrida));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, rotacionPersonajes * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		// Rotación con balanceo
		model = glm::rotate(model, sin(fasePerry) * 5.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Perry.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Cuerpo_Perry.RenderModel();

		//--------------- Extremidades_perry---------
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.0f, 0.0f, sin(fasePerry) * amplitudPiernasPerry));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Perry.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernaD_Perry.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, sin(fasePerry + glm::pi<float>()) * amplitudPiernasPerry));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Perry.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PiernaI_Perry.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, sin(fasePerry + glm::pi<float>()) * amplitudBrazosPerry));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Perry.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoI_Perry.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, sin(fasePerry) * amplitudBrazosPerry));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_Perry.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BrazoD_Perry.RenderModel();


		//**************************************************************************
		// AUTOMOVILES - Renderizado de vehículos y sus componentes
		//**************************************************************************

		// ----------------- BOTE BOB -----------------
		{
			glm::mat4 boatModel = glm::mat4(1.0);
			boatModel = glm::translate(boatModel, glm::vec3(movBote - 356.0f, -0.55f, -42.0f));
			boatModel = glm::rotate(boatModel, glm::radians(giraBote), glm::vec3(0.0f, 1.0f, 0.0f));
			boatModel = glm::rotate(boatModel, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			boatModel = glm::scale(boatModel, glm::vec3(15.0f, 15.0f, 15.0f));

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(boatModel));
			Material_Vehiculos.UseMaterial(uniformSpecularIntensity, uniformShininess);
			BoteBob.RenderModel();
		}

		// ----------------- AUTOBÚS -----------------
		{
			// Modelo base del autobús
			glm::mat4 busModel = glm::mat4(1.0);
			busModel = glm::translate(busModel, glm::vec3(movBus - 139.0f, 11.0f, 16.0f));
			busModel = glm::rotate(busModel, glm::radians(giraBus), glm::vec3(0.0f, 1.0f, 0.0f));
			busModel = glm::scale(busModel, glm::vec3(15.0f, 15.0f, 15.0));

			// Renderizar chasis principal
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(busModel));
			Material_Vehiculos.UseMaterial(uniformSpecularIntensity, uniformShininess);
			ACha.RenderModel();

			// Función para renderizar ruedas
			auto renderWheel = [&](const glm::vec3& offsetPos, Model& wheelModel) {
				glm::mat4 wheel = busModel;
				wheel = glm::translate(wheel, offsetPos);
				wheel = glm::rotate(wheel, rotllBus * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(wheel));
				wheelModel.RenderModel();
				};

			// Posiciones relativas de las ruedas (ajustadas según el chasis)
			const glm::vec3 frontLeftPos(-2.43f, -0.55f, 0.9f);
			const glm::vec3 frontRightPos(-2.43f, -0.55f, -0.8f);
			const glm::vec3 rearLeftPos(2.43f, -0.55f, 0.9f);
			const glm::vec3 rearRightPos(2.43f, -0.55f, -0.8f);

			// Renderizar las cuatro ruedas
			renderWheel(frontLeftPos, ALlDIz);    // Rueda delantera izquierda
			renderWheel(frontRightPos, ALlDDe);   // Rueda delantera derecha
			renderWheel(rearLeftPos, ALlTIz);     // Rueda trasera izquierda
			renderWheel(rearRightPos, ALlTDe);    // Rueda trasera derecha

		}


		//Balanceo de manos
		if (manos) {

			if (rotManos > -30.0f)
			{
				rotManos -= rotManosOffset * deltaTime;
			}
			else {
				manos = false;
			}
		}
		else {
			if (rotManos < 45.0f)
			{
				rotManos += rotManosOffset * deltaTime;
			}
			else {
				manos = true;
			}
		}


		if (camera.isThirdPerson != 2) {

			//CUERPO
			model = glm::mat4(1.0);
			model = glm::translate(model, characterPosition);
			model = glm::translate(model, glm::vec3(0.0f, 13.0f, 0.0f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(characterYaw), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
			modelaux = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_Finn.UseMaterial(uniformSpecularIntensity, uniformShininess);
			FCu.RenderModel();

			//BRAZO DERECHO
			model = modelaux;
			model = glm::translate(model, glm::vec3(-0.831f, 0.381f, -0.015f));
			//model = glm::translate(model, glm::vec3(-0.07f, 1.15f, 0.0f));
			//model = glm::rotate(model, 50 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::rotate(model, rotManos * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_Finn.UseMaterial(uniformSpecularIntensity, uniformShininess);
			FBDe.RenderModel();

			//BRAZO IZQUIERDO
			model = modelaux;
			model = glm::translate(model, glm::vec3(0.777f, 0.381f, 0.015f));
			//model = glm::translate(model, glm::vec3(0.07f, 1.15f, 0.0f));
			//model = glm::rotate(model, -50 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::rotate(model, -rotManos * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_Finn.UseMaterial(uniformSpecularIntensity, uniformShininess);
			FBIz.RenderModel();			
			
			//PIERNA IZQUIERDA
			model = modelaux;
			model = glm::translate(model, glm::vec3(0.647f, -1.798f, 0.002f));
			//model = glm::translate(model, glm::vec3(0.07f, 1.15f, 0.0f));
			//model = glm::rotate(model, -50 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::rotate(model, rotManos * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_Finn.UseMaterial(uniformSpecularIntensity, uniformShininess);
			FPIz.RenderModel();
			
			//PIERNA DERECHA
			model = modelaux;
			model = glm::translate(model, glm::vec3(-0.76f, -1.799f, 0.014f));
			//model = glm::translate(model, glm::vec3(0.07f, 1.15f, 0.0f));
			//model = glm::rotate(model, -50 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::rotate(model, -rotManos * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_Finn.UseMaterial(uniformSpecularIntensity, uniformShininess);
			FPDe.RenderModel();

			//model = modelaux;
			//model = glm::translate(model, posicion + glm::vec3(0.054f, 1.4f, 0.0f));
			//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			//CabezaKaren.RenderModel();

			for (size_t i = 0; i < globoPositions.size(); ++i)
			{
					model = glm::mat4(1.0f);
					model = glm::translate(model, globoPositions[i]);

					// Puedes definir colores según el índice o asignarlos en otro vector si quieres
					if (i == 0 || i == 3) color = glm::vec3(1.0f, 0.0f, 1.0f);
					else if (i == 1 || i == 7) color = glm::vec3(1.0f, 0.0f, 0.0f);
					else if (i == 2 || i == 5 || i == 8) color = glm::vec3(0.0f, 0.0f, 1.0f);
					else if (i == 4) color = glm::vec3(0.0f, 1.0f, 0.0f);
					else if (i == 6) color = glm::vec3(1.0f, 1.0f, 1.0f);
					model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));

					glUniform3fv(uniformColor, 1, glm::value_ptr(color));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					GloboBob.RenderModel();
			}

		}
		else {

			glm::mat4 handModel = glm::mat4(1.0f);

			if (isThrowing)
			{
				// Movimiento mientras vuela
				handModel = glm::translate(handModel, throwPosition);
				handModel = glm::rotate(handModel, -glm::radians(throwRotation), glm::vec3(0.0f, 0.0f, 1.0f)); // Giro al volar

				// Clavado
				handModel = glm::translate(handModel, stuckPosition);
				for (size_t i = 0; i < globoPositions.size(); ++i)
				{
					if (globoAlive[i])
					{
						model = glm::mat4(1.0f);
						model = glm::translate(model, globoPositions[i]);

						// Puedes definir colores según el índice o asignarlos en otro vector si quieres
						if (i == 0 || i == 3) color = glm::vec3(1.0f, 0.0f, 1.0f);
						else if (i == 1 || i == 7) color = glm::vec3(1.0f, 0.0f, 0.0f);
						else if (i == 2 || i == 5 || i == 8) color = glm::vec3(0.0f, 0.0f, 1.0f);
						else if (i == 4) color = glm::vec3(0.0f, 1.0f, 0.0f);
						else if (i == 6) color = glm::vec3(1.0f, 1.0f, 1.0f);
						//model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
						model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));

						glUniform3fv(uniformColor, 1, glm::value_ptr(color));
						glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
						GloboBob.RenderModel();
					}
				}
			}
			else if (isStuck)
			{
				// Clavado
				handModel = glm::translate(handModel, stuckPosition);
				for (size_t i = 0; i < globoPositions.size(); ++i)
				{
					if (globoAlive[i])
					{
						model = glm::mat4(1.0f);
						model = glm::translate(model, globoPositions[i]);

						// Puedes definir colores según el índice o asignarlos en otro vector si quieres
						if (i == 0 || i == 3) color = glm::vec3(1.0f, 0.0f, 1.0f);
						else if (i == 1 || i == 7) color = glm::vec3(1.0f, 0.0f, 0.0f);
						else if (i == 2 || i == 5 || i == 8) color = glm::vec3(0.0f, 0.0f, 1.0f);
						else if (i == 4) color = glm::vec3(0.0f, 1.0f, 0.0f);
						else if (i == 6) color = glm::vec3(1.0f, 1.0f, 1.0f);
						//model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
						model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));


						glUniform3fv(uniformColor, 1, glm::value_ptr(color));
						glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
						GloboBob.RenderModel();
					}
				}
			}
			else
			{
				// Mano normal
				glm::vec3 handOffset(0.3f, 1.0f, 1.0f);
				handModel = glm::translate(handModel, camera.getCameraPosition() + camera.getCameraFront() * handOffset.z + camera.getCameraRight() * handOffset.x + camera.getCameraUp() * handOffset.y);
				handModel = glm::rotate(handModel, -glm::radians(camera.getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));

				// Clavado
				handModel = glm::translate(handModel, stuckPosition);
				for (size_t i = 0; i < globoPositions.size(); ++i)
				{
					if (globoAlive[i])
					{
						model = glm::mat4(1.0f);
						model = glm::translate(model, globoPositions[i]);

						// Puedes definir colores según el índice o asignarlos en otro vector si quieres
						if (i == 0 || i == 3) color = glm::vec3(1.0f, 0.0f, 1.0f);
						else if (i == 1 || i == 7) color = glm::vec3(1.0f, 0.0f, 0.0f);
						else if (i == 2 || i == 5 || i == 8) color = glm::vec3(0.0f, 0.0f, 1.0f);
						else if (i == 4) color = glm::vec3(0.0f, 1.0f, 0.0f);
						else if (i == 6) color = glm::vec3(1.0f, 1.0f, 1.0f);
						model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));

						glUniform3fv(uniformColor, 1, glm::value_ptr(color));
						glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
						GloboBob.RenderModel();
					}
				}
			}

			handModel = glm::scale(handModel, glm::vec3(10.0f, 10.0f, 10.0f)); // Tamaño
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(handModel));

			// Renderizamos el modelo
			if (currentZone == 0) {
				Hacha.RenderModel();
			}
			else if (currentZone == 1) {
				MonedaBob.RenderModel();
			}


		}


		glDisable(GL_BLEND);
		
		



		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
