#include <glimac/SDLWindowManager.hpp>
#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/Sphere.hpp>
#include <cstddef>
#include <GL/glew.h>
#include <iostream>

using namespace glimac;

class Vertex2DColor{
    public:
        glm::vec2 aVertexPosition;
        glm::vec3 aVertexColor;
    
    
        Vertex2DColor(glm::vec2 pPosition, glm::vec3 pColor){
            aVertexPosition = pPosition;
            aVertexColor = pColor;
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
                                  applicationPath.dirPath() + "shaders/normals.fs.glsl");
    //Program program = loadProgram(vertexShaderSource,fragmentShaderSource);
    program.use();
    
    GLint uMVPMatrix_id = glGetUniformLocation(program.getGLId(),"uMVPMatrix");
    GLint uMVMatrix_id = glGetUniformLocation(program.getGLId(),"uMVMatrix");
    GLint uNormalMatrix_id = glGetUniformLocation(program.getGLId(),"uNormalMatrix");
    
    glEnable(GL_DEPTH_TEST);
    
    glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;
    ProjMatrix = glm::perspective(glm::radians(70.0f),4.0f/3.0f, 0.1f, 100.0f);
    MVMatrix = glm::translate(MVMatrix,glm::vec3(0,0,-5));
    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    Sphere sphere = Sphere(1, 32, 16);
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    
    glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount() * sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    
    /*GLuint ibo;
    glGenBuffers(getVertexCount(), &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    
    uint32_t indices[] = { 0,1,2,0,2,3};
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);*/

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

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
    
    //glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat),0);
    //glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, 5* sizeof(GLfloat),0);
    
    //glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (const GLvoid*) (2 * sizeof(GLfloat)));
 
    /*********************************/

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        //glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniformMatrix4fv(uMVPMatrix_id,1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix_id,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix_id,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
        
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1), glm::vec3(-2, 0, -5)); // Translation
	//MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0)); //Translation * Rotation
	//MVMatrix = glm::translate(MVMatrix, glm::vec3(-2, 0, 0)); // Translation * Rotation * Translation
	//MVMatrix = glm::scale(MVMatrix, glm::vec3(0.2, 0.2, 0.2)); // Translation * Rotation * Translation * Scale
	
	glUniformMatrix4fv(uMVPMatrix_id,1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix_id,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix_id,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        glBindVertexArray(vao);
        
        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
        //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
        /*********************************/

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
