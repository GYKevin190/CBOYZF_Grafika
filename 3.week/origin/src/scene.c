#include "scene.h"

#include <GL/gl.h>
#include <math.h>

#define M_PI 3.14159265359
#define CELL_SIZE 2

void init_scene(Scene *scene)
{
}

void update_scene(Scene *scene)
{
}

void render_scene(const Scene *scene)
{
    draw_origin();
    drawBoard();
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

void drawSquare(int i, int j, int color) {
    int x = i * CELL_SIZE;
    int y = j * CELL_SIZE;

    if (color == 0) {
        glColor3f(1.0, 1.0, 1.0);
    } else {
        glColor3f(0.0, 0.0, 0.0);
    }

    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + CELL_SIZE, y);
    glVertex2i(x + CELL_SIZE, y + CELL_SIZE);
    glVertex2i(x, y + CELL_SIZE);
    glEnd();
}

void drawBoard() {
    int i, j, color;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            color = (i + j) % 2;
            drawSquare(i, j, color);
        }
    }
}