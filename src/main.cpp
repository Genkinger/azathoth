#include <iostream>
#include "window.h"
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "shader.h"
#include "mesh.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "log.h"
#include "input.h"
#include "camera.h"
#include "scene.h"
#include "renderer.h"

#define W 800
#define H 600


int main(int argc, char** argv)
{
	Window window(W, H, "OpenGL");
	Input input(window);

	Shader shader("../assets/shaders/shader.vert", "../assets/shaders/shader.frag");
	mesh_t a = az_mesh_load_aps1(argv[1]);
	//mesh_t b = az_mesh_load_aps1(argv[1]);
	a.texture = az_texture_farbfeld_load("../assets/textures/default.ff");
	Camera cam(input, float(W)/H);
	
	float angle = 0.f;
	
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	Scene scene;
	scene.AddMesh(&a);
	//scene.AddMesh(&b);
	Renderer renderer = Renderer();

	while(!window.ShouldClose())
	{
		a.transform.model = glm::translate(glm::vec3(0,0,5)) * glm::rotate(glm::radians(angle),glm::vec3(0,1,0));
		//b.transform.model = glm::translate(glm::vec3(15,0,0));
		angle += 0.05f;
		cam.Update();
		window.Update();
		window.Clear();
		
		renderer.DrawScene(scene,shader,cam);
		
		window.SwapBuffers();		
	}	
	return 0;
}