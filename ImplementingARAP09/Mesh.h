#pragma once
#include <vector>
#include <array>

#include <Eigen/Dense>

#include <GTEngine.h>

namespace sen
{
	struct ControlPoint
	{
		Eigen::Vector3f coord;
		std::array<float, 3> bary;
		int triangle_id;
	};
	struct EdgeBoundary
	{
		std::array<int, 3> neighbours;
		Eigen::Vector3f edge_vector;
		Eigen::MatrixXf Gk;

		EdgeBoundary()
		{

		}
		EdgeBoundary(const std::array<int, 3> &neighbours_, const Eigen::Vector3f &edge_vector_)
		{
			neighbours = neighbours_;
			edge_vector = edge_vector_;
		}

		void computeGk(const std::vector<Eigen::Vector3f> vertices)
		{
			int vi = neighbours[0]; float vix = vertices[vi](0); float viy = vertices[vi](1);
			int vj = neighbours[1]; float vjx = vertices[vj](0); float vjy = vertices[vj](1);
			int vl = neighbours[2]; float vlx = vertices[vl](0); float vly = vertices[vl](1);

			Gk = (
				Eigen::MatrixXf(6, 2) <<
				vix, viy,
				viy, -vix,
				vjx, vjy,
				vjy, -vjx,
				vlx, vly,
				vly, -vlx).finished();
		}
	};
	struct EdgeInner
	{
		std::array<int, 4> neighbours;
		Eigen::Vector3f edge_vector;
		Eigen::MatrixXf Gk;
		EdgeInner()
		{

		}
		EdgeInner(const std::array<int, 4> &neighbours_, const Eigen::Vector3f &edge_vector_)
		{
			neighbours = neighbours_;
			edge_vector = edge_vector_;
		}

		void computeGk(const std::vector<Eigen::Vector3f> &vertices)
		{
			int vi = neighbours[0]; float vix = vertices[vi](0); float viy = vertices[vi](1);
			int vj = neighbours[1]; float vjx = vertices[vj](0); float vjy = vertices[vj](1);
			int vl = neighbours[2]; float vlx = vertices[vl](0); float vly = vertices[vl](1);
			int vr = neighbours[3]; float vrx = vertices[vr](0); float vry = vertices[vr](1);

			Gk = (
				Eigen::MatrixXf(8, 2) <<
				vix, viy,
				viy, -vix,
				vjx, vjy,
				vjy, -vjx,
				vlx, vly,
				vly, -vlx,
				vrx, vry,
				vry, -vrx).finished();
		}
	};
	class Mesh
	{
	public:
		Mesh()
		{

		}
		~Mesh()
		{

		}

		std::vector<Eigen::Vector3f> vertices;
		std::vector<std::array<int, 3>> triangles;
		std::vector<EdgeBoundary> edges_boundary;
		std::vector<EdgeInner> edges_inner;

		std::vector<ControlPoint> control_points;

		bool Read(const std::string &file_path);
		void SimilarityTransformation();
		void ScaleAdjustment();

		bool computeBarycentric();
		void buildA1Bottom();
		void buildA2Bottom();
		void buildB1();
		void buildB2();

	private:
		Eigen::MatrixXf L1;
		void buildA1Top();
		Eigen::MatrixXf L2;
		void buildA2Top();
		Eigen::MatrixXf C1;
		Eigen::MatrixXf C2;
		Eigen::VectorXf b1;
		Eigen::VectorXf b2x;
		Eigen::VectorXf b2y;

		typedef gte::BSNumber<gte::UIntegerAP32> Numeric;
		typedef gte::BSRational<gte::UIntegerAP32> Rational;
		typedef gte::PlanarMesh<float, Rational, Rational> PlanarMesher;

		std::unique_ptr<PlanarMesher> mPMesher;
		void preComputeBarycentric();
	};
}