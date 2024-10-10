#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

int FlatShaded = 0;	int Wireframed = 0;
//flatshading�� Wireframe�� ��۸��ϱ� ���� �ο� ����

int ViewX = 0, ViewY = 0;
// ���콺 �����ӿ� ���� ������ �ٲٱ� ���� ���� 

void InitLight() {
	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 15.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_position[] = { -3, 6, 3.0, 0.0 };

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void MyMouseMove(GLint X, GLint Y) {
	// ���콺 ������ X,Y�� ���� ������ ViewX, ViewY�� �Ҵ�
	ViewX = X - 200;
	ViewY = Y - 200;
	glutPostRedisplay();
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q': case 'Q': case '\033':
		exit(0);
		break;
	case 's':
		if (FlatShaded) {
			FlatShaded = 0;
			glShadeModel(GL_SMOOTH);
		}
		else {
			FlatShaded = 1;
			glShadeModel(GL_FLAT);
		}
		glutPostRedisplay();
		break;
	case 'w':
		// Wireframe ��� ���
		if (Wireframed) {
			Wireframed = 0;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else {
			Wireframed = 1;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		glutPostRedisplay();
		break;
	}
}

void DrawTable() {
	// Ź�� 
	glPushMatrix();
	glTranslatef(0.0, -0.5, 0.0);
	glScalef(2.0, 0.1, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
}


void DrawObjectsOnTable() {
	//  ��
	glPushMatrix();
	glTranslatef(-0.5, -0.30, 0.0);
	glutSolidSphere(0.2, 20, 20);
	glPopMatrix();

	// ������
	glPushMatrix();
	glTranslatef(0, -0.30, 0.0);
	glutSolidTeapot(0.2);
	glPopMatrix();

	// ����
	glPushMatrix();
	glTranslatef(0.5, -0.45, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.2, 0.5, 20, 20);
	glPopMatrix();
}


void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 1.0, 1.0, 0.0);
	// ���콺�� �����ӿ� ���� ������ ��ȭ��Ű����
	// MyMouseMove �Լ����� �ԷµǴ� ��ȭ���� �����Ͽ�
	// glLookAt ��ɾ� �Ķ���͸� �����غ� �� (���� ����)
	// �Ʒ��� �ʿ��� ��ü ����� ����� ������ �� 
	gluLookAt(0.0 + (ViewX / 100.0), 0.0 + (ViewY / 100.0), 1.0,
		0.0, 0.0, -1.0,    // ���� ����
		0.0, 1.0, 0.0);    // ī�޶� ���� ����

	// Ź�� �׸���
	DrawTable();

	// Ź�� ���� ��ü ��ġ
	DrawObjectsOnTable();
	glFlush();
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glOrtho(-1.5, 1.5, -1.5, 1.5, -1.5, 1.5);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");

	glClearColor(0.4, 0.4, 0.4, 0.0);
	InitLight();
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMotionFunc(MyMouseMove);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
}
