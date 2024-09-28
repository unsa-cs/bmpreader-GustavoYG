#include "bmp.h"
#include <GL/glut.h>
#include <stdio.h>

BMPImage *image;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  if (image) {
    drawBMP(image);
  }
  glFlush();
}
void ConvertirBN(BMPImage *image){
  for (unsigned int i = 0; i < image->width * image->height * 3; i += 3) {
    unsigned char r = image->data[i];
    unsigned char g = image->data[i + 1];
    unsigned char b = image->data[i + 2];
    // Promedio para convertir a escala de grises
    unsigned char gray = (r + g + b) / 3;
    // Asignar el mismo valor a los tres componentes RGB
    image->data[i] = gray;
    image->data[i + 1] = gray;
    image->data[i + 2] = gray;
}
int main() {
  char filename[256];

  // Pedir al usuario el nombre del archivo BMP
  printf("Ingrese el nombre del archivo BMP (con extensión): ");
  scanf("%255s", filename);

  image = readBMP(filename);
  if (!image) return 1;

  // Inicializar GLUT
  /*
  int argc = 1; // Necesario para evitar problemas con glutInit
  char *argv[1] = { "" }; // Argumento vacío para GLUT
  glutInit(&argc, argv);
  */
  if (argc < 2) {
    fprintf(stderr, "Uso: %s <archivo BMP>\n", argv[0]);
    return 1;
  }
  image = readBMP(argv[1]);
  if (!image) {
    fprintf(stderr, "Error: No se pudo cargar el archivo BMP.\n");
    return 1;
  }
  //convertirBN
  // Verificar si se pasó la opción de blanco y negro
  if (argc > 2 && strcmp(argv[2], "--bw") == 0) {
    ConvertirBN(image);
  }
  glutInit(&arc, arv);
  // Establecer el modo de visualización
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(image->width, image->height);
  glutCreateWindow("Visualizador de BMP");

  glLoadIdentity();
  glOrtho(0, image->width, image->height, 0, -1, 1);

  glutDisplayFunc(display);
  glutMainLoop();

  freeBMP(image);
  return 0;
}
