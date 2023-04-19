#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <obj/transform.h>
#include <math.h>

#include <SDL2/SDL_image.h>

#define PI 3.14159265359

void init_scene(Scene *scene)
{
    load_model(&(scene->cat), "assets/models/cat.obj");
    load_model(&(scene->deer), "assets/models/deer.obj");
    scene->texture_id = load_texture("assets/textures/cube.png");

    glBindTexture(GL_TEXTURE_2D, scene->texture_id);

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->rotation_speed = 0.0f;
    scene->rotation.x = 0.0f;

    scene->material.shininess = 0.0;
}

void set_lighting()
{
    float ambient_light[] = {0.0f, 1.0f, 0.0f, 1.0f};
    float diffuse_light[] = {1.0f, 0.0f, 1.0f, 1.0f};
    float specular_light[] = {0.0f, 1.0f, 1.0f, 1.0f};
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
}

void set_obj_rotation(Scene *scene, double speed)
{
   scene->rotation.x = speed;
}

void update_objects(Scene *scene, double time)
{
    if (scene->rotation_speed < 0)
    {
        scene->rotation_speed += 360.0;
    }

    if (scene->rotation_speed > 360.0)
    {
        scene->rotation_speed -= 360.0;
    }

    double angle;
    angle = degree_to_radian(scene->rotation_speed);

    scene->rotation_speed += time * scene->rotation.x / PI;
}

void render_scene(const Scene *scene)
{
    set_material(&(scene->material));
    set_lighting();
    glPushMatrix();
    draw_origin();
    glRotatef(90, 1, 0, 0);
    glRotatef(scene->rotation_speed, 0, 1, 0);
    draw_model(&(scene->cat));
    draw_model(&(scene->deer));
    glPopMatrix();
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
