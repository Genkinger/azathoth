#include "renderer.h"



void Renderer::DrawScene(Scene &scene, Shader &shader, Camera& camera)
{
    shader.Bind();
    shader.UniformMat4("View",camera.view);
    shader.UniformMat4("Projection",camera.projection);
    for(model_t *model : scene.models)
    {
        for(int i = 0; i < model->num_meshes; i++){
            mesh_t *m = model->meshes[i];
            GLCall(glBindVertexArray(m->vao));
            shader.UniformMat4("Model",m->transform.model);
            shader.UniformInt("diffuse",0);
            shader.UniformInt("ambient",1);
            shader.UniformInt("specular",2);
            shader.UniformInt("bump",3);
            shader.UniformMat4("MVP",camera.projection * camera.view * m->transform.model);
            
            shader.UniformMat4("Normal",glm::transpose(glm::inverse(m->transform.model)));
            
            GLCall(glActiveTexture(GL_TEXTURE0+m->material.map_kd.index));
            GLCall(glBindTexture(GL_TEXTURE_2D,m->material.map_kd.id));

            GLCall(glActiveTexture(GL_TEXTURE0+m->material.map_ka.index));
            GLCall(glBindTexture(GL_TEXTURE_2D,m->material.map_ka.id));
            
            GLCall(glDrawArrays(GL_TRIANGLES,0,m->count));
        }
    }
}