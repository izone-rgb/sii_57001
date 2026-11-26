#include <fstream>
#include "MundoCliente.h"
#include "glut.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

CMundo::CMundo()
{
	Init();
}

CMundo::~CMundo()
{
	if(fd_coords >= 0) close(fd_coords);
	if(fd_teclas >= 0) close(fd_teclas);
	unlink("/tmp/fifo_teclas");
}

void CMundo::InitGL()
{
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	
	glMatrixMode(GL_PROJECTION);
	gluPerspective( 40.0, 800/600.0f, 0.1, 150);
}

void print(char *mensaje, int x, int y, float r, float g, float b)
{
	glDisable (GL_LIGHTING);

	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT) );

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glColor3f(r,g,b);
	glRasterPos3f(x, glutGet(GLUT_WINDOW_HEIGHT)-18-y, 0);
	int len = strlen (mensaje );
	for (int i = 0; i < len; i++) 
		glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, mensaje[i] );
		
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable( GL_DEPTH_TEST );
}

void CMundo::OnDraw()
{
   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	
	gluLookAt(0.0, 0, 17,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	char cad[100];
	sprintf(cad,"Jugador1: %d",puntos1);
	print(cad,10,0,1,1,1);
	sprintf(cad,"Jugador2: %d",puntos2);
	print(cad,650,0,1,1,1);
	int i;
	for(i=0;i<paredes.size();i++)
		paredes[i].Dibuja();

	fondo_izq.Dibuja();
	fondo_dcho.Dibuja();
	jugador1.Dibuja();
	jugador2.Dibuja();
	esfera.Dibuja();

	glutSwapBuffers();
}

void CMundo::OnTimer(int value)
{	
	// Leer coordenadas enviadas por el servidor
	char cad[200];
	if(fd_coords >= 0) {
		if(read(fd_coords, cad, sizeof(cad)) <= 0) exit(0);
		sscanf(cad,"%f %f %f %f %f %f %f %f %f %f %d %d",
			&esfera.centro.x, &esfera.centro.y,
			&jugador1.x1, &jugador1.y1, &jugador1.x2, &jugador1.y2,
			&jugador2.x1, &jugador2.y1, &jugador2.x2, &jugador2.y2,
			&puntos1, &puntos2);
	}

	// Comunicar con el bot mediante memoria compartida
	if(mem_comp != NULL) {
		mem_comp->esfera = esfera;
		mem_comp->raqueta1 = jugador1;
		
		if(mem_comp->accion == 1) OnKeyboardDown('w', 0, 0);
		else if(mem_comp->accion == -1) OnKeyboardDown('s', 0, 0);
	}
}

void CMundo::OnKeyboardDown(unsigned char key, int x, int y)
{
	char cad[100];
	sprintf(cad, "%c", key);
	if(fd_teclas >= 0) write(fd_teclas, cad, sizeof(cad));
}

void CMundo::Init()
{
	puntos1 = 0;
	puntos2 = 0;

	Plano p;
	p.x1=-7;p.y1=-5;
	p.x2=7;p.y2=-5;
	paredes.push_back(p);

	p.x1=-7;p.y1=5;
	p.x2=7;p.y2=5;
	paredes.push_back(p);

	fondo_izq.r=0;
	fondo_izq.x1=-7;fondo_izq.y1=-5;
	fondo_izq.x2=-7;fondo_izq.y2=5;

	fondo_dcho.r=0;
	fondo_dcho.x1=7;fondo_dcho.y1=-5;
	fondo_dcho.x2=7;fondo_dcho.y2=5;

	jugador1.g=0;
	jugador1.x1=-6;jugador1.y1=-1;
	jugador1.x2=-6;jugador1.y2=1;

	jugador2.g=0;
	jugador2.x1=6;jugador2.y1=-1;
	jugador2.x2=6;jugador2.y2=1;

	// Crear FIFO de teclas antes de conectar con el servidor
	unlink("/tmp/fifo_teclas");
	mkfifo("/tmp/fifo_teclas", 0666);

	fd_coords = open("/tmp/fifo_coords", O_RDONLY);
	fd_teclas = open("/tmp/fifo_teclas", O_WRONLY);

	// Memoria compartida para el bot
	int fd_shm = open("/tmp/shm_tenis", O_CREAT | O_RDWR, 0666);
	ftruncate(fd_shm, sizeof(DatosMemCompartida));
	mem_comp = (DatosMemCompartida*)mmap(NULL, sizeof(DatosMemCompartida), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
	close(fd_shm);
}
