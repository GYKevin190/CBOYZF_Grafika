#include "app.h"

#include <SDL2/SDL_image.h>
#include <time.h>
#include <stdio.h>

void init_app(App *app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0)
    {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }
    app->window = SDL_CreateWindow(
        "BallGame!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL)
    {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0)
    {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL)
    {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = true;

    

}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO)
    {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else
    {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 100);
}

void handle_app_events(App *app)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            case SDL_SCANCODE_3:
                if(app->scene.fog_settings.fog_switch<2 && app->scene.showHelp == 1){
                    app->scene.fog_settings.fog_switch=app->scene.fog_settings.fog_switch + 1;
                }
                break;  
            case SDL_SCANCODE_1:
                if(app->scene.fog_settings.fog_switch>0 && app->scene.showHelp == 1){
                    app->scene.fog_settings.fog_switch=(app->scene.fog_settings.fog_switch-1);
                }
                break;
            case SDL_SCANCODE_SPACE:
                app->scene.score.score_count=0;
                app->scene.is_lose=false;
                app->scene.start=clock();
                update_score(&(app->scene.score));
                glFrustum(
                        -.08, .08,
                        -.06, .06,
                        .1, 6000);
                break;
            case SDL_SCANCODE_UP:
                //printf("A ball y-ja: %lf, \n",app->scene.ball.ball_y);
                if(app->scene.ball.ball_y< 7.0){
                    //printf("UP, ball x:%lf, ball y:%lf \n ", app->scene.ball.ball_x, app->scene.ball.ball_y);
                    app->scene.ball.ball_speed_y=+2.0;
                }
                    
                break;
            case SDL_SCANCODE_DOWN:
                if(app->scene.ball.ball_y>-7){
                    app->scene.ball.ball_speed_y=-2.0;
                    //printf("DOWN, ball x:%lf, ball y:%lf \n ", app->scene.ball.ball_x, app->scene.ball.ball_y);
                    //printf("LAbda x: labday: \n", app->scene.ball.ball_x, app->scene.ball.ball_y);
                }
                break;
            case SDL_SCANCODE_LEFT:
                if(app->scene.ball.ball_x>-8.0){
                    app->scene.ball.ball_speed_x=-2.0;
                    //printf("LEFT, ball x:%lf, ball y:%lf \n ", app->scene.ball.ball_x, app->scene.ball.ball_y);
                }
                break;
            case SDL_SCANCODE_RIGHT:
                if(app->scene.ball.ball_x<8.0){
                    app->scene.ball.ball_speed_x=+2.0;
                    //printf("RIGHT, ball x:%lf, ball y:%lf \n ", app->scene.ball.ball_x, app->scene.ball.ball_y);
                }
                break;
            case SDL_SCANCODE_Z:
                app->scene.ball.bouncing=4;
                //printf("ez meg jo \n");
                break;
            case SDL_SCANCODE_W:
                set_camera_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), -1);
                break;
            case SDL_SCANCODE_A:
                set_camera_side_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), -1);
                break;
            case SDL_SCANCODE_KP_PLUS:
                app->scene.light += 0.1;
                break;
            case SDL_SCANCODE_KP_MINUS:
                app->scene.light -= 0.1;
                break;
            case SDL_SCANCODE_F1:
                if (app->scene.showHelp == 0)
                {
                    app->scene.showHelp = 1;
                }
                else
                {
                    app->scene.showHelp = 0;
                    glFrustum(
                        -.08, .08,
                        -.06, .06,
                        .1, 6000);
                }
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_UP:
            case SDL_SCANCODE_DOWN:
                app->scene.ball.ball_speed_y=0.0;
                break;
            case SDL_SCANCODE_LEFT:
            case SDL_SCANCODE_RIGHT:
                app->scene.ball.ball_speed_x=0.0;
                break;
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), 0);
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (is_mouse_down)
            {
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            break;
        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_app(App *app)
{
    double current_time;
    double elapsed_time;
    double ball_z;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene));

    app->scene.ball.ball_y += app->scene.ball.ball_speed_y * 0.010;
    app->scene.ball.ball_x += app->scene.ball.ball_speed_x * 0.010;

    app->scene.ball.rotation_y += app->scene.ball.ball_speed_y * elapsed_time*150*-1;
    app->scene.ball.rotation_x += app->scene.ball.ball_speed_x * elapsed_time*150;  

    if (app->scene.ball.rotation_y < 0)
    {
        app->scene.ball.rotation_y += 360.0;
    }

    if (app->scene.ball.rotation_y > 360.0)
    {
        app->scene.ball.rotation_y -= 360.0;
    }

    if (app->scene.ball.rotation_x < 0)
    {
        app->scene.ball.rotation_x += 360.0;
    }

    if (app->scene.ball.rotation_x > 360.0)
    {
        app->scene.ball.rotation_x -= 360.0;
    }


    //app->scene.ball.gravity
    //printf("Elapsed time= %lf \n ", elapsed_time);
    

    app->scene.ball.upward_speed +=  -30.0 * elapsed_time;
    //printf("upward speed: %lf \n", app->scene.ball.upward_speed);
    app->scene.ball.rotation_z += app->scene.ball.upward_speed * elapsed_time;

    if(app->scene.ball.rotation_z < 0.2)
    {
        app->scene.ball.upward_speed = 0.0;
        app->scene.ball.rotation_z = 0.2;
        app->scene.ball.in_the_air = FALSE;
    }

    if(!app->scene.ball.in_the_air && app->scene.ball.bouncing == 4)
    {
        app->scene.ball.upward_speed = 6;
        app->scene.ball.in_the_air = TRUE;
        app->scene.ball.bouncing = 3;
    }


    if(!app->scene.ball.in_the_air && app->scene.ball.bouncing == 3)
    {
        app->scene.ball.upward_speed = 4;
        app->scene.ball.in_the_air = TRUE;
        app->scene.ball.bouncing = 2;
    }

    if(!app->scene.ball.in_the_air && app->scene.ball.bouncing == 2)
    {
        app->scene.ball.upward_speed = 2;
        app->scene.ball.in_the_air = TRUE;
        app->scene.ball.bouncing = 1;
    }

    if(!app->scene.ball.in_the_air && app->scene.ball.bouncing == 1)
    {
        app->scene.ball.upward_speed = 0.7;
        app->scene.ball.in_the_air = TRUE;
        app->scene.ball.bouncing = 0;
    }
    







}

void render_app(App *app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));
    glPopMatrix();

    if (app->camera.is_preview_visible)
    {
        show_texture_preview();
    }

    if (app->scene.showHelp == 1)
    {
        help(app->scene.help_texture_id);
        if(app->scene.fog_settings.fog_switch==0){
        render_fog(app->scene.fog_settings.st_1_en, -1.5, -0.7,-0.6,-1.7);
        render_fog(app->scene.fog_settings.st_2_di, -0.45,-0.7, 0.45,-1.7);
        //fog_3(app->scene.fog_settings.st_3_di);
        render_fog(app->scene.fog_settings.st_3_di, 0.6,-0.7, 1.5,-1.7);
        app->scene.fog_settings.strength=0.07;
        }
        else if(app->scene.fog_settings.fog_switch==1){
        render_fog(app->scene.fog_settings.st_1_di,-1.5, -0.7,  -0.6, -1.7);
        render_fog(app->scene.fog_settings.st_2_en, -0.45,-0.7, 0.45,-1.7);
        //fog_3(app->scene.fog_settings.st_3_di);
        render_fog(app->scene.fog_settings.st_3_di, 0.6,-0.7, 1.5,-1.7);
        app->scene.fog_settings.strength=0.2;
        }
        else if(app->scene.fog_settings.fog_switch==2){
        render_fog(app->scene.fog_settings.st_1_di,-1.5, -0.7,  -0.6, -1.7);
        render_fog(app->scene.fog_settings.st_2_di, -0.45,-0.7, 0.45,-1.7);
        //fog_3(app->scene.fog_settings.st_3_en);
        render_fog(app->scene.fog_settings.st_3_en, 0.6,-0.7, 1.5,-1.7);
        app->scene.fog_settings.strength=0.3;
        }
        

    }

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App *app)
{
    if (app->gl_context != NULL)
    {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL)
    {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}
