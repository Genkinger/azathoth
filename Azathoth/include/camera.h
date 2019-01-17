/**
 * @file camera.h
 * @author Lukas Genkinger (genkinger@protonmail.com)
 * @brief camera representation
 * @version 1.0
 * @date 2018-12-31
 * 
 * @copyright Copyright (c) 2018, Lukas Genkinger
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND,
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED,
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE,
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR,
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES,
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;,
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND,
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT,
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS,
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation are those,
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the Azathoth project.
 * 
 */
#pragma once
#include "input.h"
#include <glm/gtx/transform.hpp>



struct Camera
{
        
        glm::mat4 view;
        glm::mat4 projection;

        float pitch = 0; 
        float yaw = 0;
        float roll = 0;

        glm::vec3 up = glm::vec3(0.f,1.f,0.f);
        glm::vec3 world_up = glm::vec3(0.f,1.f,0.f);
        glm::vec3 right = glm::vec3(1.f,0.f,0.f);
        glm::vec3 direction = glm::vec3(0.f,0.f,-1.f);

        glm::vec3 position = glm::vec3(0.f,5.f,0.f);

        float fovy = 80.f;
        float near = 1.f;
        float far = 5000.f;

        float factor = 0.005f;
        float speed = 5.f;

        Camera(Input& input, float aspect);
        void Update();

    private:
        Input &m_Input;
};