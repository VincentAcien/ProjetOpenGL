#pragma once

#define _USE_MATH_DEFINES

#include <vector>
#include <cmath>
#include <iostream>
#include "common.hpp"

namespace glimac {

class FreeflyCamera {

public:

    FreeflyCamera(){
    	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
      	m_fPhi = M_PI;
    	m_fTheta = 0;
    	computeDirectionVectors();
    }
    
    void moveLeft(float t){
    	m_Position += t * m_LeftVector;
    	computeDirectionVectors();
    }
    
    void moveFront(float t){
    	m_Position += t * m_FrontVector;
    	computeDirectionVectors();
        //std::cout<<m_Position.x;
    	
    }
    
    void rotateLeft(float degrees){
    	m_fPhi += 2 * M_PI * (degrees / 360);
    	computeDirectionVectors();
    }
    
    void rotateUp(float degrees){
    	m_fTheta += 2 * M_PI * (degrees / 360);
    	computeDirectionVectors();
    }
    
    glm::mat4 getViewMatrix() const{
    	return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
    }

private:
    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;
    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;
    
    void computeDirectionVectors(){
    	m_FrontVector = glm::vec3(cos(m_fTheta) * sin(m_fPhi), sin(m_fTheta), cos(m_fTheta) * cos(m_fPhi));
    	m_LeftVector = glm::vec3(sin(m_fPhi + M_PI_2), 0, cos(m_fPhi + M_PI_2));
    	m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
    }
    
    
};
    
}
