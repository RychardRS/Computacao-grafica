#include <GL/glut.h>

// Posição inicial do Sol
float sunPositionX = 0.0f;
float sunPositionY = 0.0f;

// Variáveis para controlar o arraste do Sol
int isDragging = 0;
int dragStartX = 0;
int dragStartY = 0;

// Ângulo de rotação dos planetas
float rotationAngleMars = 0.0f;
float rotationAngleNeptune = 0.0f;

// Ângulo de rotação tridimensional
float rotationAngleX = 0.0f;
float rotationAngleY = 0.0f;

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Cor de fundo preta
}

void drawSun()
{
    glColor3f(1.0f, 0.7f, 0.0f); // Cor amarela para o Sol
    glTranslatef(sunPositionX, sunPositionY, 0.0f); // Translação para a posição do Sol
    glutSolidSphere(0.8f, 50, 50); // Desenha a esfera do Sol
}

void drawMars()
{
    glColor3f(0.7f, 0.3f, 0.1f); // Cor vermelha para Marte
    glTranslatef(1.5f, 0.0f, 0.0f); // Translação para a posição de Marte
    glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f); // Rotação em torno do eixo X
    glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f); // Rotação em torno do eixo Y
    glutSolidSphere(0.3f, 30, 30); // Desenha a esfera de Marte
}

void drawNeptune()
{
    glColor3f(0.2f, 0.4f, 0.8f); // Cor azul para Netuno
    glTranslatef(2.5f, 0.0f, 0.0f); // Translação para a posição de Netuno
    glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f); // Rotação em torno do eixo X
    glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f); // Rotação em torno do eixo Y
    glutSolidSphere(0.4f, 30, 30); // Desenha a esfera de Netuno
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawSun();
    drawMars();
    drawNeptune();

    glutSwapBuffers();
}

void update(int value)
{
    rotationAngleMars += 2.0f; // Incrementa o ângulo de rotação de Marte
    rotationAngleNeptune += 1.0f; // Incrementa o ângulo de rotação de Netuno

    if (rotationAngleMars > 360)
        rotationAngleMars -= 360;

    if (rotationAngleNeptune > 360)
        rotationAngleNeptune -= 360;

    glutPostRedisplay(); // Redesenha a cena
    glutTimerFunc(25, update, 0); // Chama a função de atualização a cada 25ms
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Inicia o arraste do Sol
        isDragging = 1;
        dragStartX = x;
        dragStartY = y;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        // Encerra o arraste do Sol
        isDragging = 0;
    }
}

void motion(int x, int y)
{
    if (isDragging)
    {
        int deltaX = x - dragStartX;
        int deltaY = y - dragStartY;

        rotationAngleX += deltaY; // Atualiza o ângulo de rotação em torno do eixo X
        rotationAngleY += deltaX; // Atualiza o ângulo de rotação em torno do eixo Y

        dragStartX = x;
        dragStartY = y;

        glutPostRedisplay();
    }
}

void mouseWheel(int wheel, int direction, int x, int y)
{
    if (direction > 0)
    {
        // Aumenta a escala dos planetas
        glScalef(1.1f, 1.1f, 1.1f);
    }
    else
    {
        // Diminui a escala dos planetas
        glScalef(0.9f, 0.9f, 0.9f);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sistema Solar");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMouseWheelFunc(mouseWheel); // Captura eventos da roda do mouse

    glutMainLoop();

    return 0;
}
