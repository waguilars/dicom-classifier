/* pgm file IO headerfile ------ mypgm.h */

/* Constant declaration */
#define MAX_IMAGESIZE  5024
#define MAX_BRIGHTNESS  255 /* Maximum gray level */
#define GRAYLEVEL       256 /* No. of gray levels */
#define MAX_FILENAME    256 /* Filename length limit */
#define MAX_BUFFERSIZE  256

/* Global constant declaration */
/* Image storage arrays */
unsigned char image1[MAX_IMAGESIZE][MAX_IMAGESIZE],
  image2[MAX_IMAGESIZE][MAX_IMAGESIZE];
int x_size1, y_size1, /* width & height of image1*/
  x_size2, y_size2; /* width & height of image2 */

/* Prototype declaration of functions */
void load_image_data( ); /* image input */
void save_image_data( ); /* image output*/
void load_image_file(char *); /* image input */
void save_image_file(char *); /* image output*/


/* Main body of functions */

void load_image_data( )
/* Input of header & body information of pgm file */
/* for image1[ ][ ]�Cx_size1�Cy_size1 */
{
  char file_name[MAX_FILENAME];
  char buffer[MAX_BUFFERSIZE];
  FILE *fp; /* File pointer */
  int max_gray; /* Maximum gray level */
  int x, y; /* Loop variable */

  /* Input file open */
  printf("\n-----------------------------------------------------\n");
  printf("UNIVERSIDAD POLITECNICA SALESIANA - COMPUTACION PARALELA \n Filtro de Otsu \n Jonathan Barrionuevo - Daniela Campoverde - Andres Loachamin\n");
  printf("Carga de Archivo .pgm \n");
  printf("-----------------------------------------------------\n\n");
  printf("     Solo se aceptan archivos (Portable Gray Map .pgm)\n\n");
  printf("Ingrese el nombre del Archivo (*.pgm) : ");
  scanf("%s", file_name);
  fp = fopen(file_name, "rb");
  if (NULL == fp) {
    printf("     Error! el archivo no existe\n\n");
    exit(1);
  }
  /* Check of file-type ---P5 */
  fgets(buffer, MAX_BUFFERSIZE, fp);
  if (buffer[0] != 'P' || buffer[1] != '5') {
    printf("    error de formato no es del tipo, P5!\n\n");
    exit(1);
  }
  /* input of x_size1, y_size1 */
  x_size1 = 0;
  y_size1 = 0;
  while (x_size1 == 0 || y_size1 == 0) {
    fgets(buffer, MAX_BUFFERSIZE, fp);
    if (buffer[0] != '#') {
      sscanf(buffer, "%d %d", &x_size1, &y_size1);
    }
  }
  /* input of max_gray */
  max_gray = 0;
  while (max_gray == 0) {
    fgets(buffer, MAX_BUFFERSIZE, fp);
    if (buffer[0] != '#') {
      sscanf(buffer, "%d", &max_gray);
    }
  }
  /* Display of parameters */
  printf("\n     Ancho de la Imagen = %d, Altura de la Imagen = %d\n", x_size1, y_size1);
  printf("     Nivel de Gris Maximo = %d\n\n",max_gray);
  if (x_size1 > MAX_IMAGESIZE || y_size1 > MAX_IMAGESIZE) {
    printf("     Excede el tamanio de imagen permitido %d x %d\n\n", 
	   MAX_IMAGESIZE, MAX_IMAGESIZE);
    printf("     Por favor utilice imagenes mas pequenias!\n\n");
    exit(1);
  }
  if (max_gray != MAX_BRIGHTNESS) {
    printf("     Valor de gris maximo es invalido!\n\n");
    exit(1);
  }
  /* Input of image data*/
  for (y = 0; y < y_size1; y++) {
    for (x = 0; x < x_size1; x++) {
      image1[y][x] = (unsigned char)fgetc(fp);
    }
  }
  printf("-----Carga de Imagen Correcta----\n\n");
  printf("-----------------------------------------------------\n\n");
  fclose(fp);
}

void save_image_data( )
/* Output of image2[ ][ ], x_size2, y_size2 in pgm format*/
     
{
  char file_name[MAX_FILENAME];
  FILE *fp; /* File pointer */
  int x, y; /* Loop variable */
  
  /* Output file open */
  printf("-----------------------------------------------------\n");
  printf("Fin del Procesado de la Imagen");
  printf("-----------------------------------------------------\n\n");
  printf("Ingrese nombre del Archivo? (*.pgm) : ");
  scanf("%s",file_name);
  fp = fopen(file_name, "wb");
  /* output of pgm file header information */
  fputs("P5\n", fp);
  fputs("# Created by Image Processing\n", fp);
  fprintf(fp, "%d %d\n", x_size2, y_size2);
  fprintf(fp, "%d\n", MAX_BRIGHTNESS);
  /* Output of image data */
  for (y = 0; y < y_size2; y++) {
    for (x = 0; x < x_size2; x++) {
      fputc(image2[y][x], fp);
    }
  }
  printf("\n-----Archivo de Imagen generado Correctamente-----\n\n");
  printf("-----------------------------------------------------\n\n");
  fclose(fp);
}

void load_image_file(char *filename)
/* Input of header & body information of pgm file */
/* for image1[ ][ ]�Cx_size1�Cy_size1 */
{
  char buffer[MAX_BUFFERSIZE];
  FILE *fp; /* File pointer */
  int max_gray; /* Maximum gray level */
  int x, y; /* Loop variable */
  
  /* Input file open */
  fp = fopen(filename, "rb");
  if (NULL == fp) {
    printf("    El Archivo no Existe!\n\n");
    exit(1);
  }
  /* Check of file-type ---P5 */
  fgets(buffer, MAX_BUFFERSIZE, fp);
  if (buffer[0] != 'P' || buffer[1] != '5') {
    printf("     Formato de Archivo Incorrecto, no es P5!\n\n");
    exit(1);
  }
  /* input of x_size1, y_size1 */
  x_size1 = 0;
  y_size1 = 0;
  while (x_size1 == 0 || y_size1 == 0) {
    fgets(buffer, MAX_BUFFERSIZE, fp);
    if (buffer[0] != '#') {
      sscanf(buffer, "%d %d", &x_size1, &y_size1);
    }
  }
  /* input of max_gray */
  max_gray = 0;
  while (max_gray == 0) {
    fgets(buffer, MAX_BUFFERSIZE, fp);
    if (buffer[0] != '#') {
      sscanf(buffer, "%d", &max_gray);
    }
  }
  if (x_size1 > MAX_IMAGESIZE || y_size1 > MAX_IMAGESIZE) {
    printf("     Excede tamanio de imagen %d x %d\n\n", 
	   MAX_IMAGESIZE, MAX_IMAGESIZE);
    printf("     Utilice imagenes mas pequenias!\n\n");
    exit(1);
  }
  if (max_gray != MAX_BRIGHTNESS) {
    printf("     Valor de grises maximo es invalido!\n\n");
    exit(1);
  }
  /* Input of image data*/
  for (y = 0; y < y_size1; y++) {
    for (x = 0; x < x_size1; x++) {
      image1[y][x] = (unsigned char)fgetc(fp);
    }
  }
  fclose(fp);
}

void save_image_file(char *filename)
/* Output of image2[ ][ ], x_size2, y_size2 */ 
/* into pgm file with header & body information */
{
  FILE *fp; /* File pointer */
  int x, y; /* Loop variable */
  
  fp = fopen(filename, "wb");
  /* output of pgm file header information */
  fputs("P5\n", fp);
  fputs("# Created by Image Processing\n", fp);
  fprintf(fp, "%d %d\n", x_size2, y_size2);
  fprintf(fp, "%d\n", MAX_BRIGHTNESS);
  /* Output of image data */
  for (y = 0; y < y_size2; y++) {
    for (x = 0; x < x_size2; x++) {
      fputc(image2[y][x], fp);
    }
  }
  fclose(fp);
}

