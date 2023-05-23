#include "fog_settings.h"

void init_fog(Fog_settings *fog_settings)
{
    fog_settings->fog_switch=1;
    fog_settings->strength=0.4;
    fog_settings->st_1_en = load_texture("assets/textures/fog_1_en.jpg");
    fog_settings->st_1_di = load_texture("assets/textures/fog_1_di.jpg");
    fog_settings->st_2_en = load_texture("assets/textures/fog_2_en.jpg");
    fog_settings->st_2_di = load_texture("assets/textures/fog_2_di.jpg");
    fog_settings->st_3_en = load_texture("assets/textures/fog_3_en.jpg");
    fog_settings->st_3_di = load_texture("assets/textures/fog_3_di.jpg");
}

void render_fog(GLuint texture, float x1,float y1, float x2,float y2){
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
    glVertex3d(x1, y1, -3);
    glTexCoord2f(1, 0);
    glVertex3d(x2, y1, -3);
    glTexCoord2f(1, 1);
    glVertex3d(x2, y2, -3);
    glTexCoord2f(0, 1);
    glVertex3d(x1, y2, -3);
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_FOG);
}

