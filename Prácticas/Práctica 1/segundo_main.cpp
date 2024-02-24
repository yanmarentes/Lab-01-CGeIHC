#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>
//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;
GLuint VAO, VBO, shader; //Variables int sin signo de opengl

//Vertex Shader
//recibir color, salida Vcolor
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";
//Fragment Shader para procesar color y texturas
//recibir Vcolor y dar de salida color
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(0.0f,1.0f,1.0f,1.0f);	 			\n\
}";

//Código embebido, código de un V. shader para iindicar los datos de una posición que procesados, indica la posición en el plano xyz
//Se utiliza con cualquier HW y SO,
//Se tiene la versión del shader
//Recibe datos que son de posición, que en el main, lo convierte en las coordenadas, estos son flotantes a xyz
//En main, el vec4 se agrega un punto equivalente a una matriz 4x1, porque open majeja otras matrices que premultiplican que son 4x4

void CrearTriangulo()
{
	//Se declaran 9 datos flotantes separados en bloques de tres, cada renglon se lee esos tres datos y se transforman en un shader vértice xyz

	GLfloat vertices[] = {
		/*
		-1.0f, -1.0f,0.0f, //Vértice Izquierdo
		1.0f,-1.0f, 0.0f, //Vértice derecho
		0.0f,1.0f,0.0f, //Vértice superior
		*/

		//I
		-1.0f, 0.8f,0.0f,
		-0.5f,0.8f, 0.0f,
		-1.0f,1.0f,0.0f,
		-1.0f,1.0f,0.0f,
		-0.5f,0.8f, 0.0f,
		-0.5f,1.0f,0.0f,


		-0.7f,0.25f,0.0f,
		-0.85f,0.25f, 0.0f,
		-0.85f,0.8f,0.0f,
		-0.85f,0.8f,0.0f,
		-0.7f,0.8f, 0.0f,
		-0.7f,0.25f,0.0f,

		-1.0f, 0.05f,0.0f,
		-0.5f,0.05f, 0.0f,
		-1.0f,0.25f,0.0f,
		-1.0f, 0.25f,0.0f,
		-0.5f,0.25f, 0.0f,
		-0.5f,0.05f,0.0f,

		//P
		0.5f,0.85f,0.0f,
		1.0f,0.85f, 0.0f,
		1.0f,1.0f,0.0f,

		0.5f,1.0f,0.0f,
		1.0f,1.0f, 0.0f,
		0.5f,0.85f,0.0f,

		0.35f,0.05f,0.0f,
		0.5f,0.05f, 0.0f,
		0.5f,1.0f,0.0f,
		0.35f,1.0f,0.0f,
		0.5f,1.0f, 0.0f,
		0.35f,0.05f,0.0f,

		0.5f,0.5f,0.0f,
		1.0f,0.5f, 0.0f,
		1.0f,0.35f,0.0f,
		0.5f,0.35f,0.0f,
		1.0f,0.35f, 0.0f,
		0.5f,0.5f,0.0f,

		0.85f,0.5f,0.0f,
		1.0f,0.5f, 0.0f,
		1.0f,1.0f,0.0f,
		0.85f,1.0f,0.0f,
		1.0f,1.0f, 0.0f,
		0.85f,0.5f,0.0f,

		//M
		-1.0f,-0.05f,0.0f,
		-0.9f,-0.05f,0.0f,
		-1.0f,-1.0f,0.0f,
		-1.0f,-1.0f,0.0f,
		-0.9f,-1.0f,0.0f,
		-0.9f,-0.05f,0.0f,

		-0.9f,-0.35f,0.0f,
		-0.8f,-0.5f,0.0f,
		-0.9f,-0.05f,0.0f,

		-0.8f,-0.5f,0.0f,
		-0.7f,-0.35f,0.0f,
		-0.7f,-0.05f,0.0f,

		-0.7f,-0.05f,0.0f,
		-0.6f,-0.05f,0.0f,
		-0.7f,-1.0f,0.0f,
		-0.7f,-1.0f,0.0f,
		-0.6f,-1.0f,0.0f,
		-0.6f,-0.05f,0.0f,
		
		//D
		0.45f,-0.05f,0.0f,
		0.35f,-0.05f,0.0f,
		0.45f,-1.0f,0.0f,

		0.45f,-1.0f,0.0f,
		0.35f,-1.0f,0.0f,
		0.35f,-0.05f,0.0f,

		0.45f,-0.25f,0.0f,
		0.75f,-0.35f,0.0f,
		0.45f,-0.05f,0.0f,

		0.45f,-1.0f,0.0f,
		0.75f,-0.65f,0.0f,
		0.45f,-0.8f,0.0f,

		0.70f,-0.7f,0.0f,
		0.75f,-0.65f,0.0f,
		0.75f,-0.35f,0.0f,

	};
	//Se convierten los datos en el vértice
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Se idnica el tam ya asigando
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores
		//Se indican cuantos valores se tiene por renglón, en este caso 3 por renglón, el útlimo es para hacer un salto y leer el siguiente renglón
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
		glEnableVertexAttribArray(0);
		//agregar valores a vèrtices y luego declarar un nuevo vertexAttribPointer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		//

}
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) //Función para agregar los shaders a la tarjeta gráfica
//the Program recibe los datos de theShader


{
	GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
	const GLchar* theCode[1];
	theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);//longitud del texto
	glShaderSource(theShader,1, theCode, codeLength);//Se le asigna al shader el código
	glCompileShader(theShader);//Se comila el shader
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	//verificaciones y prevención de errores
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n",shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el código a la tarjeta gráfica
}

void CompileShaders() {
	shader= glCreateProgram(); //se crea un programa
	if (!shader)
	{
		printf("Error creando el shader");
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);//Agregar vertex shader
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);//Agregar fragment shader
	//Para terminar de linkear el programa y ver que no tengamos errores
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);//se linkean los shaders a la tarjeta gráfica
	//Se recibe cierto texto que se envia al gpu y se valida o no para compilar  
	 //verificaciones y prevención de errores
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al linkear es: %s \n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al validar es: %s \n", eLog);
		return;
	}



}
int main()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Primer ventana", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);

 //Crear tríangulo
	CrearTriangulo();
	CompileShaders();
	
	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Recibir eventos del usuario 
		glfwPollEvents();

		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);
		//Indica que ya dibujará y liberar
		//Se ve un triangulo de color r sobre una ventana de color n
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,78);
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);

	}


	return 0;
}