#include <GL/glew.h>
#include <glm/ext.hpp>

#include <vector>


struct vertexBuffer
{
public:
	vertexBuffer();
	~vertexBuffer();
	void addData(glm::vec2 _value);
	void addData(glm::vec3 _value);
	void addData(glm::vec4 _value);
	int getComponents();
	GLuint getId();
private:
	GLuint id;
	int components;
	std::vector<GLfloat> data;
	bool dirty;
};