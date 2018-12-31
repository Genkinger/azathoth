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

	Shader shader("../assets/shaders/shader.vert", "../assets/shaders/shader.frag");
	Shader geometry("../assets/shaders/deferred/geometry.vert","../assets/shaders/deferred/geometry.frag");
	Shader lighting("../assets/shaders/deferred/lighting.vert","../assets/shaders/deferred/lighting.frag");
	model_t *a = az_model_aps2_load(argv[1]);
	//model_t *b = az_model_aps2_load(argv[2]);
	Camera cam(input, float(W)/H);
	
	float angle = 0.f;
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Scene scene;
	scene.AddModel(a);
	//scene.AddModel(b);
	//b->transform.model = glm::scale(glm::vec3(100,100,100));
	Renderer renderer = Renderer(W,H);
	renderer.lighting = &lighting;
	renderer.geometry = &geometry;
	renderer.forward = &shader;

	while(!window.ShouldClose())
	{
		//b->transform.model = glm::rotate(b->transform.model,glm::radians(1.f),glm::vec3(1,1,0));
		cam.Update();
		window.Update();
		
		
		//renderer.DrawSceneForward(scene,cam);
		renderer.DrawSceneDeferred(scene,cam);
		
		window.SwapBuffers();		
	}	
	return 0;
}