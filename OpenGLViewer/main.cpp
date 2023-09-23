#include <SDL.h>
#include <glad/glad.h>
#include "shader/StandardMaterialShader.hpp"
#include "buffer/GeometryBuffer.hpp"
#include "renderer/Renderer.hpp"
#include <glm/glm.hpp>
#include "geometry/Geometry.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace Viewer;

int main(int argc, char *args[])
{
   SDL_Init(SDL_INIT_VIDEO);

   unsigned int clientWidth = 1280;
   unsigned int clientHeight = 720;
   SDL_Window *window = SDL_CreateWindow("OBJ Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, clientWidth, clientHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

   Renderer renderer(*window);
   if (!renderer.Initialize(clientWidth, clientHeight))
   {
      return -1;
   }
   StandardMaterialShader shader;
   shader.Initialize();

   Geometry geometry = Geometry::CreateQuadGeometry();
   GeometryBuffer geometryBuffer;
   geometryBuffer.Initialize(geometry.positionVertices, geometry.indices);

   glm::mat4x4 projectionViewMatrix = glm::ortho(-10.0, 10.0, -5.0, 5.0, -1.0, 1.0);
   glm::mat4x4 modelMatrix = glm::mat4x4(1.0f);

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
      shader.SetProjectionViewMatrix(projectionViewMatrix);
      shader.SetModelMatrix(modelMatrix);
      geometryBuffer.Draw();

      renderer.End();

      SDL_Delay(16);
   }

   SDL_DestroyWindow(window);

   return 0;
}