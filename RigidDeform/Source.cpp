#include <iostream>
#include <cmath>
#include <algorithm>

#include <Eigen/Dense>

#include <TriMesh.h>

#include <GL/glut.h>
#include <gl/glu.h>

#include "Mesh.h"

using namespace std;
using namespace Eigen;
using namespace trimesh;
using namespace sen;

sen::Mesh mesh;
MatrixXf scaleFreeMatrix;
MatrixXf Hp, D;
int selected_id = 0;

std::vector<std::array<Eigen::Vector3f, 3>> temp_triangles_21;

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
	for (int i = 0; i < static_cast<int>(mesh.vertices.size()); ++i)
	{
		Vector2f coord_2d;
		opengl_coord = mesh.vertices[i].coord;
		OpenGLToScreen(opengl_coord, coord_2d);
		float length = sqrt((screen_coord - coord_2d).dot(screen_coord - coord_2d));
		if (length < 5)
		{
			return mesh.vertices[i].id;
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
			int origial_id = FindHitVertex((float)x, (float)y);
			if (-1 == origial_id)
				return;
			selected_id = find(mesh.vertices.begin(), mesh.vertices.end(), Vertex(origial_id)) - mesh.vertices.begin();
		}
		else
			selected_id = -1;
		glutPostRedisplay();
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		int HitPointId = FindHitVertex((float)x, (float)y);
		std::cout << "HitPointId: " << HitPointId << std::endl;
		if (-1 != HitPointId)
		{
			if (mesh.find(HitPointId))
			{
				mesh.resetVerticesTo_uq();
			}
			std::cout << "computing" << std::endl;
			scaleFreeMatrix = mesh.PreComputeScaleFreeMatrix();
			mesh.PreComputeScaleAdjustmentMatrixHf(Hp, D);
			glutPostRedisplay();
		}
	}
}

void OnMouseMove(int x, int y)
{
	if (selected_id != 0 && mesh.q_size > 0)
	{
		Vector2f screen_coord((float)x, (float)y);
		Vector3f opengl_coord;
		ScreenToOpenGL(screen_coord, opengl_coord);
		opengl_coord *= 0.4f;// 0.4 for mesh, 1 for square mesh
		mesh.vertices[selected_id].coord = opengl_coord;
		glutPostRedisplay();
	}
}

void Deform()
{
	if (mesh.q_size > 1 && mesh.q_size < static_cast<int>(mesh.vertices.size()))
	{
		VectorXf q(2 * mesh.q_size);
		for (int i = static_cast<int>(mesh.vertices.size()) - mesh.q_size, j = 0; i < static_cast<int>(mesh.vertices.size()), j < mesh.q_size; ++i, ++j)
		{
			Vector3f v = mesh.vertices[i].coord;
			q(2 * j) = v(0);
			q(2 * j + 1) = v(1);
		}

		VectorXf u = scaleFreeMatrix * q;
		for (int i = 0; i < static_cast<int>(mesh.vertices.size()) - mesh.q_size; ++i)
		{
			mesh.vertices[i].coord(0) = u(2 * i);
			mesh.vertices[i].coord(1) = u(2 * i + 1);
		}

		VectorXf f = VectorXf::Zero(2 * mesh.vertices.size());
		for (int i = 0; i < static_cast<int>(mesh.triangles.size()); ++i)
		{
			vector<Vector2f> current_triangle_points;
			mesh.AdjustScaleToTriangle(i, current_triangle_points);
			for (int j = 0; j < 3; j++)
			{
				Vector2f v0f, v1f, v2f;
				v0f = current_triangle_points[j];
				v1f = current_triangle_points[(j + 1) % 3];

				int v0f_id, v1f_id;
				v0f_id = find(mesh.vertices.begin(), mesh.vertices.end(), Vertex(mesh.triangles[i].vertex_id[j])) - mesh.vertices.begin();
				v1f_id = find(mesh.vertices.begin(), mesh.vertices.end(), Vertex(mesh.triangles[i].vertex_id[(j + 1) % 3])) - mesh.vertices.begin();

				int v0p_id = v0f_id;
				int v1p_id = v1f_id;
				f(2 * v0p_id) += -2 * v0f(0) + 2 * v1f(0);
				f(2 * v0p_id + 1) += -2 * v0f(1) + 2 * v1f(1);
				f(2 * v1p_id) += 2 * v0f(0) - 2 * v1f(0);
				f(2 * v1p_id + 1) += 2 * v0f(1) - 2 * v1f(1);
			}
		}
		int u_size = mesh.vertices.size() - mesh.q_size;
		VectorXf f0 = VectorXf::Zero(2 * u_size);
		for (int i = 0; i < 2 * u_size; i++)
		{
			f0[i] = f[i];
		}
		VectorXf b = VectorXf::Zero(2 * u_size);
		for (int i = static_cast<int>(mesh.vertices.size()) - mesh.q_size, j = 0; i < static_cast<int>(mesh.vertices.size()), j < mesh.q_size; ++i, ++j)
		{
			Vector3f v = mesh.vertices[i].coord;
			q(2 * j) = v(0);
			q(2 * j + 1) = v(1);
		}
		b = -(D*q + f0);
		u = Hp.llt().solve(b);
		for (int i = 0; i < static_cast<int>(mesh.vertices.size()) - mesh.q_size; ++i)
		{
			mesh.vertices[i].coord(0) = u(2 * i);
			mesh.vertices[i].coord(1) = u(2 * i + 1);
		}
	}
}

void display()
{
	Deform();
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 4, 0, 0, 0, 0, 1, 0);//4 for mesh, 10 for square mesh
	glLineWidth(2);
	glColor3f(0, 0, 0);
	for (unsigned int i = 0; i < mesh.triangles.size(); i++)
	{
		int v0_id = find(mesh.vertices.begin(), mesh.vertices.end(), Vertex(mesh.triangles[i].vertex_id[0])) - mesh.vertices.begin();
		int v1_id = find(mesh.vertices.begin(), mesh.vertices.end(), Vertex(mesh.triangles[i].vertex_id[1])) - mesh.vertices.begin();
		int v2_id = find(mesh.vertices.begin(), mesh.vertices.end(), Vertex(mesh.triangles[i].vertex_id[2])) - mesh.vertices.begin();

		GLfloat *v0 = mesh.vertices[v0_id].coord.data();
		GLfloat *v1 = mesh.vertices[v1_id].coord.data();
		GLfloat *v2 = mesh.vertices[v2_id].coord.data();

		glBegin(GL_LINE_LOOP);
		glVertex3fv(v0);
		glVertex3fv(v1);
		glVertex3fv(v2);
		glEnd();
	}

	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	for (int i = static_cast<int>(mesh.vertices.size()) - mesh.q_size; i < static_cast<int>(mesh.vertices.size()); ++i)
	{
		GLfloat *v = mesh.vertices[i].coord.data();
		glVertex3fv(v);
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
	mesh.Read("man.obj");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("test");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(OnMouseClick);
	glutMotionFunc(OnMouseMove);
	glutMainLoop();
	return 0;
}