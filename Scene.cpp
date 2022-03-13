#include "Scene.h"

#include "GameObject.h"

#include "GL/glew.h"
void Scene::draw()
{
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		gameObjects.at(i)->draw();
	}

}

void Scene::update()
{
	
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		gameObjects.at(i)->update();
	}
}