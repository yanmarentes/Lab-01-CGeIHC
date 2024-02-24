#include <stdio.h>
#include <glew.h>//libreria de apoyo de opengl
#include <glfw3.h>
#include <Windows.h>
//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600; //se declaran estas variables 

float r, f;
int i;
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
	//Nos sirven para indicar que se usa el api de opengl y la versión
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	//Sirven para indicar que se usaran el coore de open gl que no utiliza la versión legazy, código de la versión moderna
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//De la v4.3 a 4.6 indica que si se encuentra una mejora, se utilice

	//CREAR VENTANA
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Practica 1_EjercicioA", NULL, NULL);//declara el contenedor de la ventana que se ve
	//GLFWwindow* Window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 1_EjercicioB", NULL, NULL);


	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
		//En caso de que no se abra
	}
	/*
	if (!Window){
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
		//En caso de que no se abra
	}
	*/
	//Obtener tamaño de Buffer
	//Sirven para almacenar el valor del espacio de memoria asignado para pixeles de alto y ancho
	//La otra línea sirve para saber el espacio en memoria en caso de ridemnsionar la ventana

	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//glfwGetFramebufferSize(Window, &BufferWidth, &BufferHeight);

	//asignar el contexto
	//La ventana activa sea la ventana que crea, para que los periféricos sean recibidos por esta
	glfwMakeContextCurrent(mainWindow);
	//glfwMakeContextCurrent(Window);

	//permitir nuevas extensiones
	//Librerías que son extensiones al core profile
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}
	/*
	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(Window);
		glfwTerminate();
		return 1;
	}
	*/
	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport

	//Es la primer línea de opengl, es una ventana que se ve dentro del plano y se acomode en el origen, ajustarlo a un tam de pixeles definido por el tam de memoria ya asignado

	glViewport(0, 0, BufferWidth, BufferHeight);
	
	printf("Version de Opengl: %s \n",glGetString(GL_VERSION));
	printf("Marca: %s \n", glGetString(GL_VENDOR));
	printf("Renderer: %s \n", glGetString(GL_RENDERER));
	printf("Shaders: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	//Loop mientras no se cierra la ventana
	//Dentro del ciclo indica cuando la venta a cerrar, mientras no se cierre pueda entrar en cualquier sitio
	while (!glfwWindowShouldClose(mainWindow)/* && !glfwWindowShouldClose(Window)*/)
	{

		
		for (r = 0.0f; r <= 1.0f; r = r + 0.5f)
		{
			for (f = 0.0f; f <= 1.0f; f = f + 0.5f)
			{
				if (r <= 1.0f)
				{
					glClearColor(r, f, 0.5f, 1.0f);
					glClear(GL_COLOR_BUFFER_BIT);
					glfwSwapBuffers(mainWindow);
					Sleep(4000);

				}
			}

		}

		//glfwSwapBuffers(Window);

		//Recibir eventos del usuario
		glfwPollEvents();//Cuando se recibe un evento, se declara, para recibir info proveniente de los periféricos

		//Limpiar la ventana
		//El fondo de la ventana se establece a ese color siguiendo el rgb, el valor de alfa siempre sera en 1 cuando sea color, si es diferente es para texturizado e iluminación
		//glClearColor(0.0f,1.0f,0.0f,1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);//Limpia el buffer de color de profundidad

		//Es la última linea, al manejar un buffer doble que procesa y muestra info, lo hace cada ciclo de reloj (procesador)


	}
	 glfwDestroyWindow(mainWindow); //La venta con sus datos se eliminan permamentemente
	 //glfwDestroyWindow(Window);
	 glfwTerminate();

	return 0;
}
