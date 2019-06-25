#include <cmath>
#include <algorithm>

#include <Eigen/Geometry>

#include <TriMesh.h>

#include "Mesh.h"

using namespace std;
using namespace Eigen;
using namespace trimesh;

void sen::Mesh::computeLocalXY(Triangle &t)
{
	for (int i = 0; i < 3; ++i)
	{
		Vector2f v0 = vertices[t.vertex_id[i]].coord.head<2>();
		Vector2f v1 = vertices[t.vertex_id[(i + 1) % 3]].coord.head<2>();
		Vector2f v2 = vertices[t.vertex_id[(i + 2) % 3]].coord.head<2>();

		Vector2f v01 = v1 - v0;
		Vector2f v02 = v2 - v0;
		float x01 = v01.dot(v02) / v01.dot(v01);
		
		Matrix2f R90;
		R90 = Rotation2D<float>((float)M_PI_2);
		Vector2f v01_90 = R90 * v01;
		float y01 = v01_90.dot(v02) / v01_90.dot(v01_90);

		t.local_xy[(i + 2) % 3]= Vector2f(x01, y01);
	}
}

bool sen::Mesh::Read(const string &file_path)
{
	TriMesh::set_verbose(0);
	TriMesh *mesh = TriMesh::read(file_path);
	if (NULL != mesh)
	{
		mesh->need_bbox();

		for (int i = 0; i < static_cast<int>(mesh->vertices.size()); ++i)
		{
			Vertex v;
			v.id = i;
			v.coord = Vector3f(mesh->vertices[i][0], mesh->vertices[i][1], 0.0f);
			v.isU = true;
			vertices.push_back(v);
		}

		q_size = 0;

		for (int i = 0; i < static_cast<int>(mesh->faces.size()); ++i)
		{
			Triangle t;
			t.vertex_id[0] = mesh->faces[i][0];
			t.vertex_id[1] = mesh->faces[i][1];
			t.vertex_id[2] = mesh->faces[i][2];
			computeLocalXY(t);
			Vector2f v0 = vertices[t.vertex_id[0]].coord.head<2>();
			Vector2f v1 = vertices[t.vertex_id[1]].coord.head<2>();
			t.scale_factor_divisor = (v1 - v0).dot(v1 - v0);
			t.PreComputeScaleAdjustmentMatrixFC();
			triangles.push_back(t);
		}

		return true;
	}
	
	return false;
}

bool sen::Mesh::find(int original_id)
{
	for (int i = 0; i < static_cast<int>(vertices.size()); ++i)
	{
		if (original_id == vertices[i].id)
		{
			if (!vertices[i].isU)
			{
				vertices[i].isU = true;
				q_size--;
			}
			else
			{
				vertices[i].isU = false;
				q_size++;
			}

			return true;
		}
	}

	return false;
}

void sen::Mesh::resetVerticesTo_uq()
{
	for (int i = 0, j = 0; i < static_cast<int>(vertices.size()), j < q_size; ++i)
	{
		if (!vertices[i].isU)// control point
		{
			auto it = vertices.begin() + i;
			std::rotate(it, it + 1, vertices.end());
			i--;
			j++;
		}
	}
}
Eigen::MatrixXf sen::Mesh::PreComputeScaleFreeMatrix()
{
	Eigen::MatrixXf scaleFreeMatrix;
	if (q_size > 1)
	{
		int u_size = vertices.size() - q_size;
		q_size = q_size;
		MatrixXf G00(2 * u_size, 2 * u_size);
		MatrixXf G01(2 * u_size, 2 * q_size);
		MatrixXf G10(2 * q_size, 2 * u_size);
		MatrixXf G = MatrixXf::Zero(2 * vertices.size(), 2 * vertices.size());

		for (unsigned int i = 0; i < triangles.size(); i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				int v0_id, v1_id, v2_id;
				v0_id = std::find(vertices.begin(), vertices.end(), Vertex(triangles[i].vertex_id[j])) - vertices.begin();
				v1_id = std::find(vertices.begin(), vertices.end(), Vertex(triangles[i].vertex_id[(j + 1) % 3])) - vertices.begin();
				v2_id = std::find(vertices.begin(), vertices.end(), Vertex(triangles[i].vertex_id[(j + 2) % 3])) - vertices.begin();

				float x01, y01;
				x01 = triangles[i].local_xy[(j + 2) % 3][0];
				y01 = triangles[i].local_xy[(j + 2) % 3][1];

				G(2 * v0_id, 2 * v0_id) += pow(x01, 2) - 2 * x01 + pow(y01, 2) + 1;

				G(2 * v0_id, 2 * v0_id + 1) = 0 / 2;
				G(2 * v0_id + 1, 2 * v0_id) += 0;

				G(2 * v0_id, 2 * v1_id) += (1 - x01)*x01 - pow(y01, 2);
				G(2 * v1_id, 2 * v0_id) += (1 - x01)*x01 - pow(y01, 2);


				G(2 * v0_id, 2 * v1_id + 1) += -y01;
				G(2 * v1_id + 1, 2 * v0_id) += -y01;

				G(2 * v0_id, 2 * v2_id) += -(1 - x01);
				G(2 * v2_id, 2 * v0_id) += -(1 - x01);

				G(2 * v0_id, 2 * v2_id + 1) += y01;
				G(2 * v2_id + 1, 2 * v0_id) += y01;

				G(2 * v0_id + 1, 2 * v0_id + 1) += pow(x01, 2) - 2 * x01 + pow(y01, 2) + 1;

				G(2 * v0_id + 1, 2 * v1_id) += y01;
				G(2 * v1_id, 2 * v0_id + 1) += y01;

				G(2 * v0_id + 1, 2 * v1_id + 1) += x01 - x01 * x01 - y01 * y01;
				G(2 * v1_id + 1, 2 * v0_id + 1) += x01 - x01 * x01 - y01 * y01;

				G(2 * v0_id + 1, 2 * v2_id) += -y01;
				G(2 * v2_id, 2 * v0_id + 1) += -y01;

				G(2 * v0_id + 1, 2 * v2_id + 1) += -1 + x01;
				G(2 * v2_id + 1, 2 * v0_id + 1) += -1 + x01;

				G(2 * v1_id, 2 * v1_id) += pow(x01, 2) + pow(y01, 2);

				G(2 * v1_id, 2 * v1_id + 1) += 0 / 2;
				G(2 * v1_id + 1, 2 * v1_id) += 0 / 2;

				G(2 * v1_id, 2 * v2_id) += -x01;
				G(2 * v2_id, 2 * v1_id) += -x01;

				G(2 * v1_id, 2 * v2_id + 1) += -y01;
				G(2 * v2_id + 1, 2 * v1_id) += -y01;

				G(2 * v1_id + 1, 2 * v1_id + 1) += pow(x01, 2) + pow(y01, 2);

				G(2 * v1_id + 1, 2 * v2_id) += y01;
				G(2 * v2_id, 2 * v1_id + 1) += y01;

				G(2 * v1_id + 1, 2 * v2_id + 1) += -x01;
				G(2 * v2_id + 1, 2 * v1_id + 1) += -x01;


				G(2 * v2_id, 2 * v2_id) += 1;

				G(2 * v2_id, 2 * v2_id + 1) += 0;
				G(2 * v2_id + 1, 2 * v2_id) += 0;

				G(2 * v2_id + 1, 2 * v2_id + 1) += 1;
			}
		}

		G00 = G.block(0, 0, 2 * u_size, 2 * u_size);
		G01 = G.block(0, 2 * u_size, 2 * u_size, 2 * q_size);
		G10 = G.block(2 * u_size, 0, 2 * q_size, 2 * u_size);

		MatrixXf Gp = G00 + G00.transpose();
		MatrixXf Gp_inverse = Gp.inverse();
		MatrixXf B = G01 + G10.transpose();

		scaleFreeMatrix = -Gp_inverse * B;
	}

	return scaleFreeMatrix;
}

void sen::Mesh::AdjustScaleToTriangle(const int &triangle_id, vector<Vector2f> &triangle_points)
{
	VectorXf triangle_points_coords(6);
	for (int i = 0; i < 6; i += 2)
	{
		int v_id = std::find(vertices.begin(), vertices.end(),
			Vertex(triangles[triangle_id].vertex_id[i / 2])) - vertices.begin();
		triangle_points_coords(i) = vertices[v_id].coord(0);
		triangle_points_coords(i + 1) = vertices[v_id].coord(1);
	}
	MatrixXf F, C;
	F = triangles[triangle_id].F;
	C = triangles[triangle_id].C;

	VectorXf v_fitted_coords = -F * C * triangle_points_coords;
	Vector2f v0f = v_fitted_coords.block(0, 0, 2, 1);
	Vector2f v1f = v_fitted_coords.block(2, 0, 2, 1);

	float x01, y01;
	x01 = triangles[triangle_id].local_xy[2](0);
	y01 = triangles[triangle_id].local_xy[2](1);

	Matrix2f R90;
	R90 = Rotation2D<float>((float)M_PI_2);

	Vector2f v2f = v0f + x01 * (v1f - v0f) + y01 * R90*(v1f - v0f);

	triangle_points.push_back(v0f);
	triangle_points.push_back(v1f);
	triangle_points.push_back(v2f);

	float scale_factor = sqrt(triangles[triangle_id].scale_factor_divisor / (v1f - v0f).dot(v1f - v0f));
	Vector2f center_mass(v0f + v1f + v2f);
	center_mass *= (float)1 / (float)3;

	for (int i = 0; i < 3; i++)
	{
		triangle_points[i] -= center_mass;
		triangle_points[i] *= scale_factor;
		triangle_points[i] += center_mass;
	}
}
void sen::Mesh::PreComputeScaleAdjustmentMatrixHf(MatrixXf &Hp, MatrixXf &D)
{
	MatrixXf H;
	if (q_size > 1 && q_size < static_cast<int>(vertices.size()))
	{
		int u_size = vertices.size() - q_size;
		q_size = q_size;

		H = MatrixXf::Zero(2 * vertices.size(), 2 * vertices.size());
		MatrixXf H00(2 * u_size, 2 * u_size),
			H01(2 * u_size, 2 * q_size),
			H10(2 * q_size, 2 * u_size);

		for (unsigned int i = 0; i < triangles.size(); i++)
		{
			for (int j = 0; j < 3; j++)
			{
				int v0f_id, v1f_id, v2f_id;
				v0f_id = std::find(vertices.begin(), vertices.end(), Vertex(triangles[i].vertex_id[j])) - vertices.begin();
				v1f_id = std::find(vertices.begin(), vertices.end(), Vertex(triangles[i].vertex_id[(j + 1) % 3])) - vertices.begin();
				v2f_id = std::find(vertices.begin(), vertices.end(), Vertex(triangles[i].vertex_id[(j + 2) % 3])) - vertices.begin();

				int v0p_id = v0f_id;
				int v1p_id = v1f_id;
				H(2 * v0p_id, 2 * v0p_id) += 1;
				H(2 * v0p_id, 2 * v0p_id + 1) += 0;
				H(2 * v0p_id, 2 * v1p_id) += -1;
				H(2 * v0p_id, 2 * v1p_id + 1) += 0;
				H(2 * v0p_id + 1, 2 * v0p_id) += 0;
				H(2 * v0p_id + 1, 2 * v0p_id + 1) += 1;
				H(2 * v0p_id + 1, 2 * v1p_id) += 0;
				H(2 * v0p_id + 1, 2 * v1p_id + 1) += -1;
				H(2 * v1p_id, 2 * v0p_id) += -1;
				H(2 * v1p_id, 2 * v0p_id + 1) += 0;
				H(2 * v1p_id, 2 * v1p_id) += 1;
				H(2 * v1p_id, 2 * v1p_id + 1) += 0;
				H(2 * v1p_id + 1, 2 * v0p_id) += 0;
				H(2 * v1p_id + 1, 2 * v0p_id + 1) += -1;
				H(2 * v1p_id + 1, 2 * v1p_id + 1) += 0;
				H(2 * v1p_id + 1, 2 * v1p_id + 1) += 1;
			}
		}
		H00 = H.block(0, 0, 2 * u_size, 2 * u_size);
		H01 = H.block(0, 2 * u_size, 2 * u_size, 2 * q_size);
		H10 = H.block(2 * u_size, 0, 2 * q_size, 2 * u_size);

		Hp = H00 + H00.transpose();
		D = H01 + H10.transpose();
	}
}