/*
Práctica 5
Ramirez Moreno Diego Gerardo
319296738
09 de Marzo del 2025
*/

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Shaders
#include "Shader.h"
void Inputs(GLFWwindow* window);
const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard (Controlar la vista)
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rot = 0.0f;

// For model, genera la articulacion
float hombro = 0.0f;
float codo = 0.0f;
float muneca = 0.0f;
float dedo1 = 0.0f;
float dedo1b = 0.0f;
float dedo1c = 0.0f;
float dedo2 = 0.0f;
float dedo2b = 0.0f;
float dedo2c = 0.0f;
float dedo3 = 0.0f;
float dedo3b = 0.0f;
float dedo3c = 0.0f;
float dedo4 = 0.0f;
float dedo4b = 0.0f;
float dedo4c = 0.0f;
float pulgar = 0.0f;
float pulgarb = 0.0f;
float pulgarc = 0.0f;


int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado jerarquico | Diego Ramirez | 319296738", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);

	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	// use with Orthographic Projection

	// use with Perspective Projection
	// Usamos tres parametros (posicion)
	float vertices[] = {
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f,  0.5f, 0.5f,
		0.5f,  0.5f, 0.5f,
		-0.5f,  0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,

		-0.5f, -0.5f,-0.5f,
		 0.5f, -0.5f,-0.5f,
		 0.5f,  0.5f,-0.5f,
		 0.5f,  0.5f,-0.5f,
		-0.5f,  0.5f,-0.5f,
		-0.5f, -0.5f,-0.5f,

		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  -0.5f, 0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	glm::mat4 projection = glm::mat4(1);

	// Aqui generamos nuestra proyeccion en perspectiva
	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Aqui dibujamos
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);			// Matriz que controla el modelo
		glm::mat4 view = glm::mat4(1);			// Matriz que controla la vista
		glm::mat4 modelTemp = glm::mat4(1.0f);	// Controla la informacion de la pos de cada uno
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp3 = glm::mat4(1.0f);


		//View set up 
		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		// Con esto controlamos el pivote
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint uniformColor = ourShader.uniformColor;

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));


		glBindVertexArray(VAO);

		//Model 
		// ------------------------ Hombro --------------------------------
		model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0, 1.0f));	// Aplicamos rotacion en la componente Z
		modelTemp = model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));			// Genera sensacion de movimiento en articulacion del hombro
		// y recorremos la mitad de la caja 1.5
		model = glm::scale(model, glm::vec3(3.0f, 2.0f, 2.6f));							// Solo es el tamano de la caja
		color = glm::vec3(0.8f, 0.6f, 0.9f);											// Color cambiado a lila pastel
		// Mandamos a dibujar
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//A

		// ------------------------ Antebrazo --------------------------------
		model = glm::translate(modelTemp, glm::vec3(1.5f, 0.0f, 0.0f));					// 1.5 unidades del tamano de la caja el final e inicio de la otra caja
		model = glm::rotate(model, glm::radians(codo), glm::vec3(0.0f, 1.0f, 0.0f));
		modelTemp = model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));			// Para llegar al centro de la sig figura
		model = glm::scale(model, glm::vec3(3.0f, 2.0f, 2.6f));							// Para poder escalar	
		color = glm::vec3(0.9f, 0.8f, 0.5f); 											// Color cambiado a amarillo pastel
		// Dibujamos
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//B

		// ------------------------ Palma --------------------------------
		model = glm::translate(modelTemp, glm::vec3(1.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(muneca), glm::vec3(1.0f, 0.0f, 0.0f));
		modelTemp3 = modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));	// Para poder generar los dedos mas rapido desde la palma
		// es un tipo checkpoint
		model = glm::scale(model, glm::vec3(0.5f, 2.0f, 2.6f));
		color = glm::vec3(0.6f, 0.9f, 0.7f); 											// Color cambiado a verde menta pastel
		// Dibujamos
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//C

		// ------------------------ Dedo 1 pt1 --------------------------------
		model = glm::translate(modelTemp, glm::vec3(0.2f, 0.7f, 0.95f));
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 2.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.2f, 0.5f, 0.45f));
		color = glm::vec3(1.0f, 1.0f, 0.7f);
		// Dibujamos
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); //F

		// ------------------------ Dedo 1 pt2 --------------------------------
		model = glm::translate(modelTemp, glm::vec3(0.7f, 0.0f, 0.0f)); // Se traslada desde la base del dedo 1
		model = glm::rotate(model, glm::radians(dedo1b), glm::vec3(0.0f, 0.0f, 1.0f)); // Se rota alrededor del eje Z
		modelTemp = model = glm::translate(model, glm::vec3(0.7f, 0.0f, 0.0f)); // Se ajusta la posición después de la rotación
		model = glm::scale(model, glm::vec3(1.6f, 0.5f, 0.45f)); // Se escala (Tamaño corregido)
		color = glm::vec3(0.8f, 0.7f, 1.0f);
		// Dibujamos
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); //G

		// ------------------------ Dedo 1 pt3 (Nueva falange) --------------------------------
		model = glm::translate(modelTemp, glm::vec3(0.6f, 0.0f, 0.0f)); // Se traslada desde la base de la segunda falange
		model = glm::rotate(model, glm::radians(dedo1c), glm::vec3(0.0f, 0.0f, 1.0f)); // Se rota alrededor del eje Z
		model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); // Se ajusta la posición después de la rotación
		model = glm::scale(model, glm::vec3(1.2f, 0.4f, 0.35f)); // Se escala (Tamaño más pequeño)
		color = glm::vec3(0.7f, 0.6f, 0.9f);
		// Dibujamos
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); //H

		// ------------------------ Dedo 2 pt1 --------------------------------
		model = glm::translate(modelTemp3, glm::vec3(0.1f, 0.7f, 0.7f)); // Nueva posición
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 2.0f));
		modelTemp4 = modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f)); // Punto base para falanges
		model = glm::scale(model, glm::vec3(1.1f, 0.5f, 0.45f));
		color = glm::vec3(1.0f, 0.8f, 0.6f);
		// Dibujamos
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // I

		// ------------------------ Dedo 2 pt2 --------------------------------
		model = glm::translate(modelTemp, glm::vec3(0.6f, 0.0f, 0.0f)); // Desde la base del dedo 2
		model = glm::rotate(model, glm::radians(dedo2b), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.6f, 0.0f, 0.0f)); // Ajuste tras rotación
		model = glm::scale(model, glm::vec3(1.5f, 0.5f, 0.45f));
		color = glm::vec3(0.9f, 0.7f, 0.6f);
		// Dibujamos
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // J

		// ------------------------ Dedo 2 pt3 --------------------------------
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f)); // Desde la base de la segunda falange
		model = glm::rotate(model, glm::radians(dedo2c), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.2f, 0.4f, 0.35f));
		color = glm::vec3(0.8f, 0.6f, 0.7f);
		// Dibujamos
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // K

		// ------------------------ Dedo 3 pt1 --------------------------------
		model = glm::translate(modelTemp4, glm::vec3(0.0f, 0.7f, 0.4f)); // Nueva posición
		model = glm::rotate(model, glm::radians(dedo3), glm::vec3(0.0f, 0.0f, 2.0f));
		modelTemp5 = modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f)); // Punto base para falanges
		model = glm::scale(model, glm::vec3(1.0f, 0.5f, 0.45f));
		color = glm::vec3(1.0f, 0.9f, 0.5f);
		// Dibujamos
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // L

		// ------------------------ Dedo 3 pt2 --------------------------------
		model = glm::translate(modelTemp, glm::vec3(0.55f, 0.0f, 0.0f)); // Desde la base del dedo 3
		model = glm::rotate(model, glm::radians(dedo3b), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.55f, 0.0f, 0.0f)); // Ajuste tras rotación
		model = glm::scale(model, glm::vec3(1.4f, 0.5f, 0.45f));
		color = glm::vec3(0.9f, 0.6f, 0.6f);
		// Dibujamos
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // M

		// ------------------------ Dedo 3 pt3 --------------------------------
		model = glm::translate(modelTemp, glm::vec3(0.45f, 0.0f, 0.0f)); // Desde la base de la segunda falange
		model = glm::rotate(model, glm::radians(dedo3c), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.35f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.1f, 0.4f, 0.35f));
		color = glm::vec3(0.8f, 0.5f, 0.7f);
		// Dibujamos
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // N

		// ------------------------ Dedo 4 pt1 --------------------------------
		model = glm::translate(modelTemp6, glm::vec3(-0.2f, 0.7f, 0.0f)); // Nueva posición en la palma
		model = glm::rotate(model, glm::radians(dedo4), glm::vec3(0.0f, 0.0f, 2.0f));
		modelTemp7 = modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f)); // Punto base para falanges
		model = glm::scale(model, glm::vec3(0.9f, 0.5f, 0.45f));
		color = glm::vec3(1.0f, 0.8f, 0.4f);
		// Dibujamos
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // P

		// ------------------------ Dedo 4 pt2 --------------------------------
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f)); // Desde la base del dedo 4
		model = glm::rotate(model, glm::radians(dedo4b), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); // Ajuste tras rotación
		model = glm::scale(model, glm::vec3(1.3f, 0.5f, 0.45f));
		color = glm::vec3(0.9f, 0.7f, 0.5f);
		// Dibujamos
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // Q

		// ------------------------ Dedo 4 pt3 --------------------------------
		model = glm::translate(modelTemp, glm::vec3(0.4f, 0.0f, 0.0f)); // Desde la base de la segunda falange
		model = glm::rotate(model, glm::radians(dedo4c), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.3f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.4f, 0.35f));
		color = glm::vec3(0.8f, 0.6f, 0.6f);
		// Dibujamos
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // R

		// ------------------------ Pulgar pt1 --------------------------------
		model = glm::translate(modelTemp8, glm::vec3(-0.3f, 0.5f, 0.3f)); // Posición más baja y lateral
		model = glm::rotate(model, glm::radians(pulgar), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotación en el eje Z
		modelTemp9 = modelTemp = model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f)); // Punto base para la siguiente falange
		model = glm::scale(model, glm::vec3(1.2f, 0.6f, 0.5f)); // Más grueso y más corto
		color = glm::vec3(1.0f, 0.85f, 0.6f);
		// Dibujamos
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // S

		// ------------------------ Pulgar pt2 --------------------------------
		model = glm::translate(modelTemp, glm::vec3(0.4f, 0.0f, 0.0f)); // Desde la base del pulgar
		model = glm::rotate(model, glm::radians(pulgarb), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.3f, 0.0f, 0.0f)); // Ajuste tras la rotación
		model = glm::scale(model, glm::vec3(1.0f, 0.55f, 0.45f)); // Más corto pero manteniendo grosor
		color = glm::vec3(0.95f, 0.75f, 0.55f);
		// Dibujamos
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // T


		glBindVertexArray(0);


		// Swap the screen buffers
		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
}

// Para las entradas del teclado
// Para las entradas del teclado
void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.18f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.18f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		movY += 0.18f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		movY -= 0.18f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.18f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.18f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot += 0.68f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot -= 0.68f;
	// ------------------------ Hombro --------------------------------
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		if (90.0f > hombro)
			hombro += 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && -80.0f < hombro)
		hombro -= 1.0f;
	// ------------------------ Antebrazo --------------------------------
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		if (0.0f > codo)
			codo += 0.28f;
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && -100.0f < codo)
		codo -= 0.28f;
	// ------------------------ Muneca --------------------------------
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
		if (20.0f > muneca)
			muneca += 0.28f;
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && -75.0f < muneca)
		muneca -= 0.28f;
	// ------------------------ Dedo 1 --------------------------------
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		if (20.0f > dedo1)
			dedo1 += 0.28f;
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && -10.0f < dedo1)
		dedo1 -= 0.28f;
	// ------------------------ Dedo 1b --------------------------------
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		if (0.0f > dedo1b)
			dedo1b += 0.28f;
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && -30.0f < dedo1b)
		dedo1b -= 0.28f;
	// ------------------------ Dedo 1c --------------------------------
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		if (10.0f > dedo1c)
			dedo1c += 0.28f;
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS && -10.0f < dedo1c)
		dedo1c -= 0.28f;
	// ------------------------ Dedo 2 --------------------------------
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		if (20.0f > dedo1)
			dedo1 += 0.28f;
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && -10.0f < dedo1)
		dedo1 -= 0.28f;
	// ------------------------ Dedo 2b --------------------------------
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		if (0.0f > dedo1b)
			dedo1b += 0.28f;
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && -30.0f < dedo1b)
		dedo1b -= 0.28f;
	// ------------------------ Dedo 2c --------------------------------
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		if (10.0f > dedo1c)
			dedo1c += 0.28f;
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS && -10.0f < dedo1c)
		dedo1c -= 0.28f;
	// ------------------------ Dedo 3 --------------------------------
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		if (20.0f > dedo1)
			dedo1 += 0.28f;
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && -10.0f < dedo1)
		dedo1 -= 0.28f;
	// ------------------------ Dedo 3b --------------------------------
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		if (0.0f > dedo1b)
			dedo1b += 0.28f;
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && -30.0f < dedo1b)
		dedo1b -= 0.28f;
	// ------------------------ Dedo 3c --------------------------------
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		if (10.0f > dedo1c)
			dedo1c += 0.28f;
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS && -10.0f < dedo1c)
		dedo1c -= 0.28f;
	// ------------------------ Dedo 4 --------------------------------
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		if (20.0f > dedo1)
			dedo1 += 0.28f;
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && -10.0f < dedo1)
		dedo1 -= 0.28f;
	// ------------------------ Dedo 4b --------------------------------
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		if (0.0f > dedo1b)
			dedo1b += 0.28f;
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && -30.0f < dedo1b)
		dedo1b -= 0.28f;
	// ------------------------ Dedo 4c --------------------------------
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		if (10.0f > dedo1c)
			dedo1c += 0.28f;
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS && -10.0f < dedo1c)
		dedo1c -= 0.28f;
	// ------------------------ Pulgar --------------------------------
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		if (10.0f > pulgar)
			pulgar += 0.28f;
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && -30.0f < pulgar)
		pulgar -= 0.28f;
	// ------------------------ Pulgarb --------------------------------
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		if (30.0f > pulgarb)
			pulgarb += 0.28f;
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && 0.0f < pulgarb)
		pulgarb -= 0.28f;

}
