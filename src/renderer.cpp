#include "renderer.h"


Renderer::Renderer(int width, int height)
{  
    this->width = width;
    this->height = height;

    InitGBuffer(width, height);
    InitQuad();
}

void Renderer::DrawSceneForward(Scene &scene, Camera& camera)
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    forward->Bind();
    forward->UniformMat4("ViewMatrix",camera.view);
    forward->UniformMat4("ProjectionMatrix",camera.projection);
    glClear(GL_COLOR_BUFFER_BIT  |  GL_DEPTH_BUFFER_BIT);
    for(model_t *model : scene.models)
    {
        for(int i = 0; i < model->num_meshes; i++)
        {
            glm::mat4 modelMatrix = model->transform.model * model->meshes[i]->transform.model;
            forward->UniformMat4("ModelMatrix", modelMatrix);
            forward->UniformMat4("NormalMatrix",glm::transpose(glm::inverse(modelMatrix)));
            forward->UniformInt("diffuse_texture",0);
            forward->UniformInt("ambient_texture",1);
            forward->UniformVec3("lightPosition",glm::vec3(0,50,0));
            forward->UniformVec3("cameraPosition",camera.position);
            glBindVertexArray(model->meshes[i]->vao);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D,model->meshes[i]->material.map_kd.id);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D,model->meshes[i]->material.map_ka.id);

            glDrawArrays(GL_TRIANGLES,0,model->meshes[i]->count);
        }        
    }
}

void Renderer::DrawSceneDeferred(Scene &scene, Camera& camera)
{
   
    GeometryPass(scene,camera);
    LightPass(scene,camera);
   // DebugLightPass(scene,camera);

}

void Renderer::GeometryPass(Scene& scene, Camera& camera)
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,gBuffer);

    geometry->Bind();
    geometry->UniformMat4("ViewMatrix",camera.view);
    geometry->UniformMat4("ProjectionMatrix",camera.projection);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(model_t *model : scene.models)
    {
        for(int i = 0; i < model->num_meshes; i++)
        {
            glm::mat4 modelMatrix = model->transform.model * model->meshes[i]->transform.model;
            geometry->UniformMat4("ModelMatrix", modelMatrix);
            geometry->UniformMat4("NormalMatrix",glm::transpose(glm::inverse(modelMatrix)));
            geometry->UniformInt("diffuse_texture",0);
            glBindVertexArray(model->meshes[i]->vao);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D,model->meshes[i]->material.map_kd.id);
            glDrawArrays(GL_TRIANGLES,0,model->meshes[i]->count);
        }        
    }
}
void Renderer::LightPass(Scene& scene, Camera& camera)
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindFramebuffer(GL_READ_FRAMEBUFFER,gBuffer);
    
    lighting->Bind();
    lighting->UniformInt("color_texture",0);
    lighting->UniformInt("position_texture",3);
    lighting->UniformInt("st_texture",1);
    lighting->UniformInt("normal_texture",2);
    
    for (int i = 0; i < 4; i++){
        glActiveTexture(GL_TEXTURE0+i);
        glBindTexture(GL_TEXTURE_2D,textures[i]);
    }
    DrawFullscreenQuad();

}
void Renderer::DebugLightPass(Scene& scene, Camera& camera)
{

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindFramebuffer(GL_READ_FRAMEBUFFER,gBuffer);

    GLsizei HalfWidth = (GLsizei)(width / 2.0f);
    GLsizei HalfHeight = (GLsizei)(height / 2.0f);

    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glBlitFramebuffer(0, 0, width, height,
                    0, 0, HalfWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    glReadBuffer(GL_COLOR_ATTACHMENT1);
    glBlitFramebuffer(0, 0, width, height,
                    0, HalfHeight, HalfWidth, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    glReadBuffer(GL_COLOR_ATTACHMENT2);
    glBlitFramebuffer(0, 0, width, height,
                    HalfWidth, HalfHeight, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    glReadBuffer(GL_COLOR_ATTACHMENT3);
    glBlitFramebuffer(0, 0, width, height,
                    HalfWidth, 0, width, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR); 

}

void Renderer::DrawFullscreenQuad()
{
    GLCall(glDisable(GL_CULL_FACE));
    GLCall(glBindVertexArray(quad_vao));
    GLCall(glDrawArrays(GL_TRIANGLE_FAN,0,4));
}

void Renderer::InitQuad(){

    const static float data[] = {
        -1,-1,0,-1,-1,
        -1,1,0,-1,1,
        1,1,0,1,1,
        1,-1,0,1,-1
    };

    GLCall(glGenBuffers(1,&quad_vbo));
    GLCall(glGenVertexArrays(1,&quad_vao));

    GLCall(glBindVertexArray(quad_vao));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER,quad_vbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER,sizeof(data),data,GL_STATIC_DRAW));
    
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glEnableVertexAttribArray(1));
    
    int stride = (3+2) * sizeof(float);
    GLCall(glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,stride,0));
    GLCall(glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,stride,(void*)(sizeof(float)*3)));
}

void Renderer::InitGBuffer(int width, int height){
    
    GLCall(glGenFramebuffers(1,&gBuffer));
    GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gBuffer));

    GLCall(glGenTextures(4,textures));
    GLCall(glGenTextures(1,&depth_texture));

    for( int i = 0; i < 4; i++){
        GLCall(glBindTexture(GL_TEXTURE_2D,textures[i]));
        GLCall(glTexImage2D(GL_TEXTURE_2D,0,GL_RGB32F,width,height,0,GL_RGB,GL_FLOAT,NULL));
        GLCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST));
        GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D,textures[i],0));
    }

    GLCall(glBindTexture(GL_TEXTURE_2D,depth_texture));
    GLCall(glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT32F,width,height,0,GL_DEPTH_COMPONENT,GL_FLOAT,0));
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture, 0);

    attachments[0] = GL_COLOR_ATTACHMENT0;
    attachments[1] = GL_COLOR_ATTACHMENT1;
    attachments[2] = GL_COLOR_ATTACHMENT2;
    attachments[3] = GL_COLOR_ATTACHMENT3;

    GLCall(glDrawBuffers(4,attachments)); 
    GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0));

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE) {
        printf("FB error, status: 0x%x\n", Status);
    }
}