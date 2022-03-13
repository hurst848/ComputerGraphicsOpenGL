#include "MeshComponent.h"
#include "vertexArray.h"

MeshComponent::MeshComponent()
{
	Mesh = std::make_shared<vertexArray>();
}
MeshComponent::MeshComponent(std::string meshPath)
{
	Mesh = std::make_shared<vertexArray>(meshPath);
}

GLuint MeshComponent::getId()
{
	return Mesh->getId();
}