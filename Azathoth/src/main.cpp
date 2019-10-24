#include "common.h"
#include "window.h"
#include "renderer.h"
#include "texture.h"

#include "material.h"
#include "model.h"

#define W 800
#define H 600


int main(int argc, char** argv)
{
	Window window(W, H, "OpenGL");
	Input input(window);

	Shader shader("shader.vert", "shader.frag");
	//Shader geometry("../assets/shaders/deferred/geometry.vert","../assets/shaders/deferred/geometry.frag");
	//Shader lighting("../assets/shaders/deferred/lighting.vert","../assets/shaders/deferred/lighting.frag");
	model_t *a = az_model_aps2_load(argv[1]);

	Camera cam(input, float(W)/H);
	
	float angle = 0.f;
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Scene scene;
	scene.AddModel(a);
	Renderer renderer = Renderer(W,H);
	//renderer.lighting = &lighting;
	//renderer.geometry = &geometry;
	renderer.forward = &shader;

	while(!window.ShouldClose())
	{

		cam.Update();
		window.Update();
		
		
		renderer.DrawSceneForward(scene,cam);
		//renderer.DrawSceneDeferred(scene,cam);
		
		window.SwapBuffers();		
	}	
	return 0;
}