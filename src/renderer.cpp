#include "renderer.h"



void Renderer::DrawScene(Scene &scene, Shader &shader, Camera& camera)
{
    shader.Bind();
    shader.UniformMat4("View",camera.view);
    shader.UniformMat4("Projection",camera.projection);
    for(model_t *model : scene.models)
    {
        for(int i = 0; i < model->num_meshes; i++){
            mesh_t *m = &model->meshes[i];
            m->vao.Bind();
            shader.UniformMat4("Model",m->transform.model);
            shader.UniformInt("texture_sampler",0);
            shader.UniformMat4("Normal",glm::transpose(glm::inverse(m->transform.model)));
            GLCall(glActiveTexture(GL_TEXTURE0));
            GLCall(glBindTexture(GL_TEXTURE_2D,m->material.map_kd.id));
            GLCall(glDrawArrays(GL_TRIANGLES,0,m->count));
        }
    }
}