/*
Proyecto
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

//para iluminaci�n
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

//Variables
float terceraBmo = 25.0f;				// Distancia de camara
float terceraFinn = 20.0f;			// Distancia de camara

int numAni = 3;							//Animales por conjunto
float anguloEntreAni = 90.0f;			//Giro de animales

float distanciaEntrePollos = 2.0f;		//Espacio entre cada Pollo
float distanciaEntreOvejas = 4.0f;		//Espacio entre cada Oveja
float distanciaEntreCrab = 3.0f;		// Espacio entre cada crab
float distanciaEntreFrutas = -10.0f;	// Espacio entre cada fruta en el eje z
float distanciaEntreHongos = -5.0f;		// Espacio entre cada hongo en el eje x

int numCrab = 6;						//6x6 = 36 crabmeats
int numFrutas = 13;						//N�mero de frutas a crear

int numHongos = 92;						// N�mero de Hongos a crear

//Variables animacion 
//Animacion compleja Orbe
float movZigZag = 0.0f;					//Movimiento en el eje z de Orbe
float movVert = 0.0f;					//Movimiento en el eje y de Orbe
float movOffset;
bool dir = true;						//Para cambiar la direccion en el eje y

//Animacion Vocho
float movVoch;							//Movimiento en el eje x de Vocho
float movVochOffset;
float giraVoch;							//Para dar un giro de 180�
float rotllVoch;						//Para las llantas
float rotllVochOffset;
bool dirVoch = true;					//Para cambiar la direccion en el eje x

//Animacion Bus
float movBus;							//Movimiento en el eje x de bus
float movBusOffset;
float giraBus;							//Para dar un giro de 180�
float rotllBus;							//Para las llantas
float rotllBusOffset;
bool dirBus = true;						//Para cambiar la direccion en el eje x

//Animacion Moto
float movMoto;							//Movimiento en el eje x de moto
float movMotoOffset;
float giraMoto;							//Para dar un giro de 180�
float rotllMoto;						//Para las llantas
float rotllMotoOffset;
bool dirMoto = true;					//Para cambiar la direccion en el eje x

//Animacion basica MotoBug
bool dirAnimBas;						//Direccion de motobug
float movAnimBas;						//Movimiento de motobug
float movAnimBasOffset = true;

//Animacion basica Mineral
float movAnimBas2;						//Movimiento de Mineral
float movAnimBas2Offset = true;

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
// Variables para la animación
float velocidadAnimacion = 0.1f; // Velocidad general
float distanciaRecorrida = 0.0f; // Para controlar el desplazamiento
const float distanciaMaxima = 200.0f; // Límite del recorrido
bool avanzando = true; // Dirección del movimiento

// Animación del caminar
float faseDoctor = 0.0f;
float fasePerry = glm::pi<float>();
const float velocidadPasos = 2.5f;
const float amplitudPiernasDoctor = 10.0f;
const float amplitudBrazosDoctor = 6.0f;
const float amplitudPiernasPerry = 7.0f;
const float amplitudBrazosPerry = 8.0f;




Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

//Camaras
Camera camera;
Camera finn;
Camera sonic;

//Texturas a utilizar en entorno opengl
Texture pisoTexture;	//Textura de piso (pavimento)
Texture pisoFinn;
Texture pisoInvencible;
Texture pisoBob;
Texture pisoPhineas;
//Modelos a utilizar en entorno opengl

//Mundo Finn
Model Prismo;
Model Enchiridion;
Model Topo;
Model Banca;
Model Pizza;
Model Picnic;
Model TiroBlanco;
Model Arco;
Model Letrero;


//Mundo Invencible
Model Regalos;
Model Bateo;
Model Nave;
Model Baloncesto;
Model Casa_arbol;

//Mundo Bob Esponja
//MODELOS ESTATICOS
Model CasaCalamardo;
Model CasaPatricio;
Model PuestoHachas;
Model BoteBob;
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


//Objetos
Model Mineral;
Model FruHa;
Model Orbe;
Model Pollo;
Model Oveja;

Model Motobug;
Model Crabmeat;
Model Joya;
Model Cofre;
Model Oro;
Model HongoM;

//Vehiculos
//Vochito
Model VCha;
Model VCof;
Model VLlDDe;
Model VLlDIz;
Model VLlTDe;
Model VLlTIz;

//Autobus
Model ACha;
Model ALlDDe;
Model ALlDIz;
Model ALlTDe;
Model ALlTIz;

//Moto
Model MCha;
Model MLl;

//Personaje
//Finn
Model FCu;
Model FBDe;
Model FBIz;
Model FPDe;
Model FPIz;
Model Mochila;

//Sonic
Model SCu;
Model SBDe;
Model SBIz;
Model SPDe;
Model SPIz;

//Skybox a utilizar en entorno opengl
//Dos tipos para el dia y la noche
Skybox skybox;
Skybox skybox2;

//Materiales a utilizar en entorno opengl
Material Material_brillante;
Material Material_opaco;

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


//funci�n de calculo de normales por promedio de v�rtices 
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

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 400.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), -90.0f, -90.0f, 0.3f, 0.5f);
	finn = Camera(glm::vec3(-220.0f, 9.0f, 61.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 0.3f, 0.5f);
	sonic = Camera(glm::vec3(201.0f, 10.0f, 27.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f, 0.3f, 0.5f);

	//********************************CARGA DE TEXTURAS*************************************
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	pisoFinn = Texture("Textures/piso.png");
	pisoFinn.LoadTextureA();
	pisoInvencible = Texture("Textures/piso_invencible.png");
	pisoInvencible.LoadTextureA();
	pisoBob = Texture("Textures/PisoBob.png");
	pisoBob.LoadTextureA();
	pisoPhineas = Texture("Textures/piso_phineas.png");
	pisoPhineas.LoadTextureA();

	//********************************CARGA DE MODELOS*************************************
	//Objetos
	

	

	Mineral = Model();
	Mineral.LoadModel("Models/Mineral.obj");

	Orbe = Model();
	Orbe.LoadModel("Models/Orbe.obj");

	Motobug = Model();
	Motobug.LoadModel("Models/ModelosAle/motobug.obj");

	

	Joya = Model();
	Joya.LoadModel("Models/ModelosAle/joya.obj");

	Cofre = Model();
	Cofre.LoadModel("Models/ModelosAle/cofre.obj");



	Oro = Model();
	Oro.LoadModel("Models/ModelosAle/lingote_oro.obj");

	

	//FLORA
	FruHa = Model();
	FruHa.LoadModel("Models/FruHa.obj");

	

	HongoM = Model();
	HongoM.LoadModel("Models/ModelosAle/hongo_magico.obj");

	//FAUNA
	Crabmeat = Model();
	Crabmeat.LoadModel("Models/ModelosAle/crabmeat.obj");

	Pollo = Model();
	Pollo.LoadModel("Models/Pollo.obj");

	Oveja = Model();
	Oveja.LoadModel("Models/Oveja.obj");

	//Vehiculos
	//Vochito
	VCha = Model();
	VCha.LoadModel("Models/VCha.obj");

	VCof = Model();
	VCof.LoadModel("Models/VCof.obj");

	VLlDDe = Model();
	VLlDDe.LoadModel("Models/VLlDDe.obj");

	VLlDIz = Model();
	VLlDIz.LoadModel("Models/VLlDIz.obj");

	VLlTDe = Model();
	VLlTDe.LoadModel("Models/VLlTDe.obj");

	VLlTIz = Model();
	VLlTIz.LoadModel("Models/VLlTIz.obj");

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

	//Moto
	MCha = Model();
	MCha.LoadModel("Models/ModelosAle/moto_cuerpo.obj");

	MLl = Model();
	MLl.LoadModel("Models/ModelosAle/moto_llanta.obj");

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

	//Sonic
	SCu = Model();
	SCu.LoadModel("Models/ModelosAle/sonic_cuerpo.obj");

	SBDe = Model();
	SBDe.LoadModel("Models/ModelosAle/sonic_brazo_derecho.obj");

	SBIz = Model();
	SBIz.LoadModel("Models/ModelosAle/sonic_brazo_izquierdo.obj");

	SPDe = Model();
	SPDe.LoadModel("Models/ModelosAle/sonic_pierna_derecha.obj");

	SPIz = Model();
	SPIz.LoadModel("Models/ModelosAle/sonic_pierna_izquierda.obj");

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

	Arco = Model();
	Arco.LoadModel("Models/finn/arco_opt.obj");

	Letrero = Model();
	Letrero.LoadModel("Models/finn/Letrero.obj");


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

	//luz direccional, s�lo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);

	//LUCES PUNTUALES
	//Contador de luces puntuales
	unsigned int pointLightCount = 0;

	//*********************************+***LUZ DE LA JOYA*************************************
	pointLights[0] = PointLight(0.3f, 0.3f, 1.0f,
		0.0f, 1.0f,
		244.0f, 15.0f, -114.0f,
		0.0075f, 0.005f, 0.0025f);
	pointLightCount++;
	//*********************************+***LUZ DEL ORO*************************************
	pointLights[1] = PointLight(1.0f, 1.0f, 0.3f,
		0.5f, 0.001f,
		-417.0f, 3.0f, 232.0f,
		0.75f, 0.005f, 0.01f);
	pointLightCount++;
	//*********************************+***LUZ DEL ORBE*************************************
	pointLights[2] = PointLight(0.3f, 1.0f, 0.3f,
		0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		0.0075f, 0.01f, 0.005f);
	pointLightCount++;


	//LUCES SPOTLIGHT
	//Contador de luces spotlight
	unsigned int spotLightCount = 0;

	//Primera luz Spotlight
	//*********************************+***LUZ DEL CARRO*************************************
	spotLights[0] = SpotLight(0.3f, 0.3f, 1.0f,
		1.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0003f, 0.0002f,
		15.0f);
	spotLightCount++;
	//*********************************+***LUZ DEL VOCHO*************************************
	spotLights[1] = SpotLight(1.0f, 1.0f, 0.3f,
		1.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0003f, 0.0002f,
		15.0f);
	spotLightCount++;
	//*********************************+***LUZ DEL VOCHO*************************************
	spotLights[2] = SpotLight(1.0f, 0.3f, 0.3f,
		1.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0003f, 0.0002f,
		15.0f);
	spotLightCount++;

	//Continuar para m�s luces

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	//Loop mientras no se cierra la ventana

	//Variables para animacion de vehiculos
	movVoch = 0.0f;
	movVochOffset = 0.7f;
	rotllVoch = 0.0f;
	rotllVochOffset = 3.5f;

	movMoto = 0.0f;
	movMotoOffset = 0.7f;
	rotllMoto = 0.0f;
	rotllMotoOffset = 3.5f;

	movBus = 0.0f;
	movBusOffset = 0.7f;
	rotllBus = 0.0f;
	rotllBusOffset = 3.5f;

	//Variable animacion Orbe
	movOffset = 0.05f;

	//Variables para el movimiento de los motobugs y mineral
	dirAnimBas = true;
	movAnimBas = 0.0f;
	movAnimBasOffset = 0.05f;

	movAnimBas2 = 0.0f;
	movAnimBas2Offset = 0.5f;

	//Apagado y prendido autom�tico de la luz de la moto
	contaLuzMoto = 0.0f;
	contaLuzMotoOffset = 1.0;
	prendeLuzMoto = true;

	//ciclo de dia y de noche
	solDirZ = -1.0f;
	solDirY = 0.0f;
	solDirYOffset = 0.1f;
	invierteCiclo = true;
	esDeDia = true;


	lastTime = glfwGetTime(); //Para empezar lo m�s cercano posible a 0

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


		//Algoritmos de animacion
		// Animacion de los motobugs
		if (dirAnimBas == true)
		{
			movAnimBas += movAnimBasOffset * deltaTime;

			if (movAnimBas > 15.0f)
			{
				dirAnimBas = false;
			}
		}
		else if (dirAnimBas == false)
		{
			movAnimBas -= movAnimBasOffset * deltaTime;
			if (movAnimBas < 0.0f)
			{
				dirAnimBas = true;
			}
		}
		//Animacion Mineral
		movAnimBas2 += movAnimBas2Offset * deltaTime;

		//Animacion Compleja Orbe
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

		//Animacion Vehiculos
		//Vocho
		if (dirVoch == true)
		{
			movVoch -= movVochOffset * deltaTime;
			rotllVoch += rotllVochOffset * deltaTime;
			if (movVoch <= -130.0f)
			{
				dirVoch = false;
				giraVoch = 180.0f;
			}
		}
		else
		{
			movVoch += movVochOffset * deltaTime;
			rotllVoch += rotllVochOffset * deltaTime;
			if (movVoch >= 160.0f)
			{
				dirVoch = true;
				giraVoch = 0.0f;
			}
		}
		//Moto
		if (dirMoto == true)
		{
			movMoto += movMotoOffset * deltaTime;
			rotllMoto += rotllMotoOffset * deltaTime;
			if (movMoto >= 100.0f)
			{
				dirMoto = false;
				giraMoto = 180.0f;
			}
		}
		else
		{
			movMoto -= movMotoOffset * deltaTime;
			rotllMoto += rotllMotoOffset * deltaTime;
			if (movMoto <= -150.0f)
			{
				dirMoto = true;
				giraMoto = 0.0f;
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

		//luz moto
		if (prendeLuzMoto == true)
		{
			contaLuzMoto -= contaLuzMotoOffset * deltaTime;
			if (contaLuzMoto <= -100.0f)
			{
				prendeLuzMoto = false;
			}
		}
		else
		{
			contaLuzMoto += contaLuzMotoOffset * deltaTime;
			if (contaLuzMoto >= 0.0f)
			{
				prendeLuzMoto = true;
			}
		}
		
		float desplazamiento = velocidadAnimacion * 15.0f * deltaTime;

		if (avanzando) {
			distanciaRecorrida += desplazamiento;
			if (distanciaRecorrida >= distanciaMaxima) {
				avanzando = false;
			}
		}
		else {
			distanciaRecorrida -= desplazamiento;
			if (distanciaRecorrida <= 0.0f) {
				avanzando = true;
			}
		}

		faseDoctor += velocidadAnimacion * velocidadPasos * deltaTime;
		fasePerry += velocidadAnimacion * velocidadPasos * deltaTime;
		//Recibir eventos del usuario
		glfwPollEvents();

		//Camaras y controles asignados
		if (mainWindow.getopcion() == 0.0f)
		{
			finn.keyControlDep(mainWindow.getsKeys(), deltaTime);
			finn.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		}
		else if (mainWindow.getopcion() == 1.0f)
		{
			sonic.keyControlSon(mainWindow.getsKeys(), deltaTime);
			sonic.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		}
		else if (mainWindow.getopcion() == 2.0f)
		{
			//Para solo mover con teclado sin mouse
			camera.keyControl(mainWindow.getsKeys(), deltaTime);
		}

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Para decidir que ven las camaras
		if (esDeDia) {
			if (mainWindow.getopcion() == 0.0f)
			{
				skybox.DrawSkybox(finn.calculateViewMatrix(), projection);
			}
			else if (mainWindow.getopcion() == 1.0f)
			{
				skybox.DrawSkybox(sonic.calculateViewMatrix(), projection);
			}
			else if (mainWindow.getopcion() == 2.0f)
			{
				skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
			}
		}
		else {
			if (mainWindow.getopcion() == 0.0f)
			{
				skybox2.DrawSkybox(finn.calculateViewMatrix(), projection);
			}
			else if (mainWindow.getopcion() == 1.0f)
			{
				skybox2.DrawSkybox(sonic.calculateViewMatrix(), projection);
			}
			else if (mainWindow.getopcion() == 2.0f)
			{
				skybox2.DrawSkybox(camera.calculateViewMatrix(), projection);
			}
		}


		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//informaci�n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		//Cambiar entre camaras y guardar su posicion
		if (mainWindow.getopcion() == 0.0f)
		{
			glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(finn.calculateViewMatrix()));
			glUniform3f(uniformEyePosition, finn.getCameraPosition().x, finn.getCameraPosition().y, finn.getCameraPosition().z);
		}
		else if (mainWindow.getopcion() == 1.0f)
		{
			glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(sonic.calculateViewMatrix()));
			glUniform3f(uniformEyePosition, sonic.getCameraPosition().x, sonic.getCameraPosition().y, sonic.getCameraPosition().z);
		}
		else if (mainWindow.getopcion() == 2.0f)
		{

			glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
			glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);
		}

		//Movimiento de las luces
		//Luces Bus
		if (dirBus) {
			spotLights[0].SetFlash(glm::vec3(movBus - 169.0f, 3.0f, 16.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
		}
		else {
			spotLights[0].SetFlash(glm::vec3(movBus - 109.0f, 3.0f, 16.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		}

		//Luces del Vocho
		if (dirVoch) {
			spotLights[1].SetFlash(glm::vec3(movVoch - 366.0f, 3.0f, -42.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
		}
		else {
			spotLights[1].SetFlash(glm::vec3(movVoch - 346.0f, 3.0f, -42.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		}

		//Luces la moto
		if (dirMoto) {
			spotLights[2].SetFlash(glm::vec3(movMoto + 47.0f, 3.6f, -40.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else {
			spotLights[2].SetFlash(glm::vec3(movMoto + 47.0f, 3.6f, -40.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
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

		if (prendeLuzMoto == true) {
			shaderList[0].SetSpotLights(spotLights, spotLightCount);
		}
		else {
			shaderList[0].SetSpotLights(spotLights, spotLightCount - 1);
		}


		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		//**************************************************************************PISO**************************************************************************
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(50.0f, 1.0f, 50.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();


		//Piso finn
		model = glm::mat4(1.0);
		modelaux = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-268.06f, -0.98f, 279.844f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoFinn.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[4]->RenderMesh();

		//Piso Invencible
		model = glm::mat4(1.0);
		modelaux = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(269.04f, -0.98f, 279.844f));
		model = glm::scale(model, glm::vec3(20.0f, 23.0f, 20.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoInvencible.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[4]->RenderMesh();


		//Piso phineas
		model = glm::mat4(1.0);
		modelaux = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-269.04f, -0.98f, -330.844f));
		model = glm::scale(model, glm::vec3(20.0f, 23.0f, 15.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoPhineas.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();


		//****************************************************MundoFinn**************************************************************************

		//Prismo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-268.737f, 0.0f, 155.656f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Prismo.RenderModel();
		glDisable(GL_BLEND);


		//Enchiridion
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-422.45f, 0.0f, 155.656f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Enchiridion.RenderModel();
		glDisable(GL_BLEND);


		//Topo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-422.45f, 0.0f, 283.712f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Topo.RenderModel();
		glDisable(GL_BLEND);


		//Banca
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-367.979f, 0.0f, 393.627f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Banca.RenderModel();
		glDisable(GL_BLEND);

		//Pizzas jake
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-268.911, 0.0f, 393.627f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Pizza.RenderModel();
		glDisable(GL_BLEND);


		//Picnic
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-159.316f, 0.0f, 393.627f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Picnic.RenderModel();
		glDisable(GL_BLEND);

		//Tiro al blanco
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-113.755f, 0.0f, 283.472f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		TiroBlanco.RenderModel();
		glDisable(GL_BLEND);

		//Arco
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-113.44f, 0.0f, 155.656f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Arco.RenderModel();
		glDisable(GL_BLEND);

		//Letrero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-113.44f, 0.0f, 155.656f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Letrero.RenderModel();
		glDisable(GL_BLEND);


		//**********************************************************Mundo Invencible**************************************************************************

		//Nave
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(111.268f, 0.0f, 155.656f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Nave.RenderModel();
		glDisable(GL_BLEND);

		//Regalos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(111.268f, 0.0f, 280.636f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Regalos.RenderModel();
		glDisable(GL_BLEND);

		//Bateo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(268.887f, 0.0f, 384.216f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bateo.RenderModel();
		glDisable(GL_BLEND);


		//Baloncesto
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(394.841f, 0.0f, 280.636f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Baloncesto.RenderModel();
		glDisable(GL_BLEND);

		//Casa de eve
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(394.841f, 0.0f, 155.656f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Casa_arbol.RenderModel();
		glDisable(GL_BLEND);


		//**********************************************************Mundo Bob esponja**************************************************************************

		//Casa patricio
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(394.841f, 0.0f, -386.870f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CasaPatricio.RenderModel();
		glDisable(GL_BLEND);

		//Puesto de hachas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(394.841f, 0.0f, -309.245f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PuestoHachas.RenderModel();
		glDisable(GL_BLEND);

		//Casa de calamardo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(394.841f, 0.0f, -226.859f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CasaCalamardo.RenderModel();
		glDisable(GL_BLEND);

		//Puesto de boliche
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(280.856f, 0.0f, -328.076f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PBoliche.RenderModel();
		glDisable(GL_BLEND);

		//Boliche
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(280.856f, 0.0f, -299.923f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Boliche.RenderModel();
		glDisable(GL_BLEND);

		//Banca 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(340.79f, 0.0f, -181.312f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Banca.RenderModel();
		glDisable(GL_BLEND);

		//Banca 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(198.779f, 0.0f, -181.312f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Banca.RenderModel();
		glDisable(GL_BLEND);

		//Mesa bob 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(190.241f, 0.0f, -242.044f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MesaBob.RenderModel();
		glDisable(GL_BLEND);

		//Mesa bob 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(190.241f, 0.0f, -288.345f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MesaBob.RenderModel();
		glDisable(GL_BLEND);

		//Mesa bob 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(190.241f, 0.0f, -334.314f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MesaBob.RenderModel();
		glDisable(GL_BLEND);

		//Bote bob 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(324.807f, 0.0f, -386.229f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BoteBob.RenderModel();
		glDisable(GL_BLEND);

		//Bote bob 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(198.779f, 0.0f, -386.229f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BoteBob.RenderModel();
		glDisable(GL_BLEND);

		//Puesto de hotdogs 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(161.714f, 0.0f, -387.062f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PHotdogs.RenderModel();
		glDisable(GL_BLEND);

		//Puesto de hotdogs 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(161.714f, 0.0f, -241.536f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PHotdogs.RenderModel();
		glDisable(GL_BLEND);

		//Puesto de hotdogs 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(161.714f, 0.0f, -201.391f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PHotdogs.RenderModel();
		glDisable(GL_BLEND);

		//Puesto tacos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(161.714f, 0.0f, -287.359f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PTacos.RenderModel();
		glDisable(GL_BLEND);

		//Puesto hamburguesas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(161.714f, 0.0f, -335.05f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PHamburguesas.RenderModel();
		glDisable(GL_BLEND);

		//**************************************************************************PERSONAJES**************************************************************************

		//Finn
		//Cuerpo
		glm::vec3 camaraFinn = finn.getCameraDirection();
		glm::vec3 finnPos = finn.getCameraPosition() + terceraFinn * camaraFinn;
		finnPos.y -= 6.0f;

		model = glm::mat4(1.0f);
		model = glm::translate(model, finnPos);
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getgiroIzFinn()), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getgiroDeFinn()), glm::vec3(0.0f, 1.0f, 0.0f));

		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FCu.RenderModel();

		//Mochila
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.058f, 0.245f, -0.832f));
		model = glm::rotate(model, glm::radians(mainWindow.getgiroIzFinn()), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getgiroDeFinn()), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mochila.RenderModel();

		//Brazo Izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.777f, 0.381f, 0.015f));
		model = glm::rotate(model, glm::radians(mainWindow.getmovFinn()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getmovFinn()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FBIz.RenderModel();

		//Brazo Derecho
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.831f, 0.381f, -0.015f));
		model = glm::rotate(model, glm::radians(-mainWindow.getmovFinn()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-mainWindow.getmovFinn()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FBDe.RenderModel();

		//Pierna Izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.647f, -1.798f, 0.002f));
		model = glm::rotate(model, glm::radians(mainWindow.getmovFinn()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getmovFinn()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FPIz.RenderModel();


		//Pierna Derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.76f, -1.799f, 0.014f));
		model = glm::rotate(model, glm::radians(-mainWindow.getmovFinn()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-mainWindow.getmovFinn()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FPDe.RenderModel();

		//SONIC
		//Cuerpo
		glm::vec3 camaraSonic = sonic.getCameraDirection();
		glm::vec3 sonicPos = sonic.getCameraPosition() + terceraBmo * camaraSonic;
		sonicPos.y -= 8.0f;

		model = glm::mat4(1.0);
		model = glm::translate(model, sonicPos);
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = glm::rotate(model, glm::radians(mainWindow.getgiroIzSonic()), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getgiroDeSonic()), glm::vec3(0.0f, 1.0f, 0.0f));

		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SCu.RenderModel(); //variable con el modelo del cuerpo de la moto

		//Brazo izquierdo
		model = modelaux; //reinicia la matriz auxiliar para la jerarquia
		model = glm::translate(model, glm::vec3(0.1f, 0.4f, 0.8f));
		model = glm::rotate(model, glm::radians(-mainWindow.getmovSonic()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(-mainWindow.getmovSonic()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SBIz.RenderModel();

		//Brazo derecho
		model = modelaux; //reinicia la matriz auxiliar para la jerarquia
		model = glm::translate(model, glm::vec3(0.1f, 0.4f, -0.7f));
		model = glm::rotate(model, glm::radians(mainWindow.getmovSonic()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getmovSonic()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SBDe.RenderModel();

		//Pierna izquierda
		model = modelaux; //reinicia la matriz auxiliar para la jerarquia
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.3f));
		model = glm::rotate(model, glm::radians(mainWindow.getmovSonic()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getmovSonic()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SPIz.RenderModel();

		//Pierna derecha
		model = modelaux; //reinicia la matriz auxiliar para la jerarquia
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -0.3f));
		model = glm::rotate(model, glm::radians(-mainWindow.getmovSonic()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(-mainWindow.getmovSonic()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SPDe.RenderModel();





		//****************************************************MundoPhineas**************************************************************************
		//---------------Phineas---------

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, -3.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		modelaux = model;
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Phineas_Cuerpo.RenderModel();

		//---------------Phineas brazo derecho---------
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Phineas_BrazoDerecho.RenderModel();

		//---------------Phineas brazo izquierdo---------
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Phineas_BrazoIzquierdo.RenderModel();


		//---------------Phineas Pierna derecha---------
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Phineas_PiernaDerecha.RenderModel();


		//---------------Phineas pierna izquierda---------
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Phineas_PiernaIzquierda.RenderModel();

		//---------------Banca---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-250, 0.0f, -210.0f));
		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca_M.RenderModel();

		//---------------Laboratorio---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-422.45, 0.0f, -250.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.6f, 1.6f, 1.6f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Laboratorio_M.RenderModel();

		//---------------Laboratorio_Escaleras---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-406.2, 0.0f, -265.4f));

		model = glm::scale(model, glm::vec3(2.2f, 1.6f, 2.2f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Escaleras_M.RenderModel();

		//---------------Inator---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-410.5, 67.2f, -258.0f));

		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Inator_M.RenderModel();

		//---------------Puesto de peluches---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-113.755f, 0.0f, -250.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Peluches_M.RenderModel();

		//---------------Puesto de Limonada---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-250.0f, 0.0f, -430.0f));

		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Limonada_M.RenderModel();

		//---------------Puesto de hamburguesa---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-422.45, 0.0f, -420.0f));

		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hamburguesa_M.RenderModel();

		//---------------Mesa de Hamburguesa---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-370.0, 0.0f, -420.0f));

		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_M.RenderModel();

		//---------------Mesa de Hamburguesa---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-370.0, 0.0f, -340.0f));

		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_M.RenderModel();

		//---------------Mesa de Hamburguesa---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-422.5, 0.0f, -340.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_M.RenderModel();


		//---------------Aatraccion de Dados---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-113.755f, 0.0f, -400.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Puesto_dados.RenderModel();

		//--------------- Dado1---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-113.755f, 0.0f, -400.0f));

		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dado1_M.RenderModel();
		//--------------- Dado2---------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-113.755f, 0.0f, -400.0f));

		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dado2_M.RenderModel();


		// Renderizado del Doctor en movimiento
		model = glm::mat4(1.0);
		// Posición inicial + desplazamiento en Z (ajusta los valores iniciales según necesites)
		model = glm::translate(model, glm::vec3(-420.0f, 3.0f, -430.0f + distanciaRecorrida));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		// Rotación inicial + balanceo al caminar
		model = glm::rotate(model, (90.0f + sin(faseDoctor) * 3.0f) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cuerpo_Doctor.RenderModel();

		// Piernas del Doctor
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.5f, -1.0f, sin(faseDoctor) * amplitudPiernasDoctor));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiernaDerecha_Doc.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.5f, -1.0f, sin(faseDoctor + glm::pi<float>()) * amplitudPiernasDoctor));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiernaIzquierda_Doc.RenderModel();

		// Renderizado de Perry en movimiento (siguiendo al Doctor)
		model = glm::mat4(1.0);
		// Perry se mueve paralelo al Doctor pero con offset
		model = glm::translate(model, glm::vec3(-313.0f, 4.0f, -415.0f + distanciaRecorrida));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		// Rotación con balanceo
		model = glm::rotate(model, sin(fasePerry) * 5.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cuerpo_Perry.RenderModel();

		// Extremidades de Perry
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.3f, -0.8f, sin(fasePerry) * amplitudPiernasPerry));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiernaD_Perry.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.3f, -0.8f, sin(fasePerry + glm::pi<float>()) * amplitudPiernasPerry));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiernaI_Perry.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.4f, 1.2f, sin(fasePerry + glm::pi<float>()) * amplitudBrazosPerry));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BrazoI_Perry.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.4f, 1.2f, sin(fasePerry) * amplitudBrazosPerry));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BrazoD_Perry.RenderModel();

		

		//**************************************************************************AUTOMOVILES**************************************************************************

		//VOCHITO
		//Chasis
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(movVoch - 356.0f, 3.0f, -42.0f));
		model = glm::rotate(model, glm::radians(giraVoch), glm::vec3(0.0f, 1.0f, 0.0f));

		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		modelaux = model;

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		VCha.RenderModel();

		//Cofre
		model = modelaux;
		model = glm::translate(model, glm::vec3(-5.95f, 2.8f, -0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		VCof.RenderModel();

		//Llanta Delantera Izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(-11.5f, -4.3f, 7.3f));
		model = glm::rotate(model, rotllVoch * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		VLlDIz.RenderModel();

		//Llanta Delantera Derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-11.5f, -4.3f, -7.5f));
		model = glm::rotate(model, -rotllVoch * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		VLlDDe.RenderModel();

		//Llanta Trasera Izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(14.0f, -4.3f, 7.0f));
		model = glm::rotate(model, rotllVoch * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		VLlTIz.RenderModel();

		//Llanta Trasera Derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(14.0f, -4.3f, -7.0f));
		model = glm::rotate(model, -rotllVoch * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		VLlTDe.RenderModel();

		//AUTOBUS
		//Chasis
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(movBus - 139.0f, 4.0f, 16.0f));
		model = glm::rotate(model, glm::radians(giraBus), glm::vec3(0.0f, 1.0f, 0.0f));

		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		modelaux = model;

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ACha.RenderModel();

		//Llanta Delantera Izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.43f, -0.55f, 0.9f));
		model = glm::rotate(model, rotllBus * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ALlDIz.RenderModel();

		//Llanta Delantera Derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.43f, -0.55f, -0.8f));
		model = glm::rotate(model, rotllBus * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ALlDDe.RenderModel();

		//Llanta Trasera Izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(2.43f, -0.55f, 0.9f));
		model = glm::rotate(model, rotllBus * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ALlTIz.RenderModel();

		//Llanta Trasera Derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(2.43f, -0.55f, -0.8f));
		model = glm::rotate(model, rotllBus * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ALlTDe.RenderModel();

		//MOTO
		//Chasis
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(movMoto + 47.0f, -1.0f, -40.0f));
		model = glm::rotate(model, glm::radians(giraMoto - 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MCha.RenderModel(); //variable con el modelo del cuerpo de la moto
		modelaux = model;

		//Llanta Delantera
		model = modelaux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.8f, -2.4f)); //mueve la llanta hacia abajo
		model = glm::rotate(model, -rotllMoto * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MLl.RenderModel(); //variable con el modelo de una sola llanta

		//Llanta trasera
		model = modelaux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.8f, 2.4f)); //mueve la llanta hacia abajo
		model = glm::rotate(model, -rotllMoto * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MLl.RenderModel();

		//*********************************************************************FAUNA**************************************************************************

		//Pollos
		//Conjunto 1
		for (int i = 0; i < numAni; ++i) {

			for (int j = 0; j < numAni; ++j) {
				model = glm::mat4(1.0);
				//Ubicacion Oveja inicial
				glm::vec3 polloPos = glm::vec3(110.0f, 0.2f, 138.0f);

				//Ubicacion de Ovejas izquierda
				polloPos.x = polloPos.x + i * distanciaEntrePollos;
				polloPos.z = polloPos.z + j * distanciaEntrePollos;

				model = glm::translate(model, polloPos);
				model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
				model = glm::rotate(model, (anguloEntreAni * j) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::rotate(model, (anguloEntreAni * i) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Pollo.RenderModel();
			}
		}
		//Conjunto 2
		for (int i = 0; i < numAni; ++i) {

			for (int j = 0; j < numAni; ++j) {
				model = glm::mat4(1.0);
				//Ubicacion Pollo inicial
				glm::vec3 polloPos = glm::vec3(283.0f, 0.2f, 344.0f);

				//Ubicacion de Pollo izquierda
				polloPos.x = polloPos.x + i * distanciaEntrePollos;
				polloPos.z = polloPos.z + j * distanciaEntrePollos;

				model = glm::translate(model, polloPos);
				model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
				model = glm::rotate(model, (anguloEntreAni * j) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::rotate(model, (anguloEntreAni * i) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Pollo.RenderModel();
			}
		}

		//Ovejas
		//Conjunto 1
		for (int i = 0; i < numAni; ++i) {

			for (int j = 0; j < numAni; ++j) {
				model = glm::mat4(1.0);
				//Ubicacion Oveja inicial
				glm::vec3 ovejaPos = glm::vec3(-454.0f, 0.37f, 95.0f);

				//Ubicacion de Ovejas izquierda
				ovejaPos.x = ovejaPos.x + i * distanciaEntreOvejas;
				ovejaPos.z = ovejaPos.z + j * distanciaEntreOvejas;

				model = glm::translate(model, ovejaPos);
				model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
				model = glm::rotate(model, (anguloEntreAni * j) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::rotate(model, (anguloEntreAni * i) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Oveja.RenderModel();
			}
		}
		//Conjunto 2
		for (int i = 0; i < numAni; ++i) {

			for (int j = 0; j < numAni; ++j) {
				model = glm::mat4(1.0);
				//Ubicacion Oveja inicial
				glm::vec3 ovejaPos = glm::vec3(143.0f, 0.37f, -138.0f);

				//Ubicacion de Ovejas izquierda
				ovejaPos.x = ovejaPos.x + i * distanciaEntreOvejas;
				ovejaPos.z = ovejaPos.z + j * distanciaEntreOvejas;

				model = glm::translate(model, ovejaPos);
				model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
				model = glm::rotate(model, (anguloEntreAni * j) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::rotate(model, (anguloEntreAni * i) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Oveja.RenderModel();
			}
		}

		//Crabmeat
		//Conjunto 1
		for (int i = 0; i < numCrab; ++i) {

			for (int j = 0; j < numCrab; ++j) {
				//crabs 1
				model = glm::mat4(1.0);
				//Ubicacion de crab inicial
				glm::vec3 crabPos = glm::vec3(480.0f, -0.5f, -29.5f);

				//Ubicacion de siguientes crabs
				crabPos.x = crabPos.x + i * distanciaEntreCrab;
				crabPos.z = crabPos.z + j * distanciaEntreCrab;

				model = glm::translate(model, crabPos);
				model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
				model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Crabmeat.RenderModel();
			}
		}
		//Conjunto 2
		for (int i = 0; i < numCrab + 5; ++i) {

			for (int j = 0; j < numCrab; ++j) {
				//crabs 1
				model = glm::mat4(1.0);
				//Ubicacion de crab inicial
				glm::vec3 crabPos = glm::vec3(-260.0f, -0.5f, 328.0f);

				//Ubicacion de siguientes crabs
				crabPos.x = crabPos.x + i * distanciaEntreCrab;
				crabPos.z = crabPos.z + j * distanciaEntreCrab;

				model = glm::translate(model, crabPos);
				model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				Crabmeat.RenderModel();
			}
		}

		//**************************************************************************FLORA**************************************************************************

		//FrutasHabilidad
		for (int i = 0; i < numFrutas; ++i) {

			//Frutas Izquierda Camino
			model = glm::mat4(1.0);
			//Ubicacion de Fruta inicial
			glm::vec3 frutaPos = glm::vec3(365.0f, 0.2f, 245.0f);

			//Ubicacion de siguientes hongos
			frutaPos.z = frutaPos.z + i * distanciaEntreFrutas;

			model = glm::translate(model, frutaPos);
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			FruHa.RenderModel();

			if (i > 2)
			{
				//Frutas Izquierda Camino
				model = glm::mat4(1.0);
				//Ubicacion de Fruta inicial
				glm::vec3 frutaPos = glm::vec3(330.0f, 0.2f, 245.0f);

				//Ubicacion de siguientes hongos
				frutaPos.z = frutaPos.z + i * distanciaEntreFrutas;

				model = glm::translate(model, frutaPos);
				model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				FruHa.RenderModel();
			}
		}

		

		//Hongos
		for (int i = 0; i < numHongos; ++i) {

			//Hongos Antes Camino
			model = glm::mat4(1.0);
			//Ubicacion de Hongo inicial
			glm::vec3 hongoPosB = glm::vec3(360.0f, -1.0f, 253.1f);

			//Ubicacion de siguientes hongos
			hongoPosB.x = hongoPosB.x + i * distanciaEntreHongos;

			model = glm::translate(model, hongoPosB);
			model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			HongoM.RenderModel();

			if (i > 5)
			{
				//Hongos Cruzando Camino
				model = glm::mat4(1.0);
				//Ubicacion de Hongo inicial
				glm::vec3 hongoPos = glm::vec3(360.0f, -1.0f, 221.0f);

				//Ubicacion de siguientes hongos
				hongoPos.x = hongoPos.x + i * distanciaEntreHongos;

				model = glm::translate(model, hongoPos);
				model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				HongoM.RenderModel();
			}

		}

		//**************************************************************************OBJETOS**************************************************************************

		//Mineral (1)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-248.0f, 29.3f, 300.0f));
		model = glm::rotate(model, movAnimBas2 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mineral.RenderModel();

		

		//Cofre (3)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-84.0f, -1.0f, 164.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cofre.RenderModel();

		//Motobug 1 Piramide Luna (4)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(279.0f, -1.0f, -208.0f + movAnimBas));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Motobug.RenderModel();

		//Motobug 2 Pasando Calle
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-333.0f, -1.0f, -120.0f + movAnimBas));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Motobug.RenderModel();

		//Motobug 3 Calle
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(6.0f, -1.0f, 80.0f + movAnimBas));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Motobug.RenderModel();


		//Orbe Magico  (6)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(479.0f, 4.0f + movVert, -22.0f + 3.5 * sin(glm::radians(movZigZag))));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Orbe.RenderModel();


		//Joya  (8)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(244.0f, -0.0f, -114.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Joya.RenderModel();
		glDisable(GL_BLEND);



		//Oro (10)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-417.0f, -0.0f, 232.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Oro.RenderModel();

		

		
		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
