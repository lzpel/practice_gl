#define SDL_MAIN_HANDLED
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

static const int width = 480, height = 360, p=1000;

void draw() {
    int t=SDL_GetTicks()%p;
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(0.5+0.5*sin(5*M_PI*t/p), 0.5+0.5*sin(7*M_PI*t/p), 0.5+0.5*sin(11*M_PI*t/p));
    glVertex2f(sin(2*M_PI*t/p), 1);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glEnd();
    glFlush();
}

int main(int ArgCount, char **Args) {
    SDL_Window *Window = SDL_CreateWindow("OpenGL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,SDL_WINDOW_OPENGL);
    SDL_GLContext Context = SDL_GL_CreateContext(Window);
    for (int Running = 1; Running;) {
        SDL_Event Event;
        while (SDL_PollEvent(&Event)) {
            if (Event.type == SDL_QUIT)Running = 0;
        }
        glViewport(0, 0, width, height);
        draw();
        SDL_GL_SwapWindow(Window);
    }
    return 0;
}