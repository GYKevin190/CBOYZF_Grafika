#include "tree.h"

void init_tree(Tree *tree)
{
    load_model(&(tree->tree), "assets/models/tree_mesh.obj");
    tree->tree_texture = load_texture("assets/textures/tree.jpg");

    load_model(&(tree->leaves), "assets/models/leaves.obj");
    tree->leaves_texture = load_texture("assets/textures/leaves.jpg");
}


