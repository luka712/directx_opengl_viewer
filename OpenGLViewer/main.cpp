#include <SDL.h>
#include <glad/glad.h>
#include "shader/StandardMaterialShader.hpp"
#include "buffer/GeometryBuffer.hpp"
#include "renderer/Renderer.hpp"
#include <glm/glm.hpp>
#include "geometry/Geometry.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "texture/Texture2D.hpp"
#include "scene/SceneLights.hpp"
#include "material/MaterialData.hpp"
#include "buffer/UniformBuffer.hpp"
#include "material/StandardMaterial.hpp"
#include "camera/Camera.hpp"
#include "camera/OrbitCamera.hpp"
#include "loaders/TextureLoader.hpp"
#include "scene/SceneLights.hpp"
#include "mesh/Mesh.hpp"
#include "skybox/Skybox.hpp"

using namespace Viewer;

Viewer::TextureLoader g_texutureLoader;

int main(int argc, char *args[])
{
	SDL_Init(SDL_INIT_VIDEO);

	unsigned int clientWidth = 1280;
	unsigned int clientHeight = 720;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	SDL_Window *window = SDL_CreateWindow("OBJ Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, clientWidth, clientHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	Renderer renderer(*window);
	if (!renderer.Initialize(clientWidth, clientHeight))
	{
		return -1;
	}

	Geometry cubeGeometry = Geometry::CreateCubeGeometry();
	Mesh cubeMesh(cubeGeometry);
	cubeMesh.Initialize();
	cubeMesh.Material.DiffuseTexture = g_texutureLoader.LoadFromImg("assets/crate_texture.png");
	cubeMesh.Material.SpecularTexture = g_texutureLoader.LoadFromImg("assets/crate_specular.png");
	cubeMesh.Material.DiffuseCoefficient = 0.5f;
	cubeMesh.Material.SpecularCoefficient = 3.0f;
	cubeMesh.Material.Shininess = 12.0f;

	Geometry floorGeometry = Viewer::Geometry::CreateQuadGeometry();
	Mesh floorMesh(floorGeometry);
	floorMesh.Initialize();
	floorMesh.Material.DiffuseTexture = g_texutureLoader.LoadFromImg("assets/wood_diffuse.png");
	floorMesh.Material.SpecularTexture = g_texutureLoader.LoadFromImg("assets/wood_specular.png");
	floorMesh.Material.DiffuseCoefficient = 0.5f;
	floorMesh.Material.SpecularCoefficient = 3.0f;
	floorMesh.Material.Shininess = 24.0f;
	floorMesh.Material.TextureTilling = glm::vec2(5.0f, 5.0f);
	floorMesh.Transform.Position.y = -0.5;
	floorMesh.Transform.Scale.x = 10;
	floorMesh.Transform.Scale.y = 10;
	floorMesh.Transform.Rotation.x = 90;

	Skybox skybox;
	skybox.Initialize();
	skybox.SkyTexture = g_texutureLoader.LoadFromImg("assets/right.jpg",
													 "assets/left.jpg",
													 "assets/top.jpg",
													 "assets/bottom.jpg",
													 "assets/front.jpg",
													 "assets/back.jpg");

	SceneLights sceneLights;
	sceneLights.Initialize();

	OrbitCamera camera(float(clientWidth) / clientHeight);
	camera.Initialize();

	MouseState mouseState;

	while (true)
	{
		mouseState.ResetDeltas();
		SDL_Event Event;

		while (SDL_PollEvent(&Event))
		{
			switch (Event.type)
			{
			case SDL_QUIT:
				return 0;
				break;
				// Mouse events
			case SDL_MOUSEWHEEL:
				mouseState.DeltaWheelY = Event.wheel.y;
				break;
			case SDL_MOUSEMOTION:
				mouseState.DeltaX = Event.motion.xrel;
				mouseState.DeltaY = Event.motion.yrel;
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (Event.button.button)
				{
				case SDL_BUTTON_LEFT:
					mouseState.LeftButton = true;
					break;
				case SDL_BUTTON_RIGHT:
					mouseState.RightButton = true;
					break;
				case SDL_BUTTON_MIDDLE:
					mouseState.MiddleButton = true;
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (Event.button.button)
				{
				case SDL_BUTTON_LEFT:
					mouseState.LeftButton = false;
					break;
				case SDL_BUTTON_RIGHT:
					mouseState.RightButton = false;
					break;
				case SDL_BUTTON_MIDDLE:
					mouseState.MiddleButton = false;
					break;
				}
				break;
			}
		}

		camera.Update(mouseState);
		sceneLights.Update();
		cubeMesh.Update();
		floorMesh.Update();

		renderer.Begin();

		// Draw
 		skybox.Draw(camera);
		cubeMesh.Draw(camera, sceneLights);
		floorMesh.Draw(camera, sceneLights);

		renderer.End();

		SDL_Delay(16);
	}

	SDL_DestroyWindow(window);

	return 0;
}