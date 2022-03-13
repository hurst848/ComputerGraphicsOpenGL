#pragma once

#ifndef _SCENE_H_
#define _SCENE_H_


#include <memory>
#include <vector>
#include "glm/ext.hpp"

struct GameObject;
struct camera;
struct shaderProgram;

struct Scene
{
public:
	std::vector< std::shared_ptr<GameObject> > gameObjects;
	std::vector< std::shared_ptr<camera> > cameras;
	std::vector < std::shared_ptr<shaderProgram> > shaders;
	int mainCamera = 0;

	void update();
	void draw();

	glm::ivec2 screenSize;
};

#endif