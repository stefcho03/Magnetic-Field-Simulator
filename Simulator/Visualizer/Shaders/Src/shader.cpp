#include <shader.h>
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// Please excuse the overly descriptive comments

Shader::Shader (const char* vertexPath, const char* fragmentPath)
{
	std::stringstream vShaderStream, fShaderStream;
	std::string vertexCode;
	std::string fragmentCode;

	// Please check your spellig before any suicide attempts
	std::ifstream vShaderFile (vertexPath); // Open vertex file
	if (!vShaderFile.is_open ())
	{
		std::cerr << "ERROR: Could not open shader file: " << vertexPath << '\n';
		std::exit (EXIT_FAILURE);
	}

	std::ifstream fShaderFile (fragmentPath); // Open fragment file
	if (!fShaderFile.is_open ())
	{
		std::cerr << "ERROR: Could not open shader file: " << fragmentPath << '\n';
		std::exit (EXIT_FAILURE);
	}

	// Read files in stream
	vShaderStream << vShaderFile.rdbuf ();
	fShaderStream << fShaderFile.rdbuf ();
	// Stream -> string
	vertexCode = vShaderStream.str ();
	fragmentCode = fShaderStream.str ();
	// String -> pointer
	const char* vShaderCode = vertexCode.c_str ();
	const char* fShaderCode = fragmentCode.c_str ();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// vertex shader
	vertex = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vertex, 1, &vShaderCode, nullptr); // Attach source code to object. Object, number of strings, pointer to string
	glCompileShader (vertex);
	glGetShaderiv (vertex, GL_COMPILE_STATUS, &success); // Check if shader compilation is successful
	if (!success)
	{
		glGetShaderInfoLog (vertex, 512, nullptr, infoLog);
		std::cout << "Vertex shader compile error:\n" << infoLog << std::endl;
		std::exit (EXIT_FAILURE);
	}

	// fragment shader (Rinse and repeat)
	fragment = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fragment, 1, &fShaderCode, nullptr);
	glCompileShader (fragment);
	glGetShaderiv (fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog (fragment, 512, nullptr, infoLog);
		std::cout << "Fragment shader compile error:\n" << infoLog << std::endl;
		std::exit (EXIT_FAILURE);
	}

	// shader program
	ID = glCreateProgram ();
	glAttachShader (ID, vertex);
	glAttachShader (ID, fragment);
	glLinkProgram (ID);
	glGetProgramiv (ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog (ID, 512, nullptr, infoLog);
		std::cout << "Shader program link error:\n" << infoLog << std::endl;
		std::exit (EXIT_FAILURE);
	}

	glDeleteShader (vertex);
	glDeleteShader (fragment);
}

void Shader::use () const
{
	glUseProgram (ID);
}
