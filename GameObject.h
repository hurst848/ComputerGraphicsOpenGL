#include "glm/ext.hpp"

#include "Game.h"

#include <memory>
#include <vector>
#include <string>


struct vertexArray;
struct texture;

struct GameObject
{
public:
	GameObject();
	GameObject(std::string _modelPath, std::string _texturePath);
	~GameObject();

	virtual void draw();
	virtual void update();
	//std::shared_ptr< std::vector<Scene> > Game;
protected:
	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;

	glm::vec3 position;
	glm::vec3 rotaion;

	std::shared_ptr<vertexArray> model;
	std::shared_ptr<texture> modelTexture;
	
	//std::shared_ptr<Scene> game;
};