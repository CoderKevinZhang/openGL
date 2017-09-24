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
        // save the status of matrix
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
    
    // Draw left side
    for (i=0; i<8; i++) {
        glTranslatef(-0.2, -1, -0.2);
        glutSolidCube(1.0);
    }
    
    // Move the start point back to point ( 8, 8, 8 )
    for (i=0; i<8; i++) {
        glTranslatef(0.2, 1, 0.2);
    }
    
    // Draw right side
    for (i=0; i<8; i++) {
        glTranslatef(0.2, -1, 0.2);
        glutSolidCube(1.0);
    }
    
    // Move the start point to the center of right edge
    for (i=0; i<4; i++) {
        glTranslatef(-0.2, 0.7, -0.2);
    }
    
    // Draw middle line
    for (i=0; i<8; i++) {
        glTranslatef(-0.2, 0, -0.2);
        glutSolidCube(1.0);
    }
    
}

void drawPlus( ){
    glutSolidCube(1.0);
    
    glTranslatef(0, 0, 1);
    glutSolidCube(1.0);
    
    glTranslatef(0, 0, -2);
    glutSolidCube(1.0);
    
    glTranslatef(0, 1, 1);
    glutSolidCube(1.0);
    
    glTranslatef(0, -2, 0);
    glutSolidCube(1.0);
}

void draw3DCordinate( ){
    glTranslatef(-33,5,-85);
    glRotatef(-90,1,0,0);
    // Draw the grid
    drawGrid();
    
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

// Display the cube
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
    
    // Enable the depth test. If not, the display of cones will be incorrect.
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1, 0.5, 0.1, 1); // green
    
}

void changeSize(int w, int h) {
    
    // 防止除数即高度为0
    // (你可以设置窗口宽度为0).
    if (h == 0)
        h = 1;
    float ratio = 1.0* w / h;
    
    // 单位化投影矩阵。
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // 设置视口大小为整个窗口大小
    glViewport(0, 0, w, h);
    
    // 设置正确的投影矩阵
    gluPerspective(45, ratio, 1, 1000);
    //下面是设置模型视图矩阵
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f);//设置观测点
}

int main( int argc, char **argv){
    glutInit(&argc, argv); // GLUT 环境初始化
    glutInitDisplayMode(GLUT_DOUBLE); // 显示模式初始化
    glutInitWindowSize(800, 600); //定义窗口大小
    glutCreateWindow("Homework One"); //显示窗口
    init();
    glutDisplayFunc(display); //注册 OpenGL 绘图函数(一种特殊的调用方式,下同)
    glutIdleFunc(display); //指定程序空闲时调用函数
    glutReshapeFunc(changeSize); //指定窗口形状变化时的回调函数
    glutMainLoop();
    return 0;
}
