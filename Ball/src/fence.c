#include "fence.h"

void init_fence(Fence *fence)
{
    load_model(&(fence->fence), "assets/models/fence.obj");
    fence->fence_texture = load_texture("assets/textures/fence.jpg");

}