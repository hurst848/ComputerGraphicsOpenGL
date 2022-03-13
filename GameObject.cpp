#include "GameObject.h"
#include "vertexArray.h"
#include "texture.h"

GameObject::GameObject()
{
	modelMatrix = glm::mat4(1.0f);
	
}

GameObject::GameObject(std::string _modelPath, std::string _texturePath)
{
	model = std::make_shared<vertexArray>(_modelPath);
	modelTexture = std::make_shared<texture>(_texturePath);
}

GameObject::~GameObject()
{

}
void GameObject::draw() {}
void GameObject::update() {}