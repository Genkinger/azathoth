#include "common.h"
#include "window.h"
#include "renderer.h"
#include "texture.h"

#include "material.h"


#define W 800
#define H 600


int main(int argc, char** argv)
{
	Window window(W, H, "OpenGL");
	Input input(window);

	Shader shader("../assets/shaders/shader.vert", "../assets/shaders/shader.frag");
	mesh_t a = az_mesh_load_aps2(argv[1],argv[2]);
	
	material_lib_t material = az_ams1_material_load("sponza.ams1");
	printf("Material: %d \n",material.num_materials);

	//a.texture = az_texture_farbfeld_load("../assets/materials/textures/default.ff");
	Camera cam(input, float(W)/H);
	
	float angle = 0.f;
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Scene scene;
	scene.AddMesh(&a);
	
	Renderer renderer = Renderer();

	while(!window.ShouldClose())
	{
		a.transform.model = glm::translate(glm::vec3(0,0,5)) * glm::rotate(glm::radians(angle),glm::vec3(0,1,0));
		
		angle += 0.05f;
		
		cam.Update();
		window.Update();
		window.Clear();
		
		renderer.DrawScene(scene,shader,cam);
		
		window.SwapBuffers();		
	}	
	return 0;
}