#define GLUT_DISABLE_ATEXIT_HACK

/*
======== Teste OpenGL ==================
Nairon Neri Silva
Versão 1.0
Programa teste da configuração do GLUT
Desenha um quadrado vermelho na tela
========================================
*/

#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

float velocidade=1;
float x1=0, y1=0, x2=0, y2=0;
int direcao1=1, direcao2=1;

void desenhaPlataforma();
int autorizaMovimento(float x, float y, int direcao);
void desenhaCenario();



//Função callback para desenho
void desenha(void)
{
    //Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Define os limites dos eixos x e y
    //Argumentos da função: void gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
    gluOrtho2D (0.0f, 900.0f, 0.0f, 600.0f);

	//Limpa todos os pixels com a cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

	desenhaCenario();

	glPushMatrix();
        glTranslated(10, 250, 0);
        desenhaPlataforma();
	glPopMatrix();

	glPushMatrix();
        glTranslated(875, 250, 0);
        desenhaPlataforma();
    glPopMatrix();

    glutPostRedisplay();

	//Habilita a execução de comandos OpenGL
	glFlush();
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

int autorizaMovimento(float x, float y, int direcao){
    printf("X: %f / Y: %f\n", x1, y1);

    if ((direcao == 1) && (y < 450)){
        if ((x > 250) && (x < 350) && (y < 50)){
            return false;
        }
        return true;
    }else if ((direcao == 2) && (x > 0)){
        if ((x > 250) && (x < 350) && (y < 50)){
            return false;
        }
        return true;
    }else if ((direcao == 3) && (y < 450)){
        return true;
    }else if ((direcao == 4) && (y > 0)){
        return true;
    }else if ((direcao == 5) && (x <= 450) && (y <= 450)){
        return true;
    }else if ((direcao == 6) && (x >= 0) && (y >= 0)){
        return true;
    }else if ((direcao == 7) && (x <= 450) && (y >= 0)){
        return true;
    }else if ((direcao == 8) && (x >= 0) && (y <= 450)){
        return true;
    }else{
        return false;
    }
}

void desenhaPlataforma(){
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
        glVertex2i(0, 0);
        glVertex2i(0, 100);
        glVertex2i(15, 100);
        glVertex2i(15, 0);
    glEnd();
}

void specialKeyboard(int key, int x, int y){
    if ((key == GLUT_KEY_RIGHT) && autorizaMovimento(x1, y1, 1)){
        x1 += velocidade;
    }

    if ((key == GLUT_KEY_LEFT) && autorizaMovimento(x1, y1, 2)){
        x1 -= velocidade;
    }

    if ((key == GLUT_KEY_UP) && autorizaMovimento(x1, y1, 3)){
        y1 += velocidade;
    }

    if ((key == GLUT_KEY_DOWN) && autorizaMovimento(x1, y1, 4)){
        y1 -= velocidade;
    }
}

//Inicializa parâmetros
void init (void)
{
    // Configura a cor de fundo como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    direcao1 = rand()%8+1;
    direcao2 = rand()%8+1;
}

//Principal
int main(void)
{
    srand(time(NULL));
    //Tipo de janela (single-buffered) e cores utilizados
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	//Configura o tamanho da janela
	glutInitWindowSize (900, 600);

	//Configura a posição inicial da janela
	glutInitWindowPosition (100, 100);

	//Configura a janela
	glutCreateWindow("Teste do OpenGL");

	//Callback de teclas especiais
	glutSpecialFunc(specialKeyboard);

	//Chama a função desenha
	glutDisplayFunc(desenha);

	//Inicializa o programa
	init();

	//Habilita o loop (máquina de estados)
	glutMainLoop();
}
