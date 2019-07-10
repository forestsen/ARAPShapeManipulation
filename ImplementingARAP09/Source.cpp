#include <iostream>

#include <GL/glut.h>
#include <gl/glu.h>

#include "Mesh.h"

using namespace std;
using namespace Eigen;
using namespace sen;

Mesh mesh;
int selected_id = -1;

void ScreenToOpenGL(const Vector2f &screen_coord, Vector3f &opengl_coord)
{
	GLint viewPort[4];
	GLdouble modelView[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;
	glPushMatrix();
	glLoadIdentity();
	glScalef(0.01f, 0.01f, 1.0f);
	glGetIntegerv(GL_VIEWPORT, viewPort);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glPopMatrix();

	winX = screen_coord(0);
	winY = viewPort[3] - screen_coord[1];
	glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, 0, modelView, projection, viewPort, &posX, &posY, &posZ);
	opengl_coord[0] = (float)posX;
	opengl_coord[1] = (float)posY;
	opengl_coord[2] = 0.0f;
}
void OpenGLToScreen(const Vector3f &opengl_coord, Vector2f &screen_coord)
{
	GLint viewPort[4];
	GLdouble modelView[16];
	GLdouble projection[16];
	GLdouble winX, winY, winZ;
	GLfloat posX, posY, posZ;
	glPushMatrix();
	glGetIntegerv(GL_VIEWPORT, viewPort);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glPopMatrix();

	posX = opengl_coord[0];
	posY = opengl_coord[1];
	posZ = opengl_coord[2];

	gluProject(posX, posY, posZ, modelView, projection, viewPort, &winX, &winY, &winZ);
	screen_coord[0] = (float)winX;
	screen_coord[1] = (float)viewPort[3] - (float)winY;
}
int FindHitVertex(float x, float y)
{
	Vector2f screen_coord(x, y);
	Vector3f opengl_coord;
	for (int i = 0; i < static_cast<int>(mesh.control_points.size()); ++i)
	{
		Vector2f coord_2d;
		opengl_coord = mesh.control_points[i].coord;
		OpenGLToScreen(opengl_coord, coord_2d);
		float length = sqrt((screen_coord - coord_2d).dot(screen_coord - coord_2d));
		if (length < 5)
		{
			return i;
		}
	}
	return -1;
}

void OnMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			selected_id = FindHitVertex((float)x, (float)y);
			if (-1 == selected_id)
				return;
		}
		else
			selected_id = -1;
		glutPostRedisplay();
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		int HitPointId = FindHitVertex((float)x, (float)y);
		if (-1 != HitPointId)
		{
			mesh.control_points.erase(mesh.control_points.begin() + HitPointId);
		}
		else
		{
			Vector2f screen_coord((float)x, (float)y);
			Vector3f opengl_coord;
			ScreenToOpenGL(screen_coord, opengl_coord);

#ifdef SQUARE_MODEL
			opengl_coord *= 1.0f;
#else
			opengl_coord *= 0.4f;
#endif

			ControlPoint cp;
			cp.coord = opengl_coord;
			mesh.control_points.push_back(cp);
		}
	
		std::cout << "computing" << std::endl;
		mesh.computeBarycentric();
		if (mesh.control_points.size() > 1)
		{
			mesh.buildA1Bottom();
			mesh.buildA2Bottom();
		}

		glutPostRedisplay();
	}
}

void Deform()
{
	if (mesh.control_points.size() > 1 && mesh.control_points.size() < static_cast<int>(mesh.vertices.size()))
	{
		mesh.buildB1();
		mesh.SimilarityTransformation();
		mesh.buildB2();
		mesh.ScaleAdjustment();
	}
}

void OnMouseMove(int x, int y)
{
	if (selected_id != -1 && mesh.control_points.size() > 0)
	{
		Vector2f screen_coord((float)x, (float)y);
		Vector3f opengl_coord;
		ScreenToOpenGL(screen_coord, opengl_coord);

#ifdef SQUARE_MODEL
		opengl_coord *= 1.0f;
#else
		opengl_coord *= 0.4f;
#endif

		mesh.control_points[selected_id].coord = opengl_coord;
		glutPostRedisplay();
	}
}



void display()
{
	Deform();
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

#ifdef SQUARE_MODEL
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
#else
	gluLookAt(0, 0, 4, 0, 0, 0, 0, 1, 0);
#endif

	glLineWidth(2);
	glColor3f(0, 0, 0);
	for (unsigned int i = 0; i < mesh.triangles.size(); i++)
	{
		int v0_id = mesh.triangles[i][0];
		int v1_id = mesh.triangles[i][1];
		int v2_id = mesh.triangles[i][2];

		GLfloat *v0 = mesh.vertices[v0_id].data();
		GLfloat *v1 = mesh.vertices[v1_id].data();
		GLfloat *v2 = mesh.vertices[v2_id].data();

		glBegin(GL_LINE_LOOP);
		glVertex3fv(v0);
		glVertex3fv(v1);
		glVertex3fv(v2);
		glEnd();
	}

	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	for (int i = 0; i < mesh.control_points.size(); ++i)
	{
		GLfloat *v = mesh.control_points[i].coord.data();
		glVertex3fv(v);
	}

	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor3f(0, 1, 0);
	for (int i = 0; i < mesh.control_points.size(); ++i)
	{
		int triangle_id = mesh.control_points[i].triangle_id;

		int v0_id = mesh.triangles[triangle_id][0];
		int v1_id = mesh.triangles[triangle_id][1];
		int v2_id = mesh.triangles[triangle_id][2];

		GLfloat *v0 = mesh.vertices[v0_id].data();
		GLfloat *v1 = mesh.vertices[v1_id].data();
		GLfloat *v2 = mesh.vertices[v2_id].data();

		glVertex3fv(v0);
		glVertex3fv(v1);
		glVertex3fv(v2);
	}

	glEnd();
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 0.1, 10);
}

int main(int argc, char **argv)
{
#ifdef SQUARE_MODEL
	mesh.Read("../RigidDeform/squared_mesh.obj");
#else
	mesh.Read("../RigidDeform/man.obj");
#endif
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

#ifdef SQUARE_MODEL
	glutInitWindowSize(500, 500); 
#else
	glutInitWindowSize(1000, 1000);
#endif

	glutInitWindowPosition(100, 100);
	glutCreateWindow("test");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(OnMouseClick);
	glutMotionFunc(OnMouseMove);
	glutMainLoop();
	return 0;
}