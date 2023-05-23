#ifndef FENCE_H

#define FENCE_H

#include "camera.h"
#include "texture.h"
#include <math.h>
#include <obj/model.h>

typedef struct Fence
{
    Model fence;
    GLuint fence_texture;

} Fence;

void init_fence(Fence *fence);

#endif