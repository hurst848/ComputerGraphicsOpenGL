#include <GL/glew.h>
#include <glm/ext.hpp>

#include <string>
#include <memory>

struct vertexArray;
struct camera;
struct orbitLight;

struct shaderProgram
{
public:
	enum SHADERTYPE
	{
		SHADER_SUPER_BASIC,
		SHADER_BASIC,
		SHADER_LIGHT,
		SHADER_ORTHO
	};
	shaderProgram(std::string _vertexPath, std::string _fragementPath);
	shaderProgram(SHADERTYPE type);

	void update(glm::mat4 _proj, glm::mat4 _view, glm::mat4 _model, vertexArray &vaoID, GLuint texID);
	void update(glm::mat4 _proj, std::shared_ptr<camera> _camera, glm::mat4 _model, vertexArray& vaoID, GLuint texID);
	void update(glm::mat4 _proj, glm::mat4 _view, glm::mat4 _model, std::shared_ptr<vertexArray> vaoID, GLuint texID);
	void update(glm::mat4 _proj, std::shared_ptr<vertexArray> vaoId, GLuint texId);
	void update(glm::mat4 _proj, glm::mat4 _view, glm::mat4 _model, std::shared_ptr<vertexArray> vaoID, GLuint texID, std::shared_ptr<orbitLight> light);
	GLuint getId();
	
	
private:
	SHADERTYPE programType;
	GLuint id;
	std::string inputBuffer;

	//std::shared_ptr<vertexArray> data;

	const GLchar* readShader(std::string _path);
	
	glm::vec3 lightColour;
	glm::vec3 lightPos;
	glm::vec3 cameraPos;
	float ambientStrength;


	GLuint modelRef;
	GLuint viewRef;
	GLuint projRef;
	GLuint lightColourRef;
	GLuint ambientStrengthRef;
	GLuint lightPosRef;
	GLuint cameraPosRef;

};
