#ifndef FOG_SETTINGS_H

#define FOG_SETTINGS_H

#include "camera.h"
#include "texture.h"
#include <math.h>
#include <obj/model.h>

typedef struct Fog_settings
{
    int fog_switch;
    float strength;
    GLuint st_1_en;
    GLuint st_1_di;
    GLuint st_2_en;
    GLuint st_2_di;
    GLuint st_3_en;
    GLuint st_3_di;

} Fog_settings;

void init_fog(Fog_settings *fog_settings);



void render_fog(GLuint texture, float x1,float y1, float x2,float y2);


#endif