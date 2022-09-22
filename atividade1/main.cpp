#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

float telaX = 800.0f, telaY = 600.0f, espessura = 1;
int r, g, b, y, clique=0;
int matriz[100][8], linha=0;

void desenhaLinha(){
    if(clique==4){
        matriz[linha-1][4] = (int)espessura;
        matriz[linha-1][5] = r;
        matriz[linha-1][6] = g;
        matriz[linha-1][7] = b;

        for(int i=0; i<linha; i++){
            glColor3ub(matriz[i][5], matriz[i][6], matriz[i][7]);
            glLineWidth(matriz[i][4]);
            printf("var espessura: %d - espessura da linha %d: %d\n", espessura, i, matriz[i][4]);
            glBegin(GL_LINES);
                glVertex2i(matriz[i][0], matriz[i][1]);
                glVertex2i(matriz[i][2], matriz[i][3]);
            glEnd();
        }

    }
}

//Função callback para desenho
void desenha(void) {
    //Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Define os limites dos eixos x e y
    //Argumentos da função: void gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
    gluOrtho2D (0.0f, telaX, 0.0f, telaY);

	//Limpa todos os pixels com a cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

    desenhaLinha();

	//Habilita a execução de comandos OpenGL
	glFlush();
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case 'a':
            glClear(GL_COLOR_BUFFER_BIT);
            glFlush();
            r = g = b = linha = 0;
            espessura = 1;
            printf("Limpo\n");
            break;
        case '+':
            if(espessura < 33) espessura++;
            printf("Espessura: %.0f\n", espessura);
            break;
        case '-':
            if(espessura > 1) espessura--;
            printf("Espessura: %.0f\n", espessura);
            break;
        case '1':
            r = 255;
            g = 0;
            b = 0;
            break;
        case '2':
            r = 0;
            g = 255;
            b = 0;
            break;
        case '3':
            r = 0;
            g = 0;
            b = 255;
            break;
        case '4':
            r = 0;
            g = 0;
            b = 0;
            break;
        case '5':
            r = 255;
            g = 255;
            b = 0;
            break;
        case '6':
            r = 255;
            g = 0;
            b = 150;
            break;
        case '7':
            r = 255;
            g = 120;
            b = 0;
            break;
        case '8':
            r = 150;
            g = 150;
            b = 150;
            break;
        case '9':
            r = 100;
            g = 50;
            b = 0;
            break;
    }
}

/*void specialKeyboard(int key, int x, int y){
    if (key == GLUT_KEY_LEFT){
        printf("Tecla direcional ESQUERDA pressionada\n");
    }

    if (key == GLUT_KEY_RIGHT){
        printf("Tecla direcional DIREITA pressionada\n");
    }
}*/

void mouse(int button, int state, int x, int y){
    y = telaY - y;

    if(clique==4) clique=0;

    if (button == GLUT_LEFT_BUTTON){
        if (state == GLUT_UP){
            printf("Coordenadas: x: %d | y: %d\n", x, y);
            matriz[linha][clique] = x;
            matriz[linha][clique+1] = y;
            clique+=2;

            if(clique==4){
                glutPostRedisplay();
                linha++;
            }
        }
    }
}


//Inicializa parâmetros
void init (void){
    // Configura a cor de fundo
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

//Principal
int main(void)
{
    //Tipo de janela (single-buffered) e cores utilizados
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	//Configura o tamanho da janela
	glutInitWindowSize (telaX, telaY);

	//Configura a posição inicial da janela
	glutInitWindowPosition (283, 50);

	//Configura a janela
	glutCreateWindow("Lines");

	//Chama a função desenha
	glutDisplayFunc(desenha);

	//Callback de teclas normais
	glutKeyboardFunc(keyboard);

	//Callback de teclas especiais
	//glutSpecialFunc(specialKeyboard);

	//Callback do Mouse
	glutMouseFunc(mouse);

	//Inicializa o programa
	init();

	//Habilita o loop (máquina de estados)
	glutMainLoop();
}
