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
#define W 800
#define H 600


int main(int argc, char** argv)
{
	Window window(W, H, "OpenGL");
	Input input(window);

	Shader shader("../assets/shaders/shader.vert", "../assets/shaders/shader.frag");
	Mesh a(argv[1]);
	Camera cam(input, float(W)/H);
	
	float angle = 0.f;
	
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	while(!window.ShouldClose())
	{
		//a.GetTransform().model = glm::rotate(glm::radians(angle),glm::vec3(0,1,0));
		angle += 0.4f;
		cam.Update();
		window.Update();
		window.Clear();
		//printf("onclick: %f %f | onrelease: %f %f | scroll: %f %f\n",input.LastLeftDown.x,input.LastLeftDown.y,input.LastLeftUp.x,input.LastLeftUp.y,input.Scroll.x,input.Scroll.y);
		
		shader.Bind();
		shader.UniformMat4("Model", a.GetTransform().model);
		shader.UniformMat4("View", cam.view);
		shader.UniformMat4("Projection", cam.projection);
		
		a.Bind();
		GLCall(glDrawArrays(GL_TRIANGLES,0,a.Count()));
		
		shader.Unbind();
		
		window.SwapBuffers();		
	}	
	return 0;
}