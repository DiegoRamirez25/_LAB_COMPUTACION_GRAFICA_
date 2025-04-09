/*
Practica 3
Ramírez Moreno Diego Gerardo
319296738
14 de Febrero del 2025
*/

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D | Diego Gerardo Ramirez Moreno | Grupo 6", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		// TENAZA IZQUIERDA (Rojo claro)
		-0.21f, 0.48f, 0.0f,    1.0f, 0.5f, 0.5f, // C 0
		-0.47f, 0.08f, 0.0f,    1.0f, 0.5f, 0.5f, // F 1
		-0.15f, 0.09f, 0.0f,    1.0f, 0.5f, 0.5f, // E 2

		// TENAZA DERECHA (Rojo claro)
		0.21f, 0.49f, 0.0f,     1.5f, 0.5f, 0.5f, // D 3
		0.15f, 0.10f, 0.0f,     1.5f, 0.5f, 0.5f, // H 4
		0.47f, 0.08f, 0.0f,     1.5f, 0.5f, 0.5f, // G 5

		// CUERPO IZQ (Vino)
		-0.47f, 0.08f, 0.0f,    0.5f, 0.0f, 0.0f, // F 6
		-0.15f, 0.09f, 0.0f,    0.5f, 0.0f, 0.0f, // E 7
		-0.20f, -0.47f, 0.0f,   0.5f, 0.0f, 0.0f, // N 8

		// CUERPO DER (Vino)
		0.15f, 0.10f, 0.0f,     0.5f, 0.0f, 0.0f, // H 9
		0.47f, 0.08f, 0.0f,     0.5f, 0.0f, 0.0f, // G 10
		0.21f, -0.47f, 0.0f,    0.5f, 0.0f, 0.0f, // O 11

		// CUERPO EN MEDIO (PARTE 1) (Vino)
		-0.15f, 0.09f, 0.0f,    0.5f, 0.0f, 0.0f, // E 12
		0.15f, 0.10f, 0.0f,     0.5f, 0.0f, 0.0f, // H 13
		-0.20f, -0.47f, 0.0f,   0.5f, 0.0f, 0.0f, // N 14
		0.21f, -0.47f, 0.0f,    0.5f, 0.0f, 0.0f, // O 15

		// PIERNA IZQ (PARTE 1) (Rojo claro)
		-0.58f, -0.29f, 0.0f,   1.0f, 0.5f, 0.5f, // J 16
		-0.36f, -0.14f, 0.0f,   1.0f, 0.5f, 0.5f, // I 17
		-0.41f, -0.47f, 0.0f,   1.0f, 0.5f, 0.5f, // M 18

		// PIERNA IZQ (PARTE 2) (Rojo claro)
		-0.36f, -0.14f, 0.0f,   1.0f, 0.5f, 0.5f, // I 19
		-0.41f, -0.47f, 0.0f,   1.0f, 0.5f, 0.5f, // M 20
		-0.20f, -0.47f, 0.0f,   1.0f, 0.5f, 0.5f, // N 21

		// PATA IZQ (Rojo claro)
		-0.58f, -0.29f, 0.0f,   1.0f, 0.5f, 0.5f, // J 22
		-0.31f, -0.47f, 0.0f,   1.0f, 0.5f, 0.5f, // L 23
		-0.47f, -0.76f, 0.0f,   1.0f, 0.5f, 0.5f, // K 24

		// PIERNA DER (PARTE 1) (Rojo claro)
		0.36f, -0.14f, 0.0f,    1.0f, 0.5f, 0.5f, // P 25
		0.21f, -0.47f, 0.0f,    1.0f, 0.5f, 0.5f, // O 26
		0.41f, -0.47f, 0.0f,    1.0f, 0.5f, 0.5f, // R 27

		// PIERNA DER (PARTE 2) (Rojo claro)
		0.36f, -0.14f, 0.0f,    1.0f, 0.5f, 0.5f, // P 28
		0.41f, -0.47f, 0.0f,    1.0f, 0.5f, 0.5f, // R 29
		0.59f, -0.29f, 0.0f,    1.0f, 0.5f, 0.5f, // Q 30

		// PATA DER (Rojo claro)
		0.34f, -0.47f, 0.0f,    1.0f, 0.5f, 0.5f, // T 31
		0.59f, -0.29f, 0.0f,    1.0f, 0.5f, 0.5f, // Q 32
		0.50f, -0.75f, 0.0f,    1.0f, 0.5f, 0.5f, // S 33

		//CUERPO EN MEDIO (PARTE 2) (Vino)

		-0.20f, -0.47f, 0.0f,   0.5f, 0.0f, 0.0f, // N 34
		0.21f, -0.47f, 0.0f,    0.5f, 0.0f, 0.0f, // O 35
		0.15f, 0.10f, 0.0f,     0.5f, 0.0f, 0.0f, // H 36

	};
	unsigned int indices[] = {  // note that we start from 0!
		//TENAZA IZQUIERDA

		0,1,2,

		//TENAZA DERECHA

		3,4,5,

		//CUERPO IZQ

		6,7,8,

		//CUERPO EN MEDIO (PARTE 1)

		12,13,14,

		//CUERPO EN MEDIO (PARTE 2)

		34,35,36,

		//CUERPO DER 

		9,10,11,
	
		//PIERNA IZQ (PARTE 1)

		16,17,18,

		//PIERNA IZQ (PARTE 2)

		19,20,21,

		//PATA IZQ

		22,23,24,

		//PIERNA DER (PARTE 1)

		25,26,27,

		//PIERNA DER (PARTE 2)

		28,29,30,

		//PATA DER 

		31,32,33,

		//CUERPO EN MEDIO (PARTE 2) (Vino)

		34,35,36		
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);


        //glPointSize(10);
        //glDrawArrays(GL_POINTS,0,4);
        
        //glDrawArrays(GL_LINES,0,4);
        //glDrawArrays(GL_LINE_LOOP,0,4);
        
        //glDrawArrays(GL_TRIANGLES,0,3);
        //glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT,0);


		// Actualizar el buffer de vértices
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Renderizar
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 42, GL_UNSIGNED_INT, 0);
		

		// Swap the screen buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}
