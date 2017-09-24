#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include <math.h>

// Create a cube
void theCube( float c_x, float c_y, float c_z, GLfloat r, GLfloat g, GLfloat b){
    glPushMatrix();
    glColor3f(r, g ,b);
    glTranslatef(c_x, c_y, c_z);
    glutSolidCube(1.0);
    glPopMatrix();
}

// Draw grid
void drawGrid( ){
    int i;
    for (i=0; i<100; i++) {
        
        glPushMatrix();
        
        if (i<50) {
            glTranslated(0, 0, i);
        }
        
        if (i>=50) {
            glTranslated(i-50, 0, 0);
            glRotatef(-90, 0, 1, 0);
        }
        
        glBegin(GL_LINES);
        glColor3f(1, 1, 1); // white
        glLineWidth(1);
        glVertex3f(0, -0.1, 0);
        glVertex3f(49, -0.1, 0);
        
        glEnd();
        glPopMatrix();
    }
}

void drawA( ){
    int i;
    
    glutSolidCube(1.0); // center cube
    
    for (i=0; i<8; i++) {  // Draw left side
        glTranslatef(-0.2, -1, -0.2);
        glutSolidCube(1.0);
    }
    
    
    for (i=0; i<8; i++) { // Move the start point back to point ( 8, 8, 8 )
        glTranslatef(0.2, 1, 0.2);
    }
    
    
    for (i=0; i<8; i++) { // Draw right side
        glTranslatef(0.2, -1, 0.2);
        glutSolidCube(1.0);
    }
    
    
    for (i=0; i<4; i++) { // Move the start point to the center of right edge
        glTranslatef(-0.2, 0.7, -0.2);
    }
    
    
    for (i=0; i<8; i++) { // Draw middle line
        glTranslatef(-0.2, 0, -0.2);
        glutSolidCube(1.0);
    }
    
}

void drawPlus( ){
    glutSolidCube(1.0);
    
    glTranslatef(0, 0, 1); // right
    glutSolidCube(1.0);
    
    glTranslatef(0, 0, -2); // left
    glutSolidCube(1.0);
    
    glTranslatef(0, 1, 1); // up
    glutSolidCube(1.0);
    
    glTranslatef(0, -2, 0); // down
    glutSolidCube(1.0);
}

void draw3DCordinate( ){
    glTranslatef(-33,5,-85);
    glRotatef(-90,1,0,0);
    
    drawGrid(); // Draw the grid
    
    glRotatef(90, 1, 0, 0);
    drawGrid();
}

void drawExclamation( ){
    int i;
    
    glutSolidCube(1.0);
    
    for (i = 0; i < 6; i++) {
        glTranslatef(0, -1, 0);
        glutSolidCube(1.0);
    }
    
    glTranslatef(0, -2, 0);
    glutSolidCube(1.0);
}

// Display the geometry
void display( ){
    
    static float i = 0, j = 0;
    
    i += 1;
    if (i > 360) {
        i = 0;
    }
    
    j += 0.01;
    if (j > 1) {
        j = 0;
    }
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glTranslatef(42, -22, -22);
    glRotatef(30, 0, 1, 0);
    draw3DCordinate();
    
    /* Start drawing 'A' 
     * Center Point: ( 8, 8, 8 )
     */
    glPushMatrix();
    glColor3f(1, 0, 0); // red
    glTranslatef(23,8,23);
    glRotatef(i, 0, 1, 0);
    
    drawA( );
    glPopMatrix();
    
    /* Start drawing '+' 
     * Center Point: ( 10, 8, 10) 
     */
    glPushMatrix();
    glColor3f(1, 1, 0); // yellow
    glTranslatef(25, 8, 25);
    glRotatef(i, 0, 1, 0);
    drawPlus( );
    glPopMatrix();
    
    /* Start drawing ' ! ' */
    glPushMatrix();
    glColor3f(1, 0, 1); // purple
    glTranslatef(28, 8, 28);
    glRotatef(-10, 0, 0, 1);
    glScalef(j, j, j);
    drawExclamation( );
    glPopMatrix();
    
    glutSwapBuffers();
}

void init( ){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(35, 1.0f, 0.1f, 1000);
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_DEPTH_TEST);  // Enable the depth test. If not, the display of cones will be incorrect.
    glClearColor(0.1, 0.5, 0.1, 1); // green
    
}

void changeSize(int w, int h) {
    
    // If height equal to ' 0 ', let height equal to ' 1 '
    if (h == 0){
        h = 1;
    }
    float ratio = 1.0* w / h;
    
    glMatrixMode(GL_PROJECTION); // Set projetion mode
    glLoadIdentity();
    
    glViewport(0, 0, w, h);  // Set view port equal to the size of window
    
    gluPerspective(45, ratio, 1, 1000); // Set perspective proporities
    
    glMatrixMode(GL_MODELVIEW); // Set model view
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f); // Set view point
}

int main( int argc, char **argv){
    glutInit(&argc, argv); // GLUT environment initiation
    glutInitDisplayMode(GLUT_DOUBLE); // display mode initiation
    glutInitWindowSize(800, 600); // set the width and height of window
    glutCreateWindow("Homework One"); // display the window
    init();
    glutDisplayFunc(display); // register display function
    glutIdleFunc(display); // call display function when in spare time
    glutReshapeFunc(changeSize); // call changeSize function when the size of window changed
    glutMainLoop();
    return 0;
}
