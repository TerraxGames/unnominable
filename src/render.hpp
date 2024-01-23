#ifndef __PROJECTS_TERRAXGAMES_UNNOMINABLE_SRC_RENDER_HPP_
#define __PROJECTS_TERRAXGAMES_UNNOMINABLE_SRC_RENDER_HPP_

struct GLVars {
    GLuint vao;
    GLuint vbo;
    GLuint mainProgram;
};

bool Init();

void Render();

void Quit();

#endif // __PROJECTS_TERRAXGAMES_UNNOMINABLE_SRC_RENDER_HPP_