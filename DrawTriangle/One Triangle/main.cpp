#include <iostream>

// GLEW 
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

using namespace std;

// Function prototypes
void key_callback(GLFWwindow* window , int key , int scancode , int action , int mode);

// Window dimensions
const GLuint WIDTH = 800,HEIGHT = 600;

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
	"layout(location = 0) in vec3 position;\n"
	"void main()\n"
	"{\n"
	"gl_Postion = vec4(position.x,position.y,position.z,1.0);\n"
	"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
    
// The MAIN function , from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE , GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE , GL_FALSE);
	
	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"LearnOpenGL",nullptr,nullptr);
	glfwMakeContextCurrent(window);
	
	// Set the required callback functions
	glfwSetKeyCallback(window , key_callback);
	
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL function pointers
	glewInit();
	
	// Define the viewport dimensions
	glViewport(0,0,WIDTH,HEIGHT);
	
	
	// Build and compile our shader program
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader , 1 , &vertexShaderSource , NULL);
	glCompileShader(vertexShader);
	// Check for compile time errors
	GLint success;
	GLchar infolog[512];
	glGetShaderiv(vertexShader , GL_COMPILE_STATUS , &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader , 512, NULL , infolog);
		cout<< "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<< infolog << endl;
	}
	
	// Fragment shader
	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader , 1 , &fragmentShaderSource , NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS,&success);
	if(!success)
	{
		glGetShaderInfoLog(fragmentShader , 512, NULL ,infolog);
		cout<<"ERROR::SHADER::FRAGMENT::LINKING_FAILED\n"<<infolog<<endl;
	}
	
	// Link shaders
	GLint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram , vertexShader);
	glAttachShader(shaderProgram , fragmentShader);
	glLinkProgram(shaderProgram);
	// Check for linking errors
	glGetProgramiv(shaderProgram,GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(shaderProgram , 512 , NULL , infolog);
		cout<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<infolog<<endl;
	}
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	// Set up vertex data (and buffer(s) and attribute pointers)
	GLfloat vertices[] = {
		-0.5f,-0.5f,0.0f, // Left
		0.5f,-0.5f,0.0f, // Right
		0.0f,0.5f,0.0f	// Top
	};
	GLuint VBO,VAO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	// Bind the vertex array object first , then bind and set vertex buffer(s) and attribute pointer(s)
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER , VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER , 0);
	glBindVertexArray(0); // Unbind VAO
	
	// Game Loop 
	while(!glfwWindowShouldClose(window))
	{
		// Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		
		// Render 
		// Clear the colorbuffer
		glClearColor(0.2f,0.3f,0.3f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Draw our first triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,3);
		glBindVertexArray(0);
		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// Deallocate all resources once they no use
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	// Terminate GLFW , clearing any resources allocated by GLFW 
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window , int key ,int scancode , int action , int mode)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window , GL_TRUE);
	}
}	
