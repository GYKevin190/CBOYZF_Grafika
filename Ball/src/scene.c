#include "scene.h"
#include <obj/load.h>
#include <obj/draw.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

  

void init_scene(Scene *scene)
{
    

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    load_model(&(scene->ground), "assets/models/ground.obj");
    scene->ground_texture = load_texture("assets/textures/ground.jpg");
    scene->help_texture_id = load_texture("assets/textures/help_texture.jpg");
    scene->goal_texture=load_texture("assets/textures/goal.jpg");
    scene->win_texture=load_texture("assets/textures/win.jpg");
    load_model(&(scene->skybox), "assets/models/skybox.obj");
    scene->skybox_texture = load_texture("assets/textures/sky.jfif");


    scene->timer_texture_0=load_texture("assets/textures/remaining_time_0.jpg");
    scene->timer_texture_1=load_texture("assets/textures/remaining_time_1.jpg");
    scene->timer_texture_2=load_texture("assets/textures/remaining_time_2.jpg");
    scene->timer_texture_3=load_texture("assets/textures/remaining_time_3.jpg");
    scene->timer_texture_4=load_texture("assets/textures/remaining_time_4.jpg");
    scene->timer_texture_5=load_texture("assets/textures/remaining_time_5.jpg");
    scene->drawn_timer_texture=load_texture("assets/textures/remaining_time_5.jpg");
    scene->lose_texture=load_texture("assets/textures/lose.jpg");
    init_ball(&(scene->ball));
    init_fence(&(scene->fence));
    init_gate(&(scene->gate));
    init_score(&(scene->score));
    init_tree(&(scene->tree));
    init_fog(&(scene->fog_settings));
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_FOG);
    float color[]={0.5,0.5,0.5,1.0};
    glFogfv(GL_FOG_COLOR,color);
    //glFogf(GL_FOG_DENSITY, scene->fog_settings.strength);
    //glHint(GL_FOG_HINT, GL_NICEST);
    //glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START,0.0f); 
    glFogf(GL_FOG_END,1.0f);
    

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;

    scene->light = 1.0f;

    scene->showHelp = 1;

    scene->showGoal=0;
    scene->is_lose=false;
    scene->start=0;
    scene->isGoaled=false;
    scene->isStart=true;
    scene->max_time=20;

    scene->start=clock();


}

void set_lighting(float x)
{
    float ambient_light[] = {x, x, x, 1.0f};
    float diffuse_light[] = {x, x, x, 1.0f};
    float specular_light[] = {x, x, x, 1.0f};
    float position[] = {0.0f, 0.0f, 10.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material *material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue};

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue};

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));

}

void update_scene(Scene *scene)
{
    set_lighting(scene->light);

    glFogf(GL_FOG_DENSITY, scene->fog_settings.strength);

    if(scene->ball.ball_y >5.8 && scene->ball.ball_x >-2.5 && scene->ball.ball_x <1.8 && scene->ball.ball_y<6.2){
        scene->isGoaled=true;
    }

    scene->current_time=clock();

    if((    (    (float)(scene->current_time- scene->show_start ) )   >350)){
        scene->showGoal=0;
    }

    if(scene->isGoaled && scene->score.score_count<4){
        scene->showGoal=1;
        scene->show_start=clock();
        scene->score.score_count=scene->score.score_count+1;
        update_score(&(scene->score));

    }
    else if(scene->isGoaled) {
        scene->score.score_count=scene->score.score_count+1;
        update_score(&(scene->score));
    }
    

    if(scene->isGoaled || scene->isStart){
        srand(rand());
        scene->random_y= (float)rand()/(float)(RAND_MAX/16)-8;
        scene->random_x = (float)rand()/(float)(RAND_MAX/16)-8;
        scene->ball.ball_x = scene->random_x;
        scene->ball.ball_y= scene->random_y;
        scene->isGoaled=false;
        scene->isStart=false;
    }


    scene->end=clock();
    scene->timer=((float)(scene->end - scene->start) / CLOCKS_PER_SEC);
    //printf("Az eltelt ido: %lf \n", scene->timer );
    //printf("Az elso amit megnezunk: %lf, a masodik amit megnezunk: %lf \n", scene->timer, asd);
    if(scene->timer < (0.2)*scene->max_time){
        scene->drawn_timer_texture= scene->timer_texture_5;
    }
    else if(scene->timer < (0.4)*scene->max_time && scene->timer > (0.2)*scene->max_time ){
        scene->drawn_timer_texture= scene->timer_texture_4;
    }
    else if(scene->timer < (0.6)*scene->max_time && scene->timer > (0.4)*scene->max_time ) {
        scene->drawn_timer_texture= scene->timer_texture_3;
    }
    else if(scene->timer < (0.8)*scene->max_time && scene->timer > (0.6)*scene->max_time){
        scene->drawn_timer_texture= scene->timer_texture_2;
    }
    else if(scene->timer > (0.8)*scene->max_time ){
        scene->drawn_timer_texture= scene->timer_texture_1;
    }
    if(scene->timer >scene->max_time ){
        scene->drawn_timer_texture= scene->timer_texture_0;
        scene->is_lose=true;
    }
    
}

void render_scene(const Scene *scene)
{

    if(scene->score.score_count == 5){
        END(scene->win_texture);
    }

    if(scene->showGoal==1){
        END(scene->goal_texture);
    }

    // ground
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene->ground_texture);
    glRotated(90, 1, 0, 0);
    draw_model(&(scene->ground));
    glBindTexture(GL_TEXTURE_2D, scene->gate.gate_texture);
    draw_model(&(scene->gate.gate));
    glBindTexture(GL_TEXTURE_2D, scene->fence.fence_texture);
    draw_model(&(scene->fence.fence));
    glBindTexture(GL_TEXTURE_2D, scene->score.score_leg_texture);
    draw_model(&(scene->score.score_leg));
    glBindTexture(GL_TEXTURE_2D, scene->score.score_board_texture);
    draw_model(&(scene->score.score_board));
    glBindTexture(GL_TEXTURE_2D, scene->tree.tree_texture);
    draw_model(&(scene->tree.tree));
    glBindTexture(GL_TEXTURE_2D, scene->tree.leaves_texture);
    draw_model(&(scene->tree.leaves));
    glBindTexture(GL_TEXTURE_2D, scene->skybox_texture);
    draw_model(&(scene->skybox));
    glPopMatrix();

    // ball
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->ball.ball_texture);
    glTranslatef(scene->ball.ball_x, scene->ball.ball_y, scene->ball.rotation_z);
    //printf("a ball z %lf \n",scene->ball.ball_z);
    glRotatef(scene->ball.rotation_y,1,0,0);
    glRotatef(scene->ball.rotation_x,0,1,0);
    draw_model(&(scene->ball.ball));
    glPopMatrix();


    
    timer(scene->drawn_timer_texture);

    if(scene->is_lose){
        END(scene->lose_texture);
    }
    


}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void END(GLuint texture)
{
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_FOG);
}

void timer(GLuint texture)
{
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2.25, 1.65, -3);
    glTexCoord2f(1, 0);
    glVertex3d(-0.5, 1.65, -3);
    glTexCoord2f(1, 1);
    glVertex3d(-0.5, 1.45, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2.25, 1.45, -3);
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_FOG);
}

void help(GLuint texture)
{
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-1.5, 1.4, -3);
    glTexCoord2f(1, 0);
    glVertex3d(1.5, 1.4, -3);
    glTexCoord2f(1, 1);
    glVertex3d(1.5, -0.6, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-1.5, -0.6, -3);
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_FOG);
}




