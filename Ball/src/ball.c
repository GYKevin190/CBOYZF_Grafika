#include "ball.h"

void init_ball(Ball *ball)
{

    load_model(&(ball->ball), "assets/models/ball.obj");
    ball->ball_texture = load_texture("assets/textures/ball.jpg");

    ball->ball_x = 0.0f;
    ball->ball_y= 0.0f;

    ball->ball_speed_y=0.0;
    ball->ball_speed_x=0.0;
    ball->rotation_x=0.0;
    ball->rotation_y=0.0;



    ball->rotation_z=0.2;
    ball->bouncing=0.0;
    ball->in_the_air=false;
    ball->upward_speed = 0.0;
    ball->gravity = -30.0;

}