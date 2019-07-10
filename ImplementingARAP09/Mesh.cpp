#include <algorithm>

#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Utils/getopt.h>
#include <OpenMesh/Core/Geometry/EigenVectorT.hh>

#include <GTEngine.h>

#include "Mesh.h"
#include "Common.h"

using namespace std;
using namespace Eigen;
using namespace OpenMesh;
using namespace gte;

struct EigenTraits : DefaultTraits
{
	using Point = Eigen::Vector3f;
};

bool sen::Mesh::Read(const std::string &file_path)
{
	TriMesh_ArrayKernelT<EigenTraits> mesh;
	if (!IO::read_mesh(mesh, file_path))
	{
		return false;
	}

	for (auto v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it)
	{
		this->vertices.push_back(mesh.point(*v_it));
	}

	for (auto e_it = mesh.edges_begin(); e_it != mesh.edges_end(); ++e_it)
	{
		if (!mesh.is_boundary(*e_it))
		{
			auto halfEdgeHandle = mesh.halfedge_handle(*e_it, 0);
			auto opposite_halfEdgeHandle = mesh.opposite_halfedge_handle(halfEdgeHandle);

			auto vi = mesh.from_vertex_handle(halfEdgeHandle);
			auto vj = mesh.to_vertex_handle(halfEdgeHandle);

			auto next_halfEdgeHandle = mesh.next_halfedge_handle(halfEdgeHandle);
			auto vl = mesh.to_vertex_handle(next_halfEdgeHandle);

			auto next_opposite_halfEdgeHandle = mesh.next_halfedge_handle(opposite_halfEdgeHandle);
			auto vr = mesh.to_vertex_handle(next_opposite_halfEdgeHandle);

			std::array<int, 4> neighbours = { vi.idx(), vj.idx(), vl.idx(), vr.idx() };
			Eigen::Vector3f edge_vector = vertices[vj.idx()] - vertices[vi.idx()];
			EdgeInner edge(neighbours, edge_vector);
			edge.computeGk(this->vertices);

			this->edges_inner.push_back(edge);
		}
		else
		{
			auto halfEdgeHandle = mesh.halfedge_handle(*e_it, 0);

			auto vi = mesh.from_vertex_handle(mesh.halfedge_handle(*e_it, 0));
			auto vj = mesh.to_vertex_handle(mesh.halfedge_handle(*e_it, 0));

			auto next_halfEdgeHandle = mesh.next_halfedge_handle(halfEdgeHandle);
			auto v_other = mesh.to_vertex_handle(next_halfEdgeHandle);

			std::array<int, 3> neighbours = { vi.idx(), vj.idx(), v_other.idx() };
			Eigen::Vector3f edge_vector = vertices[vj.idx()] - vertices[vi.idx()];

			EdgeBoundary edge(neighbours, edge_vector);
			edge.computeGk(this->vertices);
			edges_boundary.push_back(edge);
		}
	}

	for (auto f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it)
	{
		std::array<int, 3> triangle_vertex_ids;
		int vi = 0;
		for (auto fv_it = mesh.fv_iter(*f_it); fv_it.is_valid(); ++fv_it)
		{
			triangle_vertex_ids[vi++] = (*fv_it).idx();
		}
		triangles.push_back(triangle_vertex_ids);
	}

	preComputeBarycentric();
	buildA1Top();
	buildA2Top();
	return true;
}

void sen::Mesh::buildA1Top()
{
	L1 = Eigen::MatrixXf::Zero(2 * (edges_boundary.size() + edges_inner.size()), 2 * vertices.size());

	Eigen::MatrixXf Gk;
	int k = 0;
	for (auto &ek : edges_inner)
	{
		int vi = ek.neighbours[0];
		int vj = ek.neighbours[1];
		int vl = ek.neighbours[2];
		int vr = ek.neighbours[3];

		Eigen::Vector3f ek_v = ek.edge_vector;
		float ekx = ek_v(0); float eky = ek_v(1);
		Eigen::Matrix2f ek_mat;
		ek_mat <<
			ekx, eky,
			eky, -ekx;
		Gk = ek.Gk;

		Eigen::MatrixXf hk = constantM_inner - ek_mat * (Gk.transpose() * Gk).inverse() * Gk.transpose();

		int vix_index = 2 * vi; int viy_index = 2 * vi + 1;
		int vjx_index = 2 * vj; int vjy_index = 2 * vj + 1;
		int vlx_index = 2 * vl; int vly_index = 2 * vl + 1;
		int vrx_index = 2 * vr; int vry_index = 2 * vr + 1;
		int ekx_index = 2 * k;  int eky_index = 2 * k + 1;

		L1(ekx_index, vix_index) = hk(0, 0); L1(eky_index, vix_index) = hk(1, 0);
		L1(ekx_index, viy_index) = hk(0, 1); L1(eky_index, viy_index) = hk(1, 1);
		L1(ekx_index, vjx_index) = hk(0, 2); L1(eky_index, vjx_index) = hk(1, 2);
		L1(ekx_index, vjy_index) = hk(0, 3); L1(eky_index, vjy_index) = hk(1, 3);
		L1(ekx_index, vlx_index) = hk(0, 4); L1(eky_index, vlx_index) = hk(1, 4);
		L1(ekx_index, vly_index) = hk(0, 5); L1(eky_index, vly_index) = hk(1, 5);
		L1(ekx_index, vrx_index) = hk(0, 6); L1(eky_index, vrx_index) = hk(1, 6);
		L1(ekx_index, vry_index) = hk(0, 7); L1(eky_index, vry_index) = hk(1, 7);

		k++;
	}

	for (auto &ek : edges_boundary)
	{
		int vi = ek.neighbours[0];
		int vj = ek.neighbours[1];
		int vl = ek.neighbours[2];

		Eigen::Vector3f ek_v = ek.edge_vector;
		float ekx = ek_v(0); float eky = ek_v(1);
		Eigen::Matrix2f ek_mat;
		ek_mat <<
			ekx, eky,
			eky, -ekx;
		Gk = ek.Gk;

		Eigen::MatrixXf hk = constantM_boundary - ek_mat * (Gk.transpose() * Gk).inverse() * Gk.transpose();

		int vix_index = 2 * vi; int viy_index = 2 * vi + 1;
		int vjx_index = 2 * vj; int vjy_index = 2 * vj + 1;
		int vlx_index = 2 * vl; int vly_index = 2 * vl + 1;
		int ekx_index = 2 * k;  int eky_index = 2 * k + 1;

		L1(ekx_index, vix_index) = hk(0, 0); L1(eky_index, vix_index) = hk(1, 0);
		L1(ekx_index, viy_index) = hk(0, 1); L1(eky_index, viy_index) = hk(1, 1);
		L1(ekx_index, vjx_index) = hk(0, 2); L1(eky_index, vjx_index) = hk(1, 2);
		L1(ekx_index, vjy_index) = hk(0, 3); L1(eky_index, vjy_index) = hk(1, 3);
		L1(ekx_index, vlx_index) = hk(0, 4); L1(eky_index, vlx_index) = hk(1, 4);
		L1(ekx_index, vly_index) = hk(0, 5); L1(eky_index, vly_index) = hk(1, 5);

		k++;
	}
}
void sen::Mesh::buildA2Top()
{
	L2 = Eigen::MatrixXf::Zero(edges_boundary.size() + edges_inner.size(), vertices.size());
	int k = 0;

	for (const auto &ek : edges_inner)
	{
		int vi_index = ek.neighbours[0];
		int vj_index = ek.neighbours[1];

		int ek_index = k;

		L2(ek_index, vi_index) = -1;
		L2(ek_index, vj_index) = 1;

		k++;
	}

	k = edges_inner.size();

	for (const auto &ek : edges_boundary)
	{
		int vi_index = ek.neighbours[0];
		int vj_index = ek.neighbours[1];

		int ek_index = k;

		L2(ek_index, vi_index) = -1;
		L2(ek_index, vj_index) = 1;

		k++;
	}
}

void sen::Mesh::preComputeBarycentric()
{
	unsigned int numVertices = vertices.size();
	std::vector<Vector2<float>> tcoords(numVertices);
	for (int i = 0; i < vertices.size(); ++i)
	{
		tcoords[i] = Vector2<float>{ vertices[i](0), vertices[i](1) };
	}

	unsigned int numTriangles = triangles.size();
	mPMesher = std::make_unique<PlanarMesher>(numVertices, &tcoords[0],
		numTriangles, reinterpret_cast<int const*>(&triangles[0]));
}
bool sen::Mesh::computeBarycentric()
{
	for (int i = 0; i < control_points.size(); ++i)
	{
		Vector2<float> P{ control_points[i].coord(0), control_points[i].coord(1) };
		std::array<float, 3> bary;

#ifdef CONVEX_MODEL
		int triangle_id = mPMesher->GetContainingTriangle(P);
		if (triangle_id == -1)
		{
			std::cout << "Not found the triangle!" << std::endl;
			bary = { 0 };
			continue;
		}

		if (!mPMesher->GetBarycentrics(triangle_id, P, bary))
		{
			std::cout << "P is in a needle-like or degenerate triangle." << std::endl;
			bary = { 0 };
			continue;
		}
		control_points[i].bary = bary;
		control_points[i].triangle_id = triangle_id;

#else
		for (int j = 0; j < triangles.size(); ++j)
		{
			if (mPMesher->Contains(j, P))
			{
				std::cout << "triangle id: " << std::endl;
				mPMesher->GetBarycentrics(j, P, bary);
				control_points[i].bary = bary;
				control_points[i].triangle_id = j;
				break;
			}
			else
			{
				bary = { 0 };
				continue;
			}
		}
#endif
	}
	return true;
}
void sen::Mesh::buildA1Bottom()
{
	C1 = Eigen::MatrixXf::Zero(2 * control_points.size(), 2 * vertices.size());

	for (int ci = 0; ci < control_points.size(); ++ci)
	{
		int cix_index = 2 * ci;
		int ciy_index = 2 * ci + 1;

		int triangle_id = control_points[ci].triangle_id;
		float w0 = control_points[ci].bary[0];
		int w0_vertex_id = 2 * triangles[triangle_id][0];
		C1(cix_index, w0_vertex_id) = w * w0;
		C1(ciy_index, w0_vertex_id + 1) = w * w0;

		float w1 = control_points[ci].bary[1];
		int w1_vertex_id = 2 * triangles[triangle_id][1];
		C1(cix_index, w1_vertex_id) = w * w1;
		C1(ciy_index, w1_vertex_id + 1) = w * w1;

		float w2 = control_points[ci].bary[2];
		int w2_vertex_id = 2 * triangles[triangle_id][2];
		C1(cix_index, w2_vertex_id) = w * w2;
		C1(ciy_index, w2_vertex_id + 1) = w * w2;
	}

	b1 = Eigen::VectorXf::Zero(2 * (edges_boundary.size() + edges_inner.size()) + 2 * control_points.size());
}
void sen::Mesh::buildA2Bottom()
{
	C2 = Eigen::MatrixXf::Zero(control_points.size(), vertices.size());

	for (int ci = 0; ci < control_points.size(); ++ci)
	{
		int triangle_id = control_points[ci].triangle_id;
		float w0 = control_points[ci].bary[0];
		int w0_vertex_id = triangles[triangle_id][0];
		C2(ci, w0_vertex_id) = w * w0;

		float w1 = control_points[ci].bary[1];
		int w1_vertex_id = triangles[triangle_id][1];
		C2(ci, w1_vertex_id) = w * w1;

		float w2 = control_points[ci].bary[2];
		int w2_vertex_id = triangles[triangle_id][2];
		C2(ci, w2_vertex_id) = w * w2;
	}

	b2x = Eigen::VectorXf(edges_boundary.size() + edges_inner.size() + control_points.size());
	b2y = Eigen::VectorXf(edges_boundary.size() + edges_inner.size() + control_points.size());
}
void sen::Mesh::buildB1()
{
	int edge_vectors_size = 2 * (edges_boundary.size() + edges_inner.size());

	for (int ci = 0; ci < control_points.size(); ++ci)
	{
		int cix_index = edge_vectors_size + 2 * ci;
		int ciy_index = edge_vectors_size + 2 * ci + 1;

		float cix = control_points[ci].coord(0);
		float ciy = control_points[ci].coord(1);

		b1(cix_index) = w * cix;
		b1(ciy_index) = w * ciy;
	}
}
void sen::Mesh::buildB2()
{

	int k = 0;
	for (const auto &ek : edges_inner)
	{
		int vi = ek.neighbours[0]; float vix = vertices[vi](0); float viy = vertices[vi](1);
		int vj = ek.neighbours[1]; float vjx = vertices[vj](0); float vjy = vertices[vj](1);
		int vl = ek.neighbours[2]; float vlx = vertices[vl](0); float vly = vertices[vl](1);
		int vr = ek.neighbours[3]; float vrx = vertices[vr](0); float vry = vertices[vr](1);

		Eigen::MatrixXf Gk = ek.Gk;

		Eigen::VectorXf vek(8, 1);
		vek << vix, viy, vjx, vjy, vlx, vly, vrx, vry;

		Eigen::Vector2f cksk = (Gk.transpose() * Gk).inverse() * Gk.transpose() * vek;
		float ck = cksk(0);
		float sk = cksk(1);
		Eigen::Matrix2f Tk;
		Tk <<
			ck, sk,
			-sk, ck;

		Tk = Tk * (1.0f / sqrt((pow(ck, 2) + pow(sk, 2))));

		Eigen::Vector2f ek_v = ek.edge_vector.head<2>();
		ek_v = Tk * ek_v;

		b2x(k) = ek_v(0);
		b2y(k) = ek_v(1);

		k++;
	}

	k = edges_inner.size();
	for (const auto &ek : edges_boundary)
	{
		int vi = ek.neighbours[0]; float vix = vertices[vi](0); float viy = vertices[vi](1);
		int vj = ek.neighbours[1]; float vjx = vertices[vj](0); float vjy = vertices[vj](1);
		int vl = ek.neighbours[2]; float vlx = vertices[vl](0); float vly = vertices[vl](1);

		Eigen::MatrixXf Gk = ek.Gk;

		Eigen::VectorXf vek(6, 1);
		vek << vix, viy, vjx, vjy, vlx, vly;

		Eigen::Vector2f cksk = (Gk.transpose() * Gk).inverse() * Gk.transpose() * vek;
		float ck = cksk(0);
		float sk = cksk(1);
		Eigen::Matrix2f Tk;
		Tk <<
			ck, sk,
			-sk, ck;

		Tk = Tk * (1.0f / sqrt((pow(ck, 2) + pow(sk, 2))));

		Eigen::Vector2f ek_v = ek.edge_vector.head<2>();
		ek_v = Tk * ek_v;

		b2x(k) = ek_v(0);
		b2y(k) = ek_v(1);

		k++;
	}

	int edge_vectors_size = edges_boundary.size() + edges_inner.size();

	for (int ci = 0; ci < control_points.size(); ++ci)
	{
		int cix_index = edge_vectors_size + ci;
		int ciy_index = edge_vectors_size + ci;

		float cix = control_points[ci].coord(0);
		float ciy = control_points[ci].coord(1);

		b2x(cix_index) = w * cix;
		b2y(ciy_index) = w * ciy;
	}
}

void sen::Mesh::SimilarityTransformation()
{
	if (control_points.size() > 1)
	{
		Eigen::MatrixXf A1(2 * (edges_boundary.size() + edges_inner.size()) + 2 * control_points.size(), 2 * vertices.size());
		A1.block(0, 0, 2 * (edges_boundary.size() + edges_inner.size()), 2 * vertices.size()) = L1;
		A1.block(2 * (edges_boundary.size() + edges_inner.size()), 0, 2 * control_points.size(), 2 * vertices.size()) = C1;
		Eigen::VectorXf v = ((A1.transpose() * A1)).ldlt().solve(A1.transpose() * b1);
		for (int i = 0; i < vertices.size(); ++i)
		{
			float vx, vy;
			vx = *(v.data() + 2 * i);
			vy = *(v.data() + 2 * i + 1);
			vertices[i](0) = vx;
			vertices[i](1) = vy;
		}
	}
}

void sen::Mesh::ScaleAdjustment()
{
	if (control_points.size() > 1)
	{
		Eigen::MatrixXf A2(edges_boundary.size() + edges_inner.size() + control_points.size(), vertices.size());
		A2.block(0, 0, edges_boundary.size() + edges_inner.size(), vertices.size()) = L2;
		A2.block(edges_boundary.size() + edges_inner.size(), 0, control_points.size(), vertices.size()) = C2;

		Eigen::VectorXf vx = ((A2.transpose() * A2)).ldlt().solve(A2.transpose() * b2x);
		for (int i = 0; i < vertices.size(); ++i)
		{
			float x = *(vx.data() + i);
			vertices[i](0) = x;
		}
		Eigen::VectorXf vy = ((A2.transpose() * A2)).ldlt().solve(A2.transpose() * b2y);
		for (int i = 0; i < vertices.size(); ++i)
		{
			float y = *(vy.data() + i);
			vertices[i](1) = y;
		}
	}
}