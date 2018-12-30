#include "common.h"
#include "window.h"
#include "renderer.h"
#include "texture.h"

#include "material.h"
#include "model.h"

#define W 1920
#define H 1080


int main(int argc, char** argv)
{
	Window window(W, H, "OpenGL",true);
	Input input(window);

	Shader shader("../assets/shaders/shader.vert", "../assets/shaders/shader.frag");
	model_t *a = az_model_aps2_load(argv[1]);
	model_t *b = az_model_aps2_load(argv[2]);
	Camera cam(input, float(W)/H);
	
	float angle = 0.f;
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Scene scene;
	scene.AddModel(a);
	scene.AddModel(b);
	b->transform.model = glm::scale(glm::vec3(100,100,100));
	Renderer renderer = Renderer();

	while(!window.ShouldClose())
	{
		b->transform.model = glm::rotate(b->transform.model,glm::radians(1.f),glm::vec3(1,1,0));
		cam.Update();
		window.Update();
		window.Clear();
		
		renderer.DrawScene(scene,shader,cam);
		
		window.SwapBuffers();		
	}	
	return 0;
}