#ifndef BALL_H

#define BALL_H

#include "camera.h"
#include "texture.h"
#include <math.h>
#include <obj/model.h>

typedef struct Ball
{
    Model ball;
    GLuint ball_texture;

    float ball_x;
    float ball_y;
    float ball_z;
    float ball_speed_y;
    float ball_speed_x;
    float rotation_y;
    float rotation_x;
    


    float rotation_z;
    float bouncing;
    bool in_the_air;
    float upward_speed;
    float gravity;

} Ball;

void init_ball(Ball *ball);

void bounce_ball(Ball *ball);



#endif