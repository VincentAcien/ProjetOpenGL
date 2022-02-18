#pragma once

#define _USE_MATH_DEFINES

#include <vector>
#include <cmath>

#include "common.hpp"

namespace glimac {

class FreeflyCamera {

    void build(GLfloat radius, GLsizei discLat, GLsizei discLong);

public:

    FreeflyCamera(){
    	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
      	m_fPhi = M_PI;
    	m_fTheta = 0;
    	computeDirectionVectors();
    }
    
    void moveLeft(float t){
    	m_Position += t * m_LeftVector;
    }
    
    void moveFront(float t){
    	m_Position += t * m_FrontVector;
    }
    
    void rotateLeft(float degrees){
    	m_fPhi += 2 * M_PI * (degrees / 360);
    }
    
    void rotateUp(float degrees){
    	m_fTheta += 2 * M_PI * (degrees / 360);
    }

private:
    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;
    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;
    
    void computeDirectionVectors(){
    	m_FrontVector = glm::vec3(cos(m_fTheta) * sin(m_fPhi), sin(m_fTheta), cos(m_fTheta) * sin(m_fPhi));
    	m_LeftVector = glm::vec3(sin(m_fPhi + M_PI_2), 0, cos(m_fPhi + M_PI_2));
    	m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
    }
    
    glm::mat4 getViewMatrix() const{
    	return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
    }
};
    
}
