#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

float velocidadePlataforma = 15.0, velocidadeBola = 0.25;
float y1 = 250.0, y2 = 250.0, bolax = 442.0, bolay = 300.0;
int movimento = 0, cont = 0, menu = 0, placar1 = 0, placar2 = 0;

void desenha(void);
void desenhaCenario();
void desenhaPlataforma();
void desenhaBola();
int autorizaMovimento(float y, int direcao);
void Key(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);
void init(void);
void movimentoBola();
void maquina();
void desenhaPlacar(int x, int placar);

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
        //maquina();
    glPopMatrix();

    glPushMatrix();
        glTranslated(350, 450, 0);
        desenhaPlacar(placar1, 1);
        glTranslated(155, 0, 0);
        desenhaPlacar(placar2, 2);
    glPopMatrix();

    glPushMatrix();
        glTranslated(bolax, bolay, 0);
        desenhaBola();
        movimentoBola();
    glPopMatrix();

    glutPostRedisplay();

	glFlush(); //Habilita a execução de comandos OpenGL
}

void desenhaPlacar(int x, int placar) {
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
        if(x==10) {
            if(placar==1) {
                desenhaPlacar(0, 1);
                glPushMatrix();
                    glTranslated(-60, 0, 0);
                    desenhaPlacar(1, 1);
                glPopMatrix();
                printf("Jogador 1 venceu por %d a %d!\n", placar1, placar2);
            } else {
                desenhaPlacar(1, 2);
                glPushMatrix();
                    glTranslated(60, 0, 0);
                    desenhaPlacar(0, 2);
                glPopMatrix();
                printf("Jogador 2 venceu por %d a %d!\n", placar2, placar1);
            }
            exit(0);
        } else {
            if((x!=1) && (x!=4)) { //a
                glVertex2i(0, 60);
                glVertex2i(0, 75);
                glVertex2i(45, 75);
                glVertex2i(45, 60);
            }
            if((x!=5) && (x!=6)) {//b
                glVertex2i(30, 30);
                glVertex2i(30, 75);
                glVertex2i(45, 75);
                glVertex2i(45, 30);
            }
            if((x!=2)) { //c
                glVertex2i(30, 0);
                glVertex2i(30, 45);
                glVertex2i(45, 45);
                glVertex2i(45, 0);
            }
            if((x!=1) && (x!=4) && (x!=7)) {//d
                glVertex2i(0, 0);
                glVertex2i(0, 15);
                glVertex2i(45, 15);
                glVertex2i(45, 0);
            }
            if((x==0) || (x==2) || (x==6) || (x==8)) {//e
                glVertex2i(0, 0);
                glVertex2i(0, 45);
                glVertex2i(15, 45);
                glVertex2i(15, 0);
            }
            if((x!=1) && (x!=2) && (x!=3) && (x!=7)) {//f
                glVertex2i(0, 30);
                glVertex2i(0, 75);
                glVertex2i(15, 75);
                glVertex2i(15, 30);
            }
            if((x!=0) && (x!=1) && (x!=7)) {//g
                glVertex2i(0, 30);
                glVertex2i(0, 45);
                glVertex2i(45, 45);
                glVertex2i(45, 30);
            }
        }

    glEnd();
}

void movimentoBola() {
    switch(movimento) {
        case 0:
            bolax -= velocidadeBola;
            if(bolay < 550) bolay += velocidadeBola;
            else movimento = 2;
            if((bolax < 25) && (bolax > 20)) {
                if((bolay > y1) && (bolay < y1 + 100)) {
                    cont++;
                    movimento = 1;
                }
            }
        break;

        case 1:
            bolax += velocidadeBola;
            if(bolay < 550) bolay += velocidadeBola;
            else movimento = 3;
            if((bolax > 860) && (bolax < 865)) {
                if((bolay > y2) && (bolay < y2 + 100)) {
                    cont++;
                    movimento = 0;
                }
            }
        break;

        case 2:
            bolax -= velocidadeBola;
            if(bolay > 35) bolay -= velocidadeBola;
            else movimento = 0;
            if((bolax < 25) && (bolax > 20)) {
                if((bolay > y1) && (bolay < y1 + 100)) {
                    cont++;
                    movimento = 3;
                }
            }
        break;

        case 3:
            bolax += velocidadeBola;
            if(bolay > 35) bolay -= velocidadeBola;
            else movimento = 1;
            if((bolax > 860) && (bolax < 865)) {
                if((bolay > y2) && (bolay < y2 + 100)) {
                    cont++;
                    movimento = 2;
                }
            }
        break;
    }
    //printf("%f\n", bolax);
    if(bolax < -315) {
        placar2++;
        if(rand()%2==0) movimento == 1;
        else movimento == 3;
    }
    if(bolax > 1200) {
        placar1++;
        if(rand()%2==0) movimento == 0;
        else movimento == 2;
    }

    if((bolax < -15) || (bolax > 900)) y1 = y2 = 250;

    if((bolax < -315) || (bolax > 1200)) {
        bolax = 442;
        bolay = 300;
    }

    if(cont == 5) {
        velocidadeBola += 0.02;
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

int autorizaMovimento(float y, int direcao) {
    if ((direcao == 1) && (y < 465)) return true;
    else if ((direcao == 0) && (y > 35)) return true;
    else return false;
}

void maquina() {
    if(bolay > y2 + 50) {
        if(autorizaMovimento(y2, 1)) {
            y2 += velocidadePlataforma / 10;
        }
    } else {
        if(autorizaMovimento(y2, 0)) {
            y2 -= velocidadePlataforma / 10;
        }
    }
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
