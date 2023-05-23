#ifndef TREE_H

#define TREE_H

#include "camera.h"
#include "texture.h"
#include <math.h>
#include <obj/model.h>

typedef struct Tree
{
    Model tree;
    GLuint tree_texture;
    Model leaves;
    GLuint leaves_texture;

} Tree;

void init_tree(Tree *tree);

#endif