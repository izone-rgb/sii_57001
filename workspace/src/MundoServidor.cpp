#include <fstream>
#include "MundoServidor.h"
#include "glut.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void* hilo_comandos(void* d)
{
	CMundo* p=(CMundo*) d;
	p->RecibeComandosJugador();
	return NULL;
}

CMundo::CMundo()
{
	Init();
}

CMundo::~CMundo()
{
	if(fd_logger >= 0) close(fd_logger);
	if(fd_coords >= 0) close(fd_coords);
	if(fd_teclas >= 0) close(fd_teclas);
	unlink("/tmp/fifo_coords");
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
	jugador1.Mueve(0.025f);
	jugador2.Mueve(0.025f);
	esfera.Mueve(0.025f);
	int i;
	for(i=0;i<paredes.size();i++)
	{
		paredes[i].Rebota(esfera);
		paredes[i].Rebota(jugador1);
		paredes[i].Rebota(jugador2);
	}

	jugador1.Rebota(esfera);
	jugador2.Rebota(esfera);
	if(fondo_izq.Rebota(esfera))
	{
		esfera.centro.x=0;
		esfera.centro.y=rand()/(float)RAND_MAX;
		esfera.velocidad.x=2+2*rand()/(float)RAND_MAX;
		esfera.velocidad.y=2+2*rand()/(float)RAND_MAX;
		puntos2++;
		
		char msg[100];
		int len = sprintf(msg, "Jugador 2 marca 1 punto, lleva un total de %d puntos.\n", puntos2);
		if(fd_logger >= 0) write(fd_logger, msg, len);
		if(puntos2 >= 3) exit(0);
	}

	if(fondo_dcho.Rebota(esfera))
	{
		esfera.centro.x=0;
		esfera.centro.y=rand()/(float)RAND_MAX;
		esfera.velocidad.x=-2-2*rand()/(float)RAND_MAX;
		esfera.velocidad.y=-2-2*rand()/(float)RAND_MAX;
		puntos1++;
		
		char msg[100];
		int len = sprintf(msg, "Jugador 1 marca 1 punto, lleva un total de %d puntos.\n", puntos1);
		if(fd_logger >= 0) write(fd_logger, msg, len);
		if(puntos1 >= 3) exit(0);
	}

	// Enviar coordenadas al cliente
	char cad[200];
	sprintf(cad,"%f %f %f %f %f %f %f %f %f %f %d %d",
		esfera.centro.x, esfera.centro.y,
		jugador1.x1, jugador1.y1, jugador1.x2, jugador1.y2,
		jugador2.x1, jugador2.y1, jugador2.x2, jugador2.y2,
		puntos1, puntos2);
	if(fd_coords >= 0) write(fd_coords, cad, sizeof(cad));
}

void CMundo::OnKeyboardDown(unsigned char key, int x, int y)
{
	// El servidor recibe las teclas a través del hilo
}

void CMundo::RecibeComandosJugador()
{
	fd_teclas = open("/tmp/fifo_teclas", O_RDONLY);
	while (1) {
		usleep(10);
		char cad[100];
		if(read(fd_teclas, cad, sizeof(cad)) > 0) {
			unsigned char key;
			sscanf(cad,"%c",&key);
			if(key=='s')jugador1.velocidad.y=-4;
			if(key=='w')jugador1.velocidad.y=4;
			if(key=='l')jugador2.velocidad.y=-4;
			if(key=='o')jugador2.velocidad.y=4;
		}
	}
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
	
	fd_logger = open("/tmp/fifo_tenis", O_WRONLY);

	unlink("/tmp/fifo_coords");
	mkfifo("/tmp/fifo_coords", 0666);
	fd_coords = open("/tmp/fifo_coords", O_WRONLY);

	pthread_create(&thid1, NULL, hilo_comandos, this);
}
	
