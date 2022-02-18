#include <glimac/SDLWindowManager.hpp>
#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
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

const char* vertexShaderSource = 
    "#version 330\n"
    "layout(location = 0) in vec2 aVertexPosition;"
    "layout(location = 1) in vec3 aVertexColor;"
    "out vec3 vFragColor;"
    "void main() {"
        "vFragColor = aVertexColor;"
        "gl_Position = vec4(aVertexPosition, 0,1);"
    "}";
 
const char* fragmentShaderSource =    
    "#version 330\n"
    "in vec3 vFragColor;"
    "out vec3 fFragColor;"
    "void main(){"
        "fFragColor = vFragColor;"
    "}";
    
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
    Program program = loadProgram(applicationPath.dirPath() + "shaders/color2D.vs.glsl",
                                  applicationPath.dirPath() + "shaders/color2D.fs.glsl");
    //Program program = loadProgram(vertexShaderSource,fragmentShaderSource);
    program.use();

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    //GLfloat vertices[] = { -0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f };
    //GLfloat vertices[] = { -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f , 0.0f, 0.5f, 0.0f, 0.0f, 1.0f };
   Vertex2DColor vertices[] = {
        Vertex2DColor(glm::vec2(-0.5f, -0.5f),glm::vec3(1, 0, 0)),
        Vertex2DColor(glm::vec2( 0.5f, -0.5f),glm::vec3(1, 1, 0)),
        Vertex2DColor(glm::vec2( 0.0f, 0.5f ),glm::vec3(0, 0, 1)),
        Vertex2DColor(glm::vec2( -0.5f, 0.5f),glm::vec3(1, 1, 1)),
    };
    
    //glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex2DColor), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    
    uint32_t indices[] = { 0,1,2,0,2,3};
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR= 1;  
    
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
    
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), offsetof(Vertex2DColor,aVertexPosition));
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*)  offsetof(Vertex2DColor,aVertexColor));
    
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
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao);

        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
        /*********************************/

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
