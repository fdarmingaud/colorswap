/*
 * colorswap.c -- Compiler avec les options -lglut -lGL -lGLU :
 * cc colorswap.c -lglut -lGL -lGLU && ./a.out
 * 
 * Placer le pointeur dans la fenêtre, puis pressez :
 * R G ou B pour changer la couleur du fond
 * r g ou b pour changer celle de l'encre
 * q pour quitter.
 * 
 * Ce programme a été écrit sous OpenSuSE avec Geany
 * depuis le Sony Satellite qui boote très bien en Linux sur SSD
 * à condition qu'on inhibe le sikioureboute et qu'on donne la 
 * priorité de boute à l'USB, ce qui bizarrement doit être fait depuis
 * Windows, en tout cas chez moi. 
 * 
 */

#include <GL/glut.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> 

#define N 10

int puceau=1;

// Nous avons besoin d'associer une fonction ("callback") à la fenêtre.
// C'est elle qui sera chargée de tout redessiner si nous la redimensionnons

GLfloat red, green, blue, RED, GREEN, BLUE, ALPHA;
GLint point[N][2];
int k,l;
char alphabet[] = "P ";
void *currentfont;

void setFont(void *font)
{
 currentfont=font;                      // Set the currentfont to the font
}

void drawstring(float x,float y,float z,char *string)
{
 char *c;
 glRasterPos3f(x,y,z);
 for(c=string;*c!='\0';c++)
 { glColor3f(0.0,0.0,0.0);
  glutBitmapCharacter(currentfont,*c);
 }
}

void displayCB(void)	
{

  glClear(GL_COLOR_BUFFER_BIT);		/* Mettre l'écran à "blanc" */
  if (puceau) { glColor3f(red=0, green=0, blue=1.0);   /* Fond bleu la première fois */
	        puceau=0;}
  
  // Nous définissons maintenant un polygone fermé de trois points :
  glPointSize(10.0f);
  glBegin(GL_POINTS);			// "Je commence un polygone"
  for (k=0; k<N; ++k) glVertex2i(point[k][0],point[k][1]);		       // Coordonnées des trois points
  glEnd();				// "J'ai défini le polygone"
  drawstring (10,10,0,"blabla");
  for (k=0; k<N; ++k) { alphabet[1]='0'+k;
                        drawstring (point[k][0]+5,point[k][1]+5,0, alphabet); 
                      }
  glFlush();				// "Maintenant, DESSINER le polygone"
}

void keyCB(unsigned char key, int x, int y)	/* action sur caractère pressé */
{
  if( key == 'q' ) exit(0);  			// q => "quitter"
  if( key == '+') { red *=1.1; green*=1.1; blue*=1.1;}
  if( key == '-') { red /=1.1; green/=1.1; blue/=1.1;}
 
  switch(key)
{ case '0' ... '9' : k=key - '0';	// Cavalier, mais garanti par le standard	
                     if (k<N) {point[k][0]=rand()%580;
                               point[k][1]=rand()%580;
                              }
}
 
  // Majuscule = couleur du fond

  if (isupper(key)) {RED=0; GREEN=0; BLUE=0; ALPHA=0.5;}
  switch(key)
  {
   case 'R' : RED=1; break;
   case 'G' : GREEN=1; break;
   case 'B' : BLUE=1; break;
   case 'Y' : RED=1; GREEN=1; break;
  }
  glClearColor(RED, GREEN, BLUE, ALPHA);

  // Minuscule = couleur de l'encre

  if (islower(key)) {red= 0; green=0; blue=0;}
  switch(key)
  {
	case 'r' : red=0.7; break;
        case 'g' : green=0.7; break;
        case 'b' : blue=0.7; break;
        case 'y' : red=0.7; green=0.7; break;
        case 'p' : red=0.7; blue=0.7; break;
        case 'c' : blue=0.7; green=0.7; break; 
        case 'w' : red=0.7; green=0.7; blue=0.7; break;
  }
  glColor3f(red,green,blue);
  displayCB();		// On affiche
}


int main(int argc, char *argv[])
{
  int win;	// Identificateur de fenêtre. Mais il n'y en aura ici qu'une.
// Initialisation

for (k=0; k<N; ++k)
    { point[k][0]= rand()%500;
      point[k][1]= rand()%500;
  }

  glutInit(&argc, argv);		/* initialise GLUT */

  glutInitDisplayMode(GLUT_RGB);	// On travaille en RGB
  glutInitWindowSize(600,600);		// Fenêtre 500 de large 400 de haut

  win = glutCreateWindow("Frappez r/g/b/y/R/G/B/Y/W/+/-/1/2/3/q");	/* create window */

  // Les ordres sont maintenant exécutés dans la fenêtre "win"

  glClearColor(RED=0.9, GREEN=0.9, BLUE=0.2, ALPHA=0); 	// Jaune pisseux
  gluOrtho2D(0,600,0,600);		// On travaillera dans ces coordonnées
  glutDisplayFunc(displayCB);		// Callback associé à la fenêtre
  glutKeyboardFunc(keyCB);		// Callback associé au clavier
  setFont(GLUT_BITMAP_HELVETICA_18);

  glutMainLoop();			/* Et on part dans la boucle infinie... */

  /* execution never reaches this point */

  return 0;
}
