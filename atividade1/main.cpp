#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//#include <math.h>

float velocidadePlataforma = 15.0, velocidadeBola = 0.18;
float y1 = 250.0, y2 = 250.0, bolax = 442.0, bolay = 300.0;
int movimento = 0, cont = 0;

void desenha(void);
void desenhaCenario();
void desenhaPlataforma();
void desenhaBola();
int autorizaMovimento(float y, int direcao);
void Key(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);
void init(void);
void movimentoBola();
void circulo();

int main(void) {
    srand(time(NULL));
    movimento = rand()%4;

    //Tipo de janela (single-buffered) e cores utilizados
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	//Configura o tamanho da janela
	glutInitWindowSize (900, 600);

	//Configura a posição inicial da janela
	glutInitWindowPosition (100, 100);

	//Configura a janela
	glutCreateWindow("Jogo Pong");

	glutKeyboardFunc(Key);

	//Callback de teclas especiais
	glutSpecialFunc(specialKeyboard);

	//Chama a função desenha
	glutDisplayFunc(desenha);

	//Inicializa o programa
	init();

	//Habilita o loop (máquina de estados)
	glutMainLoop();
}

void desenha(void) { //Função callback para desenho
    //Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Define os limites dos eixos x e y
    //Argumentos da função: void gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
    gluOrtho2D (0.0f, 900.0f, 0.0f, 600.0f);

    glClear(GL_COLOR_BUFFER_BIT); //Limpa todos os pixels com a cor de fundo

	desenhaCenario();

	glPushMatrix();
        glTranslated(10, y1, 0);
        desenhaPlataforma();
	glPopMatrix();

	glPushMatrix();
        glTranslated(875, y2, 0);
        desenhaPlataforma();
    glPopMatrix();

    glPushMatrix();
        glTranslated(bolax, bolay, 0);
        desenhaBola();
        //circulo();
        movimentoBola();
    glPopMatrix();

    glutPostRedisplay();

	glFlush(); //Habilita a execução de comandos OpenGL
}

void movimentoBola() {
    if(movimento == 0) {
        bolax -= velocidadeBola;
        if(bolay < 550) bolay += velocidadeBola;
        else movimento = 2;
        if(bolax < 25) {
            if((bolay > y1) && (bolay < y1 + 100)) {
                printf("Boa!\n");
                cont++;
                movimento = 1;
            }
        }
    }

    if(movimento == 1) {
        bolax += velocidadeBola;
        if(bolay < 550) bolay += velocidadeBola;
        else movimento = 3;
        if(bolax > 860) {
            if((bolay > y2) && (bolay < y2 + 100)) {
                printf("Boa!\n");
                cont++;
                movimento = 0;
            }
        }
    }

    if(movimento == 2) {
        bolax -= velocidadeBola;
        if(bolay > 35) bolay -= velocidadeBola;
        else movimento = 0;
        if(bolax < 25) {
            if((bolay > y1) && (bolay < y1 + 100)) {
                printf("Boa!\n");
                cont++;
                movimento = 3;
            }
        }
    }

    if(movimento == 3) {
        bolax += velocidadeBola;
        if(bolay > 35) bolay -= velocidadeBola;
        else movimento = 1;
        if(bolax > 860) {
            if((bolay > y2) && (bolay < y2 + 100)) {
                printf("Boa!\n");
                cont++;
                movimento = 2;
            }
        }
    }

    if(cont == 5) {
        velocidadeBola += 0.01;
        cont = 0;
    }
}

void desenhaCenario() {
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
        glVertex2i(10, 20);
        glVertex2i(10, 35);
        glVertex2i(890, 35);
        glVertex2i(890, 20);

        glVertex2i(10, 580);
        glVertex2i(10, 565);
        glVertex2i(890, 565);
        glVertex2i(890, 580);
    glEnd();

    glLineWidth(20.0);
    glBegin(GL_LINES);
    for(int i = 20; i < 580; i+=38) {
        glVertex2i(450, i);
        glVertex2i(450, i+19);
    }
    glEnd();
}

void desenhaPlataforma() {
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
        glVertex2i(0, 0);
        glVertex2i(0, 100);
        glVertex2i(15, 100);
        glVertex2i(15, 0);
    glEnd();
}

void desenhaBola() {
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
        glVertex2i(0, 0);
        glVertex2i(0, 15);
        glVertex2i(15, 15);
        glVertex2i(15, 0);
    glEnd();
}
/*
void circulo(){
    float angulo;
    glBegin(GL_POLYGON);
        for(int i=0; i<360; i++){
            angulo = i * 2 * M_PI / 360;
            glVertex2f(450 + (cos(angulo) * 15), 300 + (sin(angulo) * 15));
        }
    glEnd();
}*/

int autorizaMovimento(float y, int direcao) {
    if ((direcao == 1) && (y < 465)) return true;
    else if ((direcao == 0) && (y > 35)) return true;
    else return false;
}

void Key(unsigned char key, int x, int y) {
    if((key == 119) && (autorizaMovimento(y1, 1))) y1 += velocidadePlataforma;
    if((key == 115) && (autorizaMovimento(y1, 0))) y1 -= velocidadePlataforma;
}

void specialKeyboard(int key, int x, int y) {
    if((key == GLUT_KEY_UP) && (autorizaMovimento(y2, 1))) y2 += velocidadePlataforma;
    if((key == GLUT_KEY_DOWN) && (autorizaMovimento(y2, 0))) y2 -= velocidadePlataforma;
}

void init(void) { //Inicializa parâmetros
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Configura a cor de fundo como preta
}
