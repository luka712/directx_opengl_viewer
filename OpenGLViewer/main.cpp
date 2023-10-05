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
#include "transform/Transform.hpp"

using namespace Viewer;

Viewer::TextureLoader g_texutureLoader;

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);

	unsigned int clientWidth = 1280;
	unsigned int clientHeight = 720;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	SDL_Window* window = SDL_CreateWindow("OBJ Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, clientWidth, clientHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	Renderer renderer(*window);
	if (!renderer.Initialize(clientWidth, clientHeight))
	{
		return -1;
	}

	Geometry geometry = Geometry::CreateCubeGeometry();
	GeometryBuffer createGeometryBuffer;
	createGeometryBuffer.Initialize(geometry.positionVertices, geometry.indices, geometry.textureVertices, geometry.normalVertices, geometry.colorVertices);

	Geometry floorGeometry = Geometry::CreateQuadGeometry();
	GeometryBuffer floorGeometryBuffer;
	floorGeometryBuffer.Initialize(floorGeometry.positionVertices, floorGeometry.indices, floorGeometry.textureVertices, floorGeometry.normalVertices, floorGeometry.colorVertices);

	// glm::mat4x4 projectionViewMatrix = glm::ortho(-10.0, 10.0, -5.0, 5.0, -1.0, 1.0);


	StandardMaterial crateMaterial;
	crateMaterial.Initialize();
	crateMaterial.DiffuseTexture = g_texutureLoader.LoadFromImg("assets/crate_texture.png");
	crateMaterial.SpecularTexture = g_texutureLoader.LoadFromImg("assets/crate_specular.png");
	crateMaterial.DiffuseCoefficient = 0.5;
	crateMaterial.SpecularCoefficient = 3.0;
	crateMaterial.Shininess = 12.0;

	StandardMaterial floorMaterial;
	floorMaterial.Initialize();
	floorMaterial.DiffuseTexture = g_texutureLoader.LoadFromImg("assets/wood_diffuse.png");
	floorMaterial.SpecularTexture = g_texutureLoader.LoadFromImg("assets/wood_specular.png");
	floorMaterial.DiffuseCoefficient = 0.5;
	floorMaterial.SpecularCoefficient = 3.0;
	floorMaterial.Shininess = 24.0;

	SceneLights sceneLights;
	sceneLights.Initialize();

	Transform transform;
	transform.Initialize();

	Transform floorTransform;
	floorTransform.Initialize();
	floorTransform.Position.y = -0.5;
	floorTransform.Scale.x = 10;
	floorTransform.Scale.y = 10;
	floorTransform.Rotation.x = 90;

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
		transform.Update();
		floorTransform.Update();

		renderer.Begin();

		// Draw
		crateMaterial.Use();

		crateMaterial.UpdateSelfProperties();
		crateMaterial.UpdateCameraProperties(camera);
		crateMaterial.UpdateTranformProperties(transform);
		crateMaterial.UpdateLightsProperties(
			sceneLights.GetAmbientLightBuffer(),
			sceneLights.GetDirectionalLightsBuffer(),
			sceneLights.GetPointLightsBuffer());

		createGeometryBuffer.Draw();

		// floor
		floorMaterial.Use();

		floorMaterial.UpdateSelfProperties();
		floorMaterial.UpdateCameraProperties(camera);
		floorMaterial.UpdateTranformProperties(floorTransform);
		floorMaterial.UpdateLightsProperties(
			sceneLights.GetAmbientLightBuffer(),
			sceneLights.GetDirectionalLightsBuffer(),
			sceneLights.GetPointLightsBuffer());

		floorGeometryBuffer.Draw();

		renderer.End();

		SDL_Delay(16);
	}

	SDL_DestroyWindow(window);

	return 0;
}