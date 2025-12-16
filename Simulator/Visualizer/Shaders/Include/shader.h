#ifndef VISUALIZER_SHADERS_SHADER_
#define VISUALIZER_SHADERS_SHADER_

class Shader
{
public:
	Shader (const char* vertexPath, const char* fragmentPath);
	void use () const;
	unsigned int ID;
};
#endif // VISUALIZER_SHADERS_SHADER_