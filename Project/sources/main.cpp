#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_events.h>
#include <SDL/SDL_video.h>
#include <cstdlib>

#include "main.h"

int main(int argc, char *argv[]) {
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	atexit(SDL_Quit);
	SDL_WM_SetCaption("SDL GL Application", NULL);
	SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);

	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, (double) 640 / 480, 1, 1000);

	Dessiner();

	for (;;) {
		SDL_WaitEvent(&event);

		switch (event.type) {
		case SDL_QUIT:
			exit(0);
			break;
		}
		Dessiner();
	}

	return 0;
}

void Dessiner() {
	glClear( GL_COLOR_BUFFER_BIT);

	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(3, 4, 2, 0, 0, 0, 0, 0, 1);

	glBegin(GL_QUADS);

	glColor3ub(255, 0, 0); //face rouge
	glVertex3d(1, 1, 1);
	glVertex3d(1, 1, -1);
	glVertex3d(-1, 1, -1);
	glVertex3d(-1, 1, 1);
	glEnd();

	glFlush();
	SDL_GL_SwapBuffers();
}
