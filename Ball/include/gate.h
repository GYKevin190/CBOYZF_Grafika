#ifndef GATE_H

#define GATE_H

#include "camera.h"
#include "texture.h"
#include <math.h>
#include <obj/model.h>

typedef struct Gate
{
    Model gate;
    GLuint gate_texture;

} Gate;

void init_gate(Gate *gate);

#endif