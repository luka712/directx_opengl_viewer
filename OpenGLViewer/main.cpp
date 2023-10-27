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
#include "mesh/UnlitMesh.hpp"
#include "mesh/ReflectiveMesh.hpp"
#include "mesh/RefractionMesh.hpp"
#include "render_target/RenderTarget.hpp"
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"

using namespace Viewer;

Viewer::TextureLoader g_texutureLoader;

void SetupImGui(SDL_Window* window, SDL_GLContext glContext)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForOpenGL(window, glContext);
	ImGui_ImplOpenGL3_Init("#version 450");
}

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

	RenderTarget renderTarget(renderer, 256, 256);
	renderTarget.Initialize();

	Viewer::CubeTexture *skyboxTexture = g_texutureLoader.LoadFromImg("assets/right.jpg",
																	  "assets/left.jpg",
																	  "assets/top.jpg",
																	  "assets/bottom.jpg",
																	  "assets/front.jpg",
																	  "assets/back.jpg");

	Geometry cubeGeometry = Geometry::CreateCubeGeometry();
	Mesh cubeMesh(cubeGeometry);
	cubeMesh.Initialize();
	cubeMesh.DebugNormals = true;
	cubeMesh.Material.DiffuseTexture = g_texutureLoader.LoadFromImg("assets/crate_texture.png");
	cubeMesh.Material.SpecularTexture = g_texutureLoader.LoadFromImg("assets/crate_specular.png");
	cubeMesh.Material.DiffuseCoefficient = 0.5f;
	cubeMesh.Material.SpecularCoefficient = 3.0f;
	cubeMesh.Material.Shininess = 32.0f;
	cubeMesh.Transform.Position.x = 1.0f;

	Geometry quadGeometry = Viewer::Geometry::CreateQuadGeometry();
	Mesh floorMesh(quadGeometry);
	floorMesh.DebugNormals = true;
	floorMesh.Initialize();
	floorMesh.Material.DiffuseTexture = g_texutureLoader.LoadFromImg("assets/wood_diffuse.png");
	floorMesh.Material.SpecularTexture = g_texutureLoader.LoadFromImg("assets/wood_specular.png");
	floorMesh.Material.DiffuseCoefficient = 0.5f;
	floorMesh.Material.SpecularCoefficient = 2.0f;
	floorMesh.Material.Shininess = 32.0f;
	floorMesh.Material.TextureTilling = glm::vec2(5.0f, 5.0f);
	floorMesh.Transform.Position.y = -0.5;
	floorMesh.Transform.Scale.x = 10;
	floorMesh.Transform.Scale.y = 10;
	floorMesh.Transform.Rotation.x = 90;

	Mesh mirrorMesh(quadGeometry);
	mirrorMesh.Initialize();
	mirrorMesh.DebugNormals = true;
	mirrorMesh.Transform.Position = glm::vec3(0, 2, 5);
	mirrorMesh.Transform.Scale = glm::vec3(5, 5,1);
	mirrorMesh.Material.DiffuseTexture = &renderTarget.GetTexture();
	mirrorMesh.Material.SpecularTexture = &renderTarget.GetTexture();

	ReflectiveMesh reflectiveCubeMesh(cubeGeometry);
	reflectiveCubeMesh.Initialize();
	reflectiveCubeMesh.Material.EnvMapTexture = skyboxTexture;
	reflectiveCubeMesh.Transform.Position.x = 3.0f;

	RefractionMesh refractionCubeMesh(cubeGeometry);
	refractionCubeMesh.Initialize();
	refractionCubeMesh.Material.RefractionIndex = 1.0f;
	refractionCubeMesh.Material.EnvMapTexture = skyboxTexture;
	refractionCubeMesh.Transform.Position.x = -3.0f;

	UnlitMesh unlitMesh[5] =
		{
			UnlitMesh(cubeGeometry),
			UnlitMesh(cubeGeometry),
			UnlitMesh(cubeGeometry),
			UnlitMesh(cubeGeometry),
			UnlitMesh(cubeGeometry),
		};
	for (int i = 0; i < 5; i++)
	{
		unlitMesh[i].Initialize();
	}

	Skybox skybox;
	skybox.Initialize();
	skybox.SkyTexture = skyboxTexture;

	SceneLights sceneLights;
	sceneLights.Initialize();

	OrbitCamera camera(float(clientWidth) / clientHeight);
	camera.Initialize();

	Camera textureCamera(1);
	textureCamera.EyePosition = mirrorMesh.Transform.Position;
	textureCamera.EyePosition.z = 6;
	textureCamera.LootAtPosition = mirrorMesh.Transform.Position + glm::vec3(0, 0, -1);
	textureCamera.Initialize();

	MouseState mouseState;

	float cubeDirection = 0.01;

	SetupImGui(window, renderer.GetGLContext());	

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


	while (true)
	{
		mouseState.ResetDeltas();
		SDL_Event Event;

		while (SDL_PollEvent(&Event))
		{
			ImGui_ImplSDL2_ProcessEvent(&Event);

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
		glm::vec3 I = camera.GetLookAtPosition() - camera.EyePosition;
		textureCamera.LootAtPosition = glm::reflect( I, glm::vec3(0, 0, 1));
		textureCamera.Update(mouseState);
		sceneLights.Update();

		cubeMesh.Transform.Position += cubeDirection;
		if (cubeMesh.Transform.Position.y <= 0)
		{
			cubeDirection = 0.01;
		}
		else if (cubeMesh.Transform.Position.y >= 1.5)
		{
			cubeDirection = -0.01;
		}
		cubeMesh.Update();
		floorMesh.Update();
		reflectiveCubeMesh.Update();
		refractionCubeMesh.Update();
		mirrorMesh.Update();
		for (int i = 0; i < 5; i++)
		{
			unlitMesh[i].Transform.Position = sceneLights.GetPointLights(i).Position;
			unlitMesh[i].Transform.Scale = glm::vec3(.2f);
			unlitMesh[i].Material.DiffuseColor = sceneLights.GetPointLights(i).Color;
			unlitMesh[i].Material.Intensity = sceneLights.GetPointLights(i).Intensity;
			unlitMesh[i].Update();
		}

		// IMGUI
	    // Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::End();
		}

		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		// Rendering
		ImGui::Render();

		// NORMAL PASS
		renderer.Begin();

		// MIRROR PASS
		if (true)
		{
			renderTarget.Use();

			// Draw
			cubeMesh.Draw(textureCamera, sceneLights);
			floorMesh.Draw(textureCamera, sceneLights);
			reflectiveCubeMesh.Draw(textureCamera);
			refractionCubeMesh.Draw(textureCamera);
			skybox.Draw(textureCamera);

			renderTarget.Stop();
		}

		// Draw
		cubeMesh.Draw(camera, sceneLights);
		floorMesh.Draw(camera, sceneLights);
		for (int i = 0; i < 5; i++)
		{
			unlitMesh[i].Draw(camera);
		}
		reflectiveCubeMesh.Draw(camera);
		refractionCubeMesh.Draw(camera);
		mirrorMesh.Draw(camera, sceneLights);
		skybox.Draw(camera);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		renderer.End();

		SDL_Delay(16);
	}

	SDL_DestroyWindow(window);

	return 0;
}