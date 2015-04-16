#include <freeflycamera.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <scene.h>
#include <sdlglutils.h>
#include <SDL/SDL.h>
#include <SDL/SDL_events.h>
#include <SDL/SDL_stdinc.h>
#include <SDL/SDL_timer.h>
#include <SDL/SDL_video.h>
#include <vector3d.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define FPS 50
#define LARGEUR_FENETRE 640
#define HAUTEUR_FENETRE 480

void DrawGL();

FreeFlyCamera * camera;

void stop() {
	delete camera;
	SDL_Quit();
}

const void getScreenshotFilename(char * dest) {
	static int nbScreenshot = 0;

	sprintf(dest, "screenshot-%d", ++nbScreenshot);
	strcat(dest, ".bmp");
}

void executeControl(const SDL_Event& event) {
	switch (event.type) {
	case SDL_QUIT:
		exit(0);
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_p:
			char filename[255];
			getScreenshotFilename(filename);
			takeScreenshot(filename);
			printf("Screenshot saved (%s).\n", filename);
			break;
		case SDLK_ESCAPE:
			exit(0);
			break;
		default:
			camera->OnKeyboard(event.key);
		}
		break;
	case SDL_KEYUP:
		camera->OnKeyboard(event.key);
		break;
	case SDL_MOUSEMOTION:
		camera->OnMouseMotion(event.motion);
		break;
	case SDL_MOUSEBUTTONUP:
	case SDL_MOUSEBUTTONDOWN:
		camera->OnMouseButton(event.button);
		break;
	}
}

void pollAndExecuteAllEvents(SDL_Event& event) {
	while (SDL_PollEvent(&event)) {
		executeControl(event);
	}
}

int main(int argc, char *argv[]) {
	SDL_Event event;
	const Uint32 time_per_frame = 1000 / FPS;
	unsigned int width = LARGEUR_FENETRE;
	unsigned int height = HAUTEUR_FENETRE;

	Uint32 last_time, current_time, elapsed_time; //for time animation
	Uint32 start_time, stop_time; //for frame limit

	SDL_Init(SDL_INIT_VIDEO);
	atexit(stop);

	SDL_WM_SetCaption("Synthèse 3D - Projet 2015", NULL);
	SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
	//initFullScreen(&width,&height);

	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, (double) width / height, 0.001, 1000);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	chargerTextures();

	camera = new FreeFlyCamera(Vector3D(0, 0, 2));

	last_time = SDL_GetTicks();
	for (;;) {
		start_time = SDL_GetTicks();

		pollAndExecuteAllEvents(event);

		current_time = SDL_GetTicks();
		elapsed_time = current_time - last_time;
		last_time = current_time;

		camera->animate(elapsed_time);

		DrawGL();

		stop_time = SDL_GetTicks();
		if ((stop_time - last_time) < time_per_frame) {
			SDL_Delay(time_per_frame - (stop_time - last_time));
		}

	}

	return 0;
}

void DrawGL() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();

	camera->look();

	dessinerScene();

	glFlush();
	SDL_GL_SwapBuffers();
}

