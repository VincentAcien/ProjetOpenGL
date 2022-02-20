#include <glimac/SDLWindowManager.hpp>
#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/common.hpp>
#include <glimac/Image.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/Sphere.hpp>
#include <cstddef>
#include <GL/glew.h>
#include <iostream>
#include <math.h>
#include <filesystem>

using namespace glimac;
//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

/*
struct ShapeVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};
*/

class Parallelepipede{
    public:
       float largeur;
       float hauteur;
       float profondeur;
       
       Parallelepipede(float pLargeur,float pHauteur,float pProfondeur){
           largeur = pLargeur;
           hauteur = pHauteur;
           profondeur = pProfondeur;
       }
       
       GLint VertexCount(){
           return 3;
       }

};

    
int main(int argc, char** argv) {
 
     //Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                                  applicationPath.dirPath() + "shaders/directionallights.fs.glsl");
    //Program program = loadProgram(vertexShaderSource,fragmentShaderSource);
    program.use();
    
    
    
    
    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    
    /////////// TEXTURE INITIALISATION /////////////
       //std::unique_ptr<Image>  pImage = loadImage(applicationPath.dirPath() + "image/triforce.png");
       std::unique_ptr<Image>  pImage = loadImage(applicationPath.dirPath() + "image/EarthMap.jpg");
    
    GLuint texture;
    glGenTextures(1,&texture);
    glBindTexture( GL_TEXTURE_2D,texture);
    glTexImage2D( GL_TEXTURE_2D,0,GL_RGBA,pImage->getWidth(),pImage->getHeight(),0,GL_RGBA,GL_FLOAT,pImage->getPixels() );
  	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture( GL_TEXTURE_2D,0);
    
    GLint uTexture_id = glGetUniformLocation(program.getGLId(),"uTexture");
    
        
    ///////////// 3D INITIALISATION /////////////
    
     
    GLint uMVPMatrix_id = glGetUniformLocation(program.getGLId(),"uMVPMatrix");
    GLint uMVMatrix_id = glGetUniformLocation(program.getGLId(),"uMVMatrix");
    GLint uNormalMatrix_id = glGetUniformLocation(program.getGLId(),"uNormalMatrix");
    
    GLint uKd_id = glGetUniformLocation(program.getGLId(),"uKd");
    GLint uKs_id = glGetUniformLocation(program.getGLId(),"uKs");
    GLint uShininess_id = glGetUniformLocation(program.getGLId(),"uShininess");
    GLint uLightDir_vs_id = glGetUniformLocation(program.getGLId(),"uLightDir_vs");
    GLint uLightIntensity_id = glGetUniformLocation(program.getGLId(),"uLightIntensity");
    
    glEnable(GL_DEPTH_TEST);
    
    glm::mat4 ProjMatrix, MVMatrix, NormalMatrix, MMatrix, ViewMatrix;
    ProjMatrix = glm::perspective(glm::radians(70.0f),4.0f/3.0f, 0.1f, 100.0f);
    MMatrix = glm::translate(MMatrix,glm::vec3(0,0,-5));
    MVMatrix = ViewMatrix * MMatrix;
    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    glm::vec3 LightDir = glm::vec3(-1.0f,-1.0f,-1.0f);
    
    
    ///////////// VERTEX INITIALISATION /////////////
    
   
   ShapeVertex vertex00,vertex01,vertex02,vertex03,
   		vertex10,vertex11,vertex12,vertex13,
   		vertex20,vertex21,vertex22,vertex23,
   		vertex30,vertex31,vertex32,vertex33,
   		vertex40,vertex41,vertex42,vertex43,
   		vertex50,vertex51,vertex52,vertex53;
   vertex00.position = glm::vec3(-1.0f, -1.0f, 1.0f);
   vertex00.normal = glm::vec3(0.0f, 0.0f, -1.0f);
   vertex00.texCoords = glm::vec2(0,0);
   
   vertex01.position = glm::vec3(-1.0f, 1.0f, 1.0f);
   vertex01.normal = glm::vec3(0.0f, 0.0f, -1.0f);
   vertex01.texCoords = glm::vec2(0,0);
   
   vertex02.position = glm::vec3(1.0f, 1.0f , 1.0f);
   vertex02.normal = glm::vec3(0.0f, 0.0f, -1.0f);
   vertex02.texCoords = glm::vec2(0,0);
   
   vertex03.position = glm::vec3(1.0f, -1.0f , 1.0f);
   vertex03.normal = glm::vec3(0.0f, 0.0f, -1.0f);
   vertex03.texCoords = glm::vec2(0,0);
   
   
   
   vertex10.position = glm::vec3(-1.0f, -1.0f, -1.0f);
   vertex10.normal = glm::vec3(0.0f, 0.0f, 1.0f);
   vertex10.texCoords = glm::vec2(0,0);
   
   vertex11.position = glm::vec3(-1.0f, 1.0f, -1.0f);
   vertex11.normal = glm::vec3(0.0f, 0.0f, 1.0f);
   vertex11.texCoords = glm::vec2(0, 0);
   
   vertex12.position = glm::vec3(1.0f, 1.0f , -1.0f);
   vertex12.normal = glm::vec3(0.0f, 0.0f, 1.0f);
   vertex12.texCoords = glm::vec2(0,0);
   
   vertex13.position = glm::vec3(1.0f, -1.0f , -1.0f);
   vertex13.normal = glm::vec3(0.0f, 0.0f, 1.0f);
   vertex13.texCoords = glm::vec2(0,0);
   
   
   
   vertex20.position = glm::vec3(-1.0f, -1.0f, -1.0f);
   vertex20.normal = glm::vec3(1.0f, 0.0f, 0.0f);
   vertex20.texCoords = glm::vec2(0,0);
   
   vertex21.position = glm::vec3(-1.0f, 1.0f, -1.0f);
   vertex21.normal = glm::vec3(1.0f, 0.0f, 0.0f);
   vertex21.texCoords =glm::vec2(0,0);
   
   vertex22.position = glm::vec3(-1.0f, 1.0f , 1.0f);
   vertex22.normal = glm::vec3(1.0f, 0.0f, 0.0f);
   vertex22.texCoords = glm::vec2(0,0);
   
   vertex23.position = glm::vec3(-1.0f, -1.0f , 1.0f);
   vertex23.normal = glm::vec3(1.0f, 0.0f, 0.0f);
   vertex23.texCoords = glm::vec2(0,0);
   
   
   
   vertex30.position = glm::vec3(1.0f, -1.0f, -1.0f);
   vertex30.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
   vertex30.texCoords = glm::vec2(0,0);
   
   vertex31.position = glm::vec3(1.0f, 1.0f, -1.0f);
   vertex31.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
   vertex31.texCoords = glm::vec2(0,0);
   
   vertex32.position = glm::vec3(1.0f, 1.0f , 1.0f);
   vertex32.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
   vertex32.texCoords = glm::vec2(0,0);
   
   vertex33.position = glm::vec3(1.0f, -1.0f , 1.0f);
   vertex33.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
   vertex33.texCoords = glm::vec2(0,0);
   
   
   
   vertex40.position = glm::vec3(-1.0f, -1.0f, -1.0f);
   vertex40.normal = glm::vec3(0.0f, 1.0f, 0.0f);
   vertex40.texCoords = glm::vec2(0,0);
   
   vertex41.position = glm::vec3(-1.0f, -1.0f, 1.0f);
   vertex41.normal = glm::vec3(0.0f, 1.0f, 0.0f);
   vertex41.texCoords = glm::vec2(0,0);
   
   vertex42.position = glm::vec3(1.0f, -1.0f , 1.0f);
   vertex42.normal = glm::vec3(0.0f, 1.0f, 0.0f);
   vertex42.texCoords = glm::vec2(0,0);
   
   vertex43.position = glm::vec3(1.0f, -1.0f , -1.0f);
   vertex43.normal = glm::vec3(0.0f, 1.0f, 0.0f);
   vertex43.texCoords = glm::vec2(0,0);
   
   
   
   vertex50.position = glm::vec3(-1.0f, 1.0f, -1.0f);
   vertex50.normal = glm::vec3(0.0f, -1.0f, 0.0f);
   vertex50.texCoords = glm::vec2(0,0);
   
   vertex51.position = glm::vec3(-1.0f, 1.0f, 1.0f);
   vertex51.normal = glm::vec3(0.0f, -1.0f, 0.0f);
   vertex51.texCoords =glm::vec2(0,0);
   
   vertex52.position = glm::vec3(1.0f, 1.0f , 1.0f);
   vertex52.normal = glm::vec3(0.0f, -1.0f, 0.0f);
   vertex52.texCoords = glm::vec2(0,0);
   
   vertex53.position = glm::vec3(1.0f, 1.0f , -1.0f);
   vertex53.normal = glm::vec3(0.0f, -1.0f, 0.0f);
   vertex53.texCoords = glm::vec2(0,0);
   
   ShapeVertex vertices[] = {	vertex00,vertex01,vertex02,vertex03,
   				vertex10,vertex11,vertex12,vertex13,
   				vertex20,vertex21,vertex22,vertex23,
   				vertex30,vertex31,vertex32,vertex33,
   				vertex40,vertex41,vertex42,vertex43,
   				vertex50,vertex51,vertex52,vertex53
        
        //ShapeVertex(glm::vec3( -0.5f, 0.5f, 0.0f),glm::vec3(-0.5f, -0.5f, 0.0f),glm::vec3(1, 1, 1)),
    };
    
    
    Sphere sphere = Sphere(1,32,16);
    
     ///////////// VBO INITIALISATION /////////////
    
    GLuint vbo1,vbo2;
    glGenBuffers(1, &vbo1);
    glGenBuffers(1, &vbo2);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(ShapeVertex), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount() * sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    
    ///////////// IBO INITIALISATION /////////////
    
    
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    
    uint32_t indices[] = { 	0,2,1 , 	0,2,3,
    				4,6,5 , 	4,6,7,
    				8,10,9 , 	8,10,11,
    				12,14,13 , 	12,14,15,
    				16,18,17, 	16,18,19,
    				20,22,21 , 	20,22,23};
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    

    ///////////// VAO INITIALISATION /////////////

    GLuint vao1,vao2;
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL= 1;  
    const GLuint VERTEX_ATTR_TEXCOORDS= 2; 
    
    glGenVertexArrays(1, &vao1);
    glBindVertexArray(vao1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
    
    glBindBuffer(GL_ARRAY_BUFFER,vbo1);
        
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), offsetof(ShapeVertex,position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)  offsetof(ShapeVertex,normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)  offsetof(ShapeVertex,texCoords));
    
    
    
    glGenVertexArrays(1, &vao2);
    glBindVertexArray(vao2);
    
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
    
    glBindBuffer(GL_ARRAY_BUFFER,vbo2);
        
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), offsetof(ShapeVertex,position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)  offsetof(ShapeVertex,normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)  offsetof(ShapeVertex,texCoords));
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    
    /*glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat),0);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, 5* sizeof(GLfloat),0);
    
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (const GLvoid*) (2 * sizeof(GLfloat)));*/
    
    ///////////// FREE CAMERA /////////////
    
    FreeflyCamera camera = FreeflyCamera();
 
    /****************************************************************************************/
    
    
    ///////////// APPLICATION LOOP /////////////
    //glm::vec2 middle = glm::vec2(400.0f,300.0f);

    bool done = false;
    while(!done) {
    	ViewMatrix = camera.getViewMatrix();
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_KEYDOWN){
        	//std::cout << "key pressed\n";
        		if (windowManager.isKeyPressed(SDLK_z)){
        			camera.moveFront(0.5);
        			ViewMatrix = camera.getViewMatrix();
        			//NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        			//ProjMatrix = glm::translate(ProjMatrix, glm::vec3(0, 0, 0.1f));
        			}
        		if (windowManager.isKeyPressed(SDLK_s)){
        			camera.moveFront(-0.5);
        			ViewMatrix = camera.getViewMatrix();
        			//NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        		}
        		if (windowManager.isKeyPressed(SDLK_q)){
        			camera.moveLeft(0.5);
        			ViewMatrix = camera.getViewMatrix();
        		}
        		if (windowManager.isKeyPressed(SDLK_d)){
        			camera.moveLeft(-0.5);
        			ViewMatrix = camera.getViewMatrix();
        		}
        		if (windowManager.isKeyPressed(SDLK_SPACE)){
        			std::cout << "light dir" << LightDir;
        		}
        		
        		
        	}
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }
        
        glm::vec2 mousePos = windowManager.getMousePosition();
        camera.rotateLeft((400-mousePos.x)/(500*4.44f));
        camera.rotateUp((300-mousePos.y)/(500*3.33f));
        ViewMatrix = camera.getViewMatrix();
	MVMatrix = ViewMatrix * MMatrix;

    /*********************************
    * HERE SHOULD COME THE RENDERING CODE
    *********************************/
        
       
        
         
        //glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //MVMatrix = glm::rotate(MVMatrix, 0.0005f, glm::vec3(0, 2, 0));
        //LightDir = glm::rotate(LightDir, 0.0005f, glm::vec3(0, 2, 0));
        //ProjMatrix = glm::translate(ProjMatrix, glm::vec3(0.003f, 0, 0.0f));//MVMatrix = glm::translate(MVMatrix, glm::vec3(-2, 0, 0));
        //MVMatrix = glm::rotate(MVMatrix, 0.001f, glm::vec3(0, 2, 0)); //Translation * Rotation
	 //MVMatrix = glm::translate(MVMatrix, glm::vec3(0, 0.001f, 0));//MVMatrix = glm::translate(MVMatrix, glm::vec3(-2, 0, 0)); // Translation * Rotation * Translation
	
        
        
        
        
        glUniform3f(uKd_id,1.0f,1.0f,1.0f);
        glUniform3f(uKs_id,0.2f,0.2f,0.2f);
        glUniform1f(uShininess_id,0.2f);
        //LightDir = ViewMatrix*LightDir;
        glUniform3f(uLightDir_vs_id,-LightDir.x,-LightDir.y,-LightDir.z);
        glUniform3f(uLightIntensity_id,0.5f,0.5f,0.5f);
        
        MVMatrix = glm::scale(MVMatrix, glm::vec3(20.0, 20.0, 20.0));
        
        glUniformMatrix4fv(uMVPMatrix_id,1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix_id,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix_id,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        
        
        
        glBindVertexArray(vao1);
        
        //glBindTexture( GL_TEXTURE_2D,texture);
        glUniform1i(uTexture_id,0);
        
        glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
        glBindTexture( GL_TEXTURE_2D,0);
        
        
        MVMatrix = glm::scale(MVMatrix, glm::vec3(0.05, 0.05, 0.05));
        //MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0));
        glUniformMatrix4fv(uMVPMatrix_id,1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix_id,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix_id,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glBindVertexArray(vao2);
        
        glBindTexture( GL_TEXTURE_2D,texture);
        glUniform1i(uTexture_id,0);
        
        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
        glBindTexture( GL_TEXTURE_2D,0);
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        /**
        glUniform3f(uKd_id,1.0f,1.0f,1.0f);
        glUniform3f(uKs_id,0.2f,0.2f,0.2f);
        glUniform1f(uShininess_id,0.2f);
        glUniform3f(uLightDir_vs_id,LightDir.x,LightDir.y,LightDir.z);
        glUniform3f(uLightIntensity_id,0.0f,1.0f,0.0f);
        
        glUniformMatrix4fv(uMVPMatrix_id,1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix_id,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix_id,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        
        glBindVertexArray(vao1);
        
        glBindTexture( GL_TEXTURE_2D,texture);
        glUniform1i(uTexture_id,0);
        
        glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
        //glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
        glBindTexture( GL_TEXTURE_2D,0);
        **/
	
         
         
         
         
         
         
         
         
        
        //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);*/
        glBindVertexArray(0);
        
        /*********************************/

        // Update the display
        windowManager.swapBuffers();
    }

    ///////////// DEALOCATIONS /////////////

    //glDeleteTextures(1,&texture);
    glDeleteBuffers(1, &vbo1);
    glDeleteVertexArrays(1, &vao1);
    glDeleteBuffers(1, &vbo2);
    glDeleteVertexArrays(1, &vao2);
    glDeleteBuffers(1, &ibo);

    return EXIT_SUCCESS;
}
