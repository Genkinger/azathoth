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
	model_t *a = az_model_aps2_load(argv[1]);

	Camera cam(input, float(W)/H);
	
	float angle = 0.f;
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Scene scene;
	scene.AddModel(a);
	
	Renderer renderer = Renderer();

	while(!window.ShouldClose())
	{
		a->meshes[0]->transform.model = glm::translate(glm::vec3(4,0,0)) * glm::rotate(glm::radians(angle),glm::vec3(0,1,0));
		
		angle += 0.05f;
		
		cam.Update();
		window.Update();
		window.Clear();
		
		renderer.DrawScene(scene,shader,cam);
		
		window.SwapBuffers();		
	}	
	return 0;
}