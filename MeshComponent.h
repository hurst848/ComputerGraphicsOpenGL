#include "Component.h"
#include "GL/glew.h"

struct vertexArray;

#include <memory>

struct MeshComponent : public Component
{
public:
	virtual std::string ComponentName() override
	{
		return "MESH_COMPONENT";
	}

	MeshComponent();
	MeshComponent(std::string meshPath);

	GLuint getId();

private:
	std::shared_ptr<vertexArray> Mesh;
};