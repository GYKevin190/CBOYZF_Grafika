#include "scoreboard.h"

void init_score(Score *score)
{
    score->score_x = 0.0f;
    score->score_y= 0.0f;

    score->score_count=0;

    load_model(&(score->score_leg), "assets/models/score_board_leg.obj");
    score->score_leg_texture = load_texture("assets/textures/gate.jpg");
    score->score_board_texture = load_texture("assets/textures/score_0.jpg");
    load_model(&(score->score_board), "assets/models/score_board.obj");
    score->score_0=load_texture("assets/textures/score_0.jpg");
    score->score_1=load_texture("assets/textures/score_1.jpg");
    score->score_2=load_texture("assets/textures/score_2.jpg");
    score->score_3=load_texture("assets/textures/score_3.jpg");
    score->score_4=load_texture("assets/textures/score_4.jpg");
    score->score_5=load_texture("assets/textures/score_5.jpg");
    
}



void update_score(Score *score){
    if(score->score_count==0){
        score->score_board_texture =score->score_0 ;
    }
    else if (score->score_count==1){
        score->score_board_texture =score->score_1 ;
    }
    else if (score->score_count==2){
        score->score_board_texture = score->score_2;
    }
    else if (score->score_count==3){
        score->score_board_texture = score->score_3;
    }
    else if (score->score_count==4){
        score->score_board_texture =score->score_4 ;
    }
    else {
        score->score_board_texture =score->score_5 ;
    }
}