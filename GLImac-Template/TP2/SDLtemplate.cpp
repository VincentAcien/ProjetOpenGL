#include <glimac/SDLWindowManager.hpp>
#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/common.hpp>
#include <glimac/Image.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <cstddef>
#include <GL/glew.h>
#include <iostream>
#include <math.h>
#include <filesystem>

using namespace glimac;


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
       std::unique_ptr<Image>  pImage = loadImage(applicationPath.dirPath() + "image/triforce.png");
    
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
    glm::vec3 LightDir = glm::vec3(0.0f,0.0f,1.0f);
    
    
    ///////////// VERTEX INITIALISATION /////////////
    
    
    //GLfloat vertices[] = { -0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f };
    //GLfloat vertices[] = { -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f , 0.0f, 0.5f, 0.0f, 0.0f, 1.0f };
   ShapeVertex vertex0,vertex1,vertex2,vertex3,vertex4,vertex5,vertex6,vertex7;
   vertex0.position = glm::vec3(-1.0f, 1.0f, 1.0f);
   vertex0.normal = glm::vec3(0.0f, 0.0f, 1.0f);
   vertex0.texCoords = glm::vec2(0, 1);
   
   vertex1.position = glm::vec3(1.0f, -1.0f, 1.0f);
   vertex1.normal = glm::vec3(0.0f, 0.0f, 1.0f);
   vertex1.texCoords = glm::vec2(1, 1);
   
   vertex2.position = glm::vec3(1.0f, 1.0f , 1.0f);
   vertex2.normal = glm::vec3(0.0f, 0.0f, 1.0f);
   vertex2.texCoords = glm::vec2(0.5f, 0);
   
   vertex3.position = glm::vec3(-1.0f, -1.0f , 1.0f);
   vertex3.normal = glm::vec3(0.0f, 0.0f, 1.0f);
   vertex3.texCoords = glm::vec2(0.5f, 0);
   
   vertex4.position = glm::vec3(-1.0f, 1.0f, -1.0f);
   vertex4.normal = glm::vec3(0.0f, 0.0f, -1.0f);
   vertex4.texCoords = glm::vec2(1, 1);
   
   vertex5.position = glm::vec3(1.0f, -1.0f, -1.0f);
   vertex5.normal = glm::vec3(0.0f, 0.0f, -1.0f);
   vertex5.texCoords = glm::vec2(1, 1);
   
   vertex6.position = glm::vec3(1.0f, 1.0f , -1.0f);
   vertex6.normal = glm::vec3(0.0f, 0.0f, -1.0f);
   vertex6.texCoords = glm::vec2(0, 1);
   
   vertex7.position = glm::vec3(-1.0f, -1.0f , -1.0f);
   vertex7.normal = glm::vec3(0.0f, 0.0f, -1.0f);
   vertex7.texCoords = glm::vec2(1, 1);
   
   ShapeVertex vertices[] = {vertex0,vertex1,vertex2,vertex3,vertex4,vertex5,vertex6,vertex7
        
        //ShapeVertex(glm::vec3( -0.5f, 0.5f, 0.0f),glm::vec3(-0.5f, -0.5f, 0.0f),glm::vec3(1, 1, 1)),
    };
    
    
     ///////////// VBO INITIALISATION /////////////
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(ShapeVertex), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    
    ///////////// IBO INITIALISATION /////////////
    
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    
    uint32_t indices[] = { 2,5,6, 0,1,2, 0,1,3, 4,5,6, 4,5,7, 0,4,3, 7,4,3, 0,4,2, 6,4,2, 2,5,1,  7,1,3, 7,1,5};
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);


    ///////////// VAO INITIALISATION /////////////

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL= 1;  
    const GLuint VERTEX_ATTR_TEXCOORDS= 2; 
    
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
    
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
        
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
        camera.rotateLeft((400-mousePos.x)/(2000*4.44f));
        camera.rotateUp((300-mousePos.y)/(2000*3.33f));
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
	//MVMatrix = glm::scale(glm::mat4x4(1), glm::vec3(1.0f, 1.0f, 1.0f));
        
        
        
        
        glUniform3f(uKd_id,2.0f,2.0f,2.0f);
        glUniform3f(uKs_id,0.0f,0.0f,0.0f);
        glUniform1f(uShininess_id,1.0f);
        //LightDir = ViewMatrix*LightDir;
        glUniform3f(uLightDir_vs_id,LightDir.x,LightDir.y,LightDir.z);
        glUniform3f(uLightIntensity_id,1.0f,0.0f,0.0f);
        
        glUniformMatrix4fv(uMVPMatrix_id,1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix_id,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix_id,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        glBindVertexArray(vao);
        
        glBindTexture( GL_TEXTURE_2D,texture);
        glUniform1i(uTexture_id,0);
        
        
        
        glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
        
        glBindTexture( GL_TEXTURE_2D,0);
	
         
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);*/
        glBindVertexArray(0);
        
        /*********************************/

        // Update the display
        windowManager.swapBuffers();
    }

    ///////////// DEALOCATIONS /////////////

    //glDeleteTextures(1,&texture);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
