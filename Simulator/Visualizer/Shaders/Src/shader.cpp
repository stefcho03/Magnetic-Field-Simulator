#include <shader.h>
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

Shader::Shader (const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile (vertexPath);

	// Please check your spellig before any suicide attempts
	if (!vShaderFile.is_open ())
	{
		std::cerr << "ERROR: Could not open shader file: " << vertexPath << '\n';
		std::exit (EXIT_FAILURE);
	}
	std::cout << "Trying to open fragment shader at: " << std::filesystem::absolute (fragmentPath) << '\n';
	std::ifstream fShaderFile (fragmentPath);
	if (!fShaderFile.is_open ())
	{
		std::cerr << "ERROR: Could not open shader file: " << fragmentPath << '\n';
		std::exit (EXIT_FAILURE);
	}
	std::stringstream vShaderStream, fShaderStream;

	vShaderStream << vShaderFile.rdbuf ();
	fShaderStream << fShaderFile.rdbuf ();
	vertexCode = vShaderStream.str ();
	fragmentCode = fShaderStream.str ();

	const char* vShaderCode = vertexCode.c_str ();
	const char* fShaderCode = fragmentCode.c_str ();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// vertex shader
	vertex = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vertex, 1, &vShaderCode, nullptr);
	glCompileShader (vertex);
	glGetShaderiv (vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog (vertex, 512, nullptr, infoLog);
		std::cout << "Vertex shader compile error:\n" << infoLog << std::endl;
		std::exit (EXIT_FAILURE);
	}

	// fragment shader
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
