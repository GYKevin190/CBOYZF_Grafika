#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include <math.h>
#include <obj/model.h>
#include "ball.h"
#include "fence.h"
#include "gate.h"
#include "scoreboard.h"
#include "tree.h"
#include <time.h>
#include "fog_settings.h"

typedef struct Scene
{

    Material material;

    float random_y;
    float random_x;
    bool isGoaled;
    bool isStart; 

    Ball ball;
    Fence fence;
    Gate gate;
    Tree tree;
    Model skybox;
    GLuint skybox_texture;

    Fog_settings fog_settings;

    Score score;

    Model ground;
    GLuint ground_texture;
    float light;
    bool is_lose;

    GLuint help_texture_id;
    GLuint lose_texture;
    GLuint goal_texture;
    GLuint win_texture;
    GLuint timer_texture_5;
    GLuint timer_texture_4;
    GLuint timer_texture_3;
    GLuint timer_texture_2;
    GLuint timer_texture_1;
    GLuint timer_texture_0;
    GLuint drawn_timer_texture;
    int showGoal;
    int showHelp;
    float timer;
    float max_time;

    clock_t start;
    clock_t end;

    clock_t show_start;
    clock_t current_time;




} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene *scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(float x);

/**
 * Set the current material.
 */
void set_material(const Material *material);

/**
 * Update the scene.
 */
void update_scene(Scene *scene);

/**
 * Render the scene objects.
 */
void render_scene(const Scene *scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

void END(GLuint texture);

void goal(GLuint texture);

void timer(GLuint texture);

void help(GLuint texture);

#endif /* SCENE_H */
