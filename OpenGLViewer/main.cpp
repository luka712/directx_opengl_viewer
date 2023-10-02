#include <SDL.h>
#include <glad/glad.h>
#include "shader/StandardMaterialShader.hpp"
#include "buffer/GeometryBuffer.hpp"
#include "renderer/Renderer.hpp"
#include <glm/glm.hpp>
#include "geometry/Geometry.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "loaders/ImageLoader.hpp"
#include "texture/Texture2D.hpp"
#include "light/AmbientLight.hpp"
#include "light/DirectionalLight.hpp"
#include "light/PointLight.hpp"

using namespace Viewer;

Viewer::AmbientLight ambientLight = { 0.3f, glm::vec3(1, 1, 1) };
Viewer::DirectionalLight directionalLights[3] = {
	{ glm::vec3(1, -1, 0), 1.0f, glm::vec3(1, 1, 1) },
	{ glm::vec3(-1, 0, 0), 0.5f, glm::vec3(1, 1, 1) },
	{ glm::vec3(1, 0, 0), 0.5f, glm::vec3(1, 1, 1) },
};
Viewer::PointLight pointLights[5] = {
	{ glm::vec3(1, 0, 0), 0.0f, glm::vec3(1, 0, 0) },
	{ glm::vec3(0, 1, 0), 0.0f, glm::vec3(0, 1, 0) },
	{ glm::vec3(0, 0, 1), 0.0f, glm::vec3(0, 0, 1)  },
	{ glm::vec3(1, 1, 0), 0.0f, glm::vec3(1, 1, 0)  },
	{ glm::vec3(0, 1, 1), 0.0f, glm::vec3(0, 1, 1)  },	
};


int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);

	unsigned int clientWidth = 1280;
	unsigned int clientHeight = 720;
	SDL_Window* window = SDL_CreateWindow("OBJ Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, clientWidth, clientHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	Renderer renderer(*window);
	if (!renderer.Initialize(clientWidth, clientHeight))
	{
		return -1;
	}
	StandardMaterialShader shader;
	shader.Initialize();

	Geometry geometry = Geometry::CreateCubeGeometry();
	GeometryBuffer geometryBuffer;
	geometryBuffer.Initialize(geometry.positionVertices, geometry.indices, geometry.textureVertices, geometry.normalVertices, geometry.colorVertices);

	glm::vec3 eyePosition = glm::vec3(3, 3, -3);
	glm::vec3 lookAtPosition = glm::vec3(0, 0, 0);
	glm::vec3 upVector = glm::vec3(0, 1, 0);

	glm::mat4x4 viewMatrix = glm::lookAt(eyePosition, lookAtPosition, upVector);
	float aspectRatio = (float)clientWidth / (float)clientHeight;
	glm::mat4x4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

	glm::mat4x4 projectionViewMatrix = projectionMatrix * viewMatrix;

	// glm::mat4x4 projectionViewMatrix = glm::ortho(-10.0, 10.0, -5.0, 5.0, -1.0, 1.0);
	glm::mat4x4 modelMatrix = glm::mat4x4(1.0f);
	glm::mat3x3 normalMatrix = glm::transpose(glm::inverse(glm::mat3x3(modelMatrix)));


	ImageData* imgData = ImageLoader::LoadImage("assets/crate_texture.png");
	Texture2D diffuseTexture(imgData->data, imgData->width, imgData->height, imgData->bytePerPixel);
	diffuseTexture.Initialize();

	ImageData* specularImgData = ImageLoader::LoadImage("assets/crate_specular.png");
	Texture2D specularTexture(*specularImgData);
	specularTexture.Initialize();

	while (true)
	{
		SDL_Event Event;
		while (SDL_PollEvent(&Event))
		{
			switch (Event.type)
			{
			case SDL_QUIT:
				return 0;
				break;
			}
		}

		renderer.Begin();

		// Draw
		shader.Use();

		// matrices
		shader.SetProjectionViewMatrix(projectionViewMatrix);
		shader.SetModelMatrix(modelMatrix);
		shader.SetNormalMatrix(normalMatrix);

		// material 
		shader.SetDiffuseTexture(diffuseTexture);
		shader.SetSpecularTexture(specularTexture);
		shader.SetDiffuseCoefficient(0.5);
		shader.SetSpecularCoefficient(3.0);
		shader.SetShininess(12.0);

		shader.SetCameraPosition(eyePosition);

		// lights 
		shader.SetAmbientLight(ambientLight.Intensity, ambientLight.Color);
		for (size_t i = 0; i < 3; i++)
		{
			shader.SetDirectionalLight(i, directionalLights[i].Direction, directionalLights[i].Intensity, directionalLights[i].Color);
		}
		for(size_t i = 0; i < 5; i++)
		{
			shader.SetPointLight(i, pointLights[i].Position, pointLights[i].Intensity, pointLights[i].Color);
		}

		geometryBuffer.Draw();

		renderer.End();

		SDL_Delay(16);
	}

	SDL_DestroyWindow(window);

	return 0;
}