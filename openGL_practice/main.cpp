#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

// Create a cube
void theCube( int c_x, int c_y, int c_z, GLfloat r, GLfloat g, GLfloat b){
    glPushMatrix();
    glColor3f(r, g ,b);
    glTranslatef(c_x, c_y, c_z);
    glutSolidCube(1.0);
    glPopMatrix();
}

// Draw grid
void drawGrid( ){
    int i;
    for (i=0; i<40; i++) {
        // save the status of matrix
        glPushMatrix();
        
        if (i<20) {
            glTranslated(0, 0, i);
        }
        
        if (i>=20) {
            glTranslated(i-20, 0, 0);
            glRotatef(-90, 0, 1, 0);
        }
        
        glBegin(GL_LINES);
        glColor3f(1, 1, 1);
        glLineWidth(1);
        glVertex3f(0, -0.1, 0);
        glVertex3f(19, -0.1, 0);
        
        glEnd();
        glPopMatrix();
    }
}

// Display the cube
void display( ){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-13,0,-45);
    glRotatef(40,1,1,0);
    
    drawGrid();
    theCube(8, 8, 8, 0, 1, 1);
    theCube(16, 0, 16, 1, 1, 1);
    glutSwapBuffers();
}

void init( ){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(35, 1.0f, 0.1f, 1000);
    glMatrixMode(GL_MODELVIEW);
    
    // Enable the depth test. If not, the display of cones will be incorrect.
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1, 0.1, 0.1, 1);
    
}

int main( int argc, char **argv){
    glutInit(&argc, argv); // GLUT 环境初始化
    glutInitDisplayMode(GLUT_DOUBLE); // 显示模式初始化
    glutInitWindowSize(800, 600); //定义窗口大小
    glutCreateWindow("Homework One"); //显示窗口
    init();
    glutDisplayFunc(display); //注册 OpenGL 绘图函数(一种特殊的调用方式,下同)
    glutMainLoop();
    return 0;
}
