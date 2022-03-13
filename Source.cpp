#define SDL_MAIN_HANDLED
#define STB_IMAGE_IMPLEMENTATION

#include "vertexBuffer.h"
#include "vertexArray.h"
#include "input.h"
#include "texture.h"
#include "shaderProgram.h"
#include "camera.h"
#include "Scene.h"
#include "Game.h"
#include "Plane.h"
#include "screen.h"
#include "renderTexture.h"
#include "throttleUI.h"
#include "orbitLight.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/ext.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <memory>




int main()
{
	//std::shared_ptr<Scene> game = std::make_shared<Scene>();




	SDL_Window* window = SDL_CreateWindow("ADAM_HURST_CG_PROJECT", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (!SDL_GL_CreateContext(window)){	throw std::exception();	}
	if (glewInit() != GLEW_OK){	throw std::exception();	}

	
  
	

	//std::shared_ptr<texture> textureId = std::make_shared<texture>("Models/curuthers/Whiskers_diffuse.png");
	//std::shared_ptr<texture> textureId = std::make_shared<texture>("D:/UniDocs/year_2/computerGraphicsProgramming/assets/projectLevelTexture.png");
	
	//std::shared_ptr<texture> textureId = std::make_shared<texture>("Models/plane/plane.png");
	//std::shared_ptr<vertexArray> modelVAO = std::make_shared<vertexArray>("D:/UniDocs/year_2/computerGraphicsProgramming/assets/prop.obj");
	//std::shared_ptr<vertexArray> modelVAO = std::make_shared<vertexArray>("Models/plane/plane.obj");
	//std::shared_ptr<vertexArray> modelVAO = std::make_shared<vertexArray>("D:/UniDocs/year_2/computerGraphicsProgramming/assets/projectLevel.obj");
	std::shared_ptr<texture> textureId = std::make_shared<texture>("Models/newMap/mapTexture.png");
	std::shared_ptr<vertexArray> modelVAO = std::make_shared<vertexArray>("Models/newMap/newTestMap.obj");
	std::shared_ptr<shaderProgram> program = std::make_shared<shaderProgram>(shaderProgram::SHADERTYPE::SHADER_LIGHT);
	
	std::shared_ptr<texture> sunTextureId = std::make_shared<texture>("Models/sun/sun.png");
	std::shared_ptr<vertexArray> sunModelVAO = std::make_shared<vertexArray>("Models/sun/sun.obj");
	std::shared_ptr<shaderProgram> sunProgram = std::make_shared<shaderProgram>(shaderProgram::SHADERTYPE::SHADER_BASIC);

	std::shared_ptr<renderTexture> sceneTexture = std::make_shared<renderTexture>(glm::ivec2(1920,1080));

	std::shared_ptr<orbitLight> sceneLight = std::make_shared<orbitLight>(glm::vec3(0,0,0),glm::vec3(1,0,0), 1.0f, 1000.0f);


	bool stopped = false;
	
	//SDL_ShowCursor(SDL_FALSE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	input inp;
	std::shared_ptr<camera> cam = std::make_shared<camera>();
	

	
	
	
	std::shared_ptr<screen> scrn = std::make_shared<screen>();

	
	std::shared_ptr<Plane> testPlane = std::make_shared<Plane>();
	
	scrn->update(textureId->getId());
	std::shared_ptr<throttleUI> ui = std::make_shared <throttleUI>();


	float lastTime = 0.0f;
	float diffTime = 0.0f;
	float deltaTime = 0.0f;
	float currentTime = 0.0f;

	int currentCamera = 0;

	while (!stopped)
	{
		

		
		int width = 0;
		int height = 0;
		SDL_GetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glEnable(GL_DEPTH_TEST);
	
		stopped = inp.pollInput(glm::ivec2(width, height));
		cam->processInputs(inp);

		//sceneTexture->bind();

		glClearColor(0.584313725f, 0.784313725f, 0.847058824f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		if (inp.getKey_v())		{ scrn->update(sunTextureId->getId()); }
		if (inp.getKey_esc())	{ stopped = true; }
		if (inp.getKey_n()) { currentCamera = 0; }
		if (inp.getKey_m()) { currentCamera = 1; }

		// update the light
		//sceneLight->update(deltaTime);

		// update and render plane and attached objects
		if (currentCamera == 0)
		{
			testPlane->update(inp, testPlane->cockpitCamera->getMatrix(), deltaTime);
			glm::mat4 model(1.0f);
			model = glm::scale(model, glm::vec3(10, 10, 10));
			glm::mat4 projection = glm::perspective(glm::radians(60.0f), ((1.0f * width) / (1.0f * height)), 0.1f, 10000.0f);
			model = glm::translate(model, glm::vec3(0, -5, -8.5f));
			program->update(projection, testPlane->cockpitCamera->getMatrix(), model, modelVAO, textureId->getId());
		}
		else if (currentCamera == 1)
		{
			testPlane->update(inp, testPlane->rearCamera->getMatrix(), deltaTime);
			glm::mat4 model(1.0f);
			model = glm::scale(model, glm::vec3(10, 10, 10));
			glm::mat4 projection = glm::perspective(glm::radians(60.0f), ((1.0f * width) / (1.0f * height)), 0.1f, 10000.0f);
			model = glm::translate(model, glm::vec3(0, -5, -8.5f));
			program->update(projection, testPlane->rearCamera->getMatrix(), model, modelVAO, textureId->getId());
		}
		
		testPlane->draw(sceneLight, deltaTime, currentCamera);

		// update and render the terrain
		
		//program->update(projection, testPlane->cockpitCamera->getMatrix(), model, modelVAO, textureId->getId(), sceneLight);

		


		// update and render the sun object
		//model = glm::mat4(1.0f);
		//sunProgram->update(projection, testPlane->cockpitCamera, model, *sunModelVAO, sunTextureId->getId());	

		//sceneTexture->unBind();

		//scrn->update(sceneTexture->getTexture());
		//scrn->draw(testPlane->cockpitCamera->getMatrix());
		
		ui->update(testPlane->throttle);

		SDL_GL_SwapWindow(window);	

		currentTime = SDL_GetTicks();
		float diffTime = currentTime - lastTime;
		lastTime = currentTime;
		deltaTime = diffTime / 1000.0f;
	}
}
