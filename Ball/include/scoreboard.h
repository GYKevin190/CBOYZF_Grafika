#ifndef SCORE_H

#define SCORE_H

#include "camera.h"
#include "texture.h"
#include <math.h>
#include <obj/model.h>

typedef struct Score
{

    int score_count;
    
    Model score_leg;

    GLuint score_leg_texture;

    Model score_board;

    GLuint score_board_texture;

    GLuint score_0;
    GLuint score_1;
    GLuint score_2;
    GLuint score_3;
    GLuint score_4;
    GLuint score_5;

    float score_x;
    float score_y;


} Score;

void init_score(Score *score);
void update_score(Score *score);


#endif