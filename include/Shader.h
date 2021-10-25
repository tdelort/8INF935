#include <glad/glad.h>

// Will be changed with a class that reads .glsl files

//Vertex Shader
const char* vertexSource = R"glsl(
    #version 130

	in vec3 position;
    in vec3 color;

    out vec3 Color;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 proj;
    uniform vec3 albedo;

	void main()
	{
        //Color = color;
        Color = albedo;
		gl_Position = proj * view * model * vec4(position, 1.0);
	}
)glsl";

//Fragment Shader
const char* fragmentSource = R"glsl(
    #version 130

    in vec3 Color;

	out vec4 outColor;

	void main()
	{
		outColor = vec4(Color, 1.0);
	}
)glsl";

GLuint createProgram()
{
    // Creating Vertex shader
    GLint status;
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    std::cout << "Vertex shader compile status : " << status << std::endl;

    // Creating Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    std::cout << "Fragment shader compile status : " << status << std::endl;
    
    // Creating shader program and linking it
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glUseProgram(program);
    return program;
}