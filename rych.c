#include <GL/glut.h>

// Posição inicial do Sol
float sunPositionX = 0.0f;
float sunPositionY = 0.0f;
float sunPositionZ = 0.0f;

// Variáveis para controlar o arraste do Sol
int isDragging = 0;
int dragStartX = 0;
int dragStartY = 0;

// Ângulo de rotação dos planetas
float rotationAngleMars = 0.0f;
float rotationAngleNeptune = 0.0f;
float rotationAngleEarth = 0.0f;

// Escala dos planetas
float scale = 1.0f;

// Raio da órbita da Terra
float orbitRadiusEarth = 2.0f;

void init() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Cor de fundo preta

  // Configurações de iluminação
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  GLfloat light_position[] = {0.0f, 0.0f, 10.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  // Configuração de projeção
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
}

void drawSun() {
  glColor3f(1.0f, 0.7f, 0.0f); // Cor amarela para o Sol
  glTranslatef(sunPositionX, sunPositionY,
               sunPositionZ);            // Translação para a posição do Sol
  glutSolidSphere(0.8f * scale, 50, 50); // Desenha a esfera do Sol
}

void drawEarth() {
  glColor3f(0.0f, 0.7f, 0.0f); // Cor verde para a Terra
  glPushMatrix();
  glRotatef(rotationAngleEarth, 0.0f, 1.0f, 0.0f); // Rotação em torno do eixo y
  glTranslatef(orbitRadiusEarth, 0.0f,
               0.0f);                    // Translação para a órbita da Terra
  glutSolidSphere(0.5f * scale, 30, 30); // Desenha a esfera da Terra
  glPopMatrix();
}

void drawMars() {
  glColor3f(0.7f, 0.3f, 0.1f); // Cor vermelha para Marte
  glPushMatrix();
  glRotatef(rotationAngleMars, 0.0f, 1.0f, 0.0f); // Rotação em torno do eixo y
  glTranslatef(1.5f, 0.0f, 0.0f); // Translação para a posição de Marte
  glutSolidSphere(0.3f * scale, 30, 30); // Desenha a esfera de Marte
  glPopMatrix();
}

void drawNeptune() {
  glColor3f(0.2f, 0.4f, 0.8f); // Cor azul para Netuno
  glPushMatrix();
  glRotatef(rotationAngleNeptune, 0.0f, 1.0f,
            0.0f);                // Rotação em torno do eixo y
  glTranslatef(2.5f, 0.0f, 0.0f); // Translação para a posição de Netuno
  glutSolidSphere(0.4f * scale, 30, 30); // Desenha a esfera de Netuno
  glPopMatrix();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  gluLookAt(5.0f, 5.0f, 5.0f,  // Posição da câmera
            0.0f, 0.0f, 0.0f,  // Ponto de referência
            0.0f, 1.0f, 0.0f); // Vetor "up"

  drawSun();
  drawEarth();
  drawMars();
  drawNeptune();

  glutSwapBuffers();
}

void update(int value) {
  rotationAngleMars += 2.0f;    // Incrementa o ângulo de rotação de Marte
  rotationAngleNeptune += 1.0f; // Incrementa o ângulo de rotação de Netuno
  rotationAngleEarth +=
      0.5f; // Incrementa o ângulo de rotação da Terra com uma velocidade menor

  if (rotationAngleMars > 360)
    rotationAngleMars -= 360;

  if (rotationAngleNeptune > 360)
    rotationAngleNeptune -= 360;

  if (rotationAngleEarth > 360)
    rotationAngleEarth -= 360;

  glutPostRedisplay();          // Redesenha a cena
  glutTimerFunc(25, update, 0); // Chama a função de atualização a cada 25ms
}

void mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    // Inicia o arraste do Sol
    isDragging = 1;
    dragStartX = x;
    dragStartY = y;
  } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    // Encerra o arraste do Sol
    isDragging = 0;
  }
}

void motion(int x, int y) {
  if (isDragging) {
    // Calcula a diferença de posição do arraste
    int deltaX = x - dragStartX;
    int deltaY = y - dragStartY;

    // Verifica a direção do movimento do mouse
    if (deltaY > 0) {
      // Movimento para cima (girar no eixo X)
      sunPositionZ -= 0.01f;
    } else if (deltaY < 0) {
      // Movimento para baixo (girar no eixo X)
      sunPositionZ += 0.01f;
    }

    // Atualiza a posição do Sol
    sunPositionX += (float)deltaX / 800.0f;
    sunPositionY -= (float)deltaY / 600.0f;

    // Atualiza a posição inicial do arraste
    dragStartX = x;
    dragStartY = y;

    glutPostRedisplay(); // Redesenha a cena
  }
}

void mouseWheel(int wheel, int direction, int x, int y) {
  if (direction > 0) {
    // Aproxima a câmera
    glTranslatef(0.0f, 0.0f, 0.1f);
  } else {
    // Afasta a câmera
    glTranslatef(0.0f, 0.0f, -0.1f);
  }

  glutPostRedisplay(); // Redesenha a cena
}

int main(int argc, char **argv) {
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
