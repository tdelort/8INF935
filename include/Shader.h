#include <glad/glad.h>

// Will be changed with a class that reads .glsl files

//Vertex Shader
const char* vertexSource = R"glsl(
    #version 150

	in vec3 position;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 proj;

	void main()
	{
		gl_Position = proj * view * model * vec4(position, 1.0);
	}
)glsl";

//Geometry Shader
const char* geometrySource = R"glsl(
    #version 150

    layout(triangles) in;
    layout(triangle_strip, max_vertices=3) out;

    out vec3 normal;

    void main( void )
    {
        vec3 a = ( gl_in[1].gl_Position - gl_in[0].gl_Position ).xyz;
        vec3 b = ( gl_in[2].gl_Position - gl_in[0].gl_Position ).xyz;
        vec3 N = normalize( cross( b, a ) );

        for( int i=0; i<gl_in.length(); ++i )
        {
            gl_Position = gl_in[i].gl_Position;
            normal = N;
            EmitVertex();
        }

        EndPrimitive();
    }
)glsl";

//Fragment Shader
const char* fragmentSource = R"glsl(
    #version 150

    uniform vec3 albedo;
    in vec3 normal;

    vec3 lightPos = vec3(0.0, 0.0, 0.0);

	out vec4 outColor;

	void main()
	{
		outColor = vec4(normal, 1.0);
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

    // Creating Geometry shader
    GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &geometrySource, NULL);
    glCompileShader(geometryShader);

    glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &status);
    std::cout << "Geometry shader compile status : " << status << std::endl;

    // Creating Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    std::cout << "Fragment shader compile status : " << status << std::endl;
    
    // Creating shader program and linking it
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, geometryShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glUseProgram(program);
    return program;
}