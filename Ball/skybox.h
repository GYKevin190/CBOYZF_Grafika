#ifndef SKYBOX_H
#define SKYBOX_H

#include <obj/load.h>
#include <obj/draw.h>
#include <GL/gl.h>
#include "texture.h"

typedef struct Skybox {
    GLuint left;
    GLuint right;
    GLuint top;
    GLuint bottom;
    GLuint front;
    GLuint back;
} Skybox;

/**
 * Initialize the skybox.
*/
void init_skybox(Skybox* skybox);

/**
 * Render the skybox.
*/
void render_skybox(const Skybox *skybox);



#endif /*SKYBOX_H*/