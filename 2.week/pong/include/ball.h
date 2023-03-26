#ifndef BALL_H
#define BALL_H

/**
 * Ball position and speed
 */
typedef struct Ball
{
    float x;
    float y;
    float radius;
    float speed_x;
    float speed_y;
} Ball;

/**
 * Move the ball to the given position.
 */
void init_ball(Ball* ball, float x, float y);

/**
 * Update the ball.
 * @param time elapsed time in seconds.
 */
void update_ball(Ball* ball, double time);

void set_ball_pos(Ball* ball, float x, float y);

void inc_ball_size(Ball* ball, float radius);

void dec_ball_size(Ball* ball, float radius);

/**
 * Render the ball.
 */
void render_ball(Ball* ball);

#endif /* BALL_H */
