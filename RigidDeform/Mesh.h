#pragma once
#include <string>
#include <vector>
#include <array>
#include <Eigen/Dense>

namespace sen
{
	struct Triangle
	{
		std::array<int, 3> vertex_id;
		std::array<Eigen::Vector2f, 3> local_xy;
		float scale_factor_divisor;
		Eigen::MatrixXf F;
		Eigen::MatrixXf C;

		void PreComputeScaleAdjustmentMatrixFC()
		{
			float x01 = local_xy[2](0);
			float y01 = local_xy[2](1);
			float x12 = local_xy[0](0);
			float y12 = local_xy[0](1);
			float x20 = local_xy[1](0);
			float y20 = local_xy[1](1);

			F.resize(4, 4);
			F(0, 0) = 4 - 8 * x01 + 4 * pow(x01, 2) + 2 * pow(x12, 2) - 4 * x01*pow(x12, 2) + 2 * pow(x01, 2)*pow(x12, 2) + 4 * x01*x20 - 4 * pow(x01, 2)*x20 + 2 * pow(x01, 2)*pow(x20, 2) +
				4 * pow(y01, 2) + 2 * pow(x12, 2)*pow(y01, 2) - 4 * x20*pow(y01, 2) + 2 * pow(x20, 2)*pow(y01, 2) + 2 * pow(y12, 2) - 4 * x01*pow(y12, 2) + 2 * pow(x01, 2)*pow(y12, 2) +
				2 * pow(y01, 2)*pow(y12, 2) - 4 * y01*y20 + 2 * pow(x01, 2)*pow(y20, 2) + 2 * pow(y01, 2)*pow(y20, 2);
			F(0, 1) = 2 * (-(x12*y01) + (1 - x01)*y12)*((1 - x01)*x12 + y01 * y12) + 2 * (x12*y01 + (-1 + x01)*y12)*((1 - x01)*x12 + y01 * y12) +
				2 * (y01 - x20 * y01 - x01 * y20)*(1 - x01 + x01 * x20 - y01 * y20) + 2 * (-y01 + x20 * y01 + x01 * y20)*(1 - x01 + x01 * x20 - y01 * y20);
			F(0, 2) = 2 * (1 - x01)*x01 - 2 * pow(y01, 2) + 2 * (-(x12*y01) + (1 - x01)*y12)*(x12*y01 + (-1 + x01)*y12) + 2 * (1 + (-1 + x01)*x12 - y01 * y12)*((1 - x01)*x12 + y01 * y12) +
				2 * (y01 - x20 * y01 - x01 * y20)*(-y01 + x20 * y01 + x01 * y20) + 2 * (1 - x01 + x01 * x20 - y01 * y20)*(x01 - x01 * x20 + y01 * y20);
			F(0, 3) = -2 * (1 - x01)*y01 - 2 * x01*y01 + 2 * (-(x12*y01) + (1 - x01)*y12)*(1 + (-1 + x01)*x12 - y01 * y12) + 2 * (-(x12*y01) + (1 - x01)*y12)*((1 - x01)*x12 + y01 * y12) +
				2 * (-y01 + x20 * y01 + x01 * y20)*(1 - x01 + x01 * x20 - y01 * y20) + 2 * (-y01 + x20 * y01 + x01 * y20)*(x01 - x01 * x20 + y01 * y20);
			F(1, 0) = 2 * (-(x12*y01) + (1 - x01)*y12)*((1 - x01)*x12 + y01 * y12) + 2 * (x12*y01 + (-1 + x01)*y12)*((1 - x01)*x12 + y01 * y12) +
				2 * (y01 - x20 * y01 - x01 * y20)*(1 - x01 + x01 * x20 - y01 * y20) + 2 * (-y01 + x20 * y01 + x01 * y20)*(1 - x01 + x01 * x20 - y01 * y20);
			F(1, 1) = 4 - 8 * x01 + 4 * pow(x01, 2) + 2 * pow(x12, 2) - 4 * x01*pow(x12, 2) + 2 * pow(x01, 2)*pow(x12, 2) + 4 * x01*x20 - 4 * pow(x01, 2)*x20 + 2 * pow(x01, 2)*pow(x20, 2) +
				4 * pow(y01, 2) + 2 * pow(x12, 2)*pow(y01, 2) - 4 * x20*pow(y01, 2) + 2 * pow(x20, 2)*pow(y01, 2) + 2 * pow(y12, 2) - 4 * x01*pow(y12, 2) + 2 * pow(x01, 2)*pow(y12, 2) +
				2 * pow(y01, 2)*pow(y12, 2) - 4 * y01*y20 + 2 * pow(x01, 2)*pow(y20, 2) + 2 * pow(y01, 2)*pow(y20, 2);
			F(1, 2) = 2 * (1 - x01)*y01 + 2 * x01*y01 + 2 * (x12*y01 + (-1 + x01)*y12)*(1 + (-1 + x01)*x12 - y01 * y12) + 2 * (x12*y01 + (-1 + x01)*y12)*((1 - x01)*x12 + y01 * y12) +
				2 * (y01 - x20 * y01 - x01 * y20)*(1 - x01 + x01 * x20 - y01 * y20) + 2 * (y01 - x20 * y01 - x01 * y20)*(x01 - x01 * x20 + y01 * y20);
			F(1, 3) = 2 * (1 - x01)*x01 - 2 * pow(y01, 2) + 2 * (-(x12*y01) + (1 - x01)*y12)*(x12*y01 + (-1 + x01)*y12) + 2 * (1 + (-1 + x01)*x12 - y01 * y12)*((1 - x01)*x12 + y01 * y12) +
				2 * (y01 - x20 * y01 - x01 * y20)*(-y01 + x20 * y01 + x01 * y20) + 2 * (1 - x01 + x01 * x20 - y01 * y20)*(x01 - x01 * x20 + y01 * y20);
			F(2, 0) = 2 * (1 - x01)*x01 - 2 * pow(y01, 2) + 2 * (-(x12*y01) + (1 - x01)*y12)*(x12*y01 + (-1 + x01)*y12) + 2 * (1 + (-1 + x01)*x12 - y01 * y12)*((1 - x01)*x12 + y01 * y12) +
				2 * (y01 - x20 * y01 - x01 * y20)*(-y01 + x20 * y01 + x01 * y20) + 2 * (1 - x01 + x01 * x20 - y01 * y20)*(x01 - x01 * x20 + y01 * y20);
			F(2, 1) = 2 * (1 - x01)*y01 + 2 * x01*y01 + 2 * (x12*y01 + (-1 + x01)*y12)*(1 + (-1 + x01)*x12 - y01 * y12) + 2 * (x12*y01 + (-1 + x01)*y12)*((1 - x01)*x12 + y01 * y12) +
				2 * (y01 - x20 * y01 - x01 * y20)*(1 - x01 + x01 * x20 - y01 * y20) + 2 * (y01 - x20 * y01 - x01 * y20)*(x01 - x01 * x20 + y01 * y20);
			F(2, 2) = 2 + 4 * pow(x01, 2) - 4 * x12 + 4 * x01*x12 + 2 * pow(x12, 2) - 4 * x01*pow(x12, 2) + 2 * pow(x01, 2)*pow(x12, 2) - 4 * pow(x01, 2)*x20 + 2 * pow(x01, 2)*pow(x20, 2) +
				4 * pow(y01, 2) + 2 * pow(x12, 2)*pow(y01, 2) - 4 * x20*pow(y01, 2) + 2 * pow(x20, 2)*pow(y01, 2) - 4 * y01*y12 + 2 * pow(y12, 2) - 4 * x01*pow(y12, 2) +
				2 * pow(x01, 2)*pow(y12, 2) + 2 * pow(y01, 2)*pow(y12, 2) + 2 * pow(x01, 2)*pow(y20, 2) + 2 * pow(y01, 2)*pow(y20, 2);
			F(2, 3) = 2 * (-(x12*y01) + (1 - x01)*y12)*(1 + (-1 + x01)*x12 - y01 * y12) + 2 * (x12*y01 + (-1 + x01)*y12)*(1 + (-1 + x01)*x12 - y01 * y12) +
				2 * (y01 - x20 * y01 - x01 * y20)*(x01 - x01 * x20 + y01 * y20) + 2 * (-y01 + x20 * y01 + x01 * y20)*(x01 - x01 * x20 + y01 * y20);
			F(3, 0) = -2 * (1 - x01)*y01 - 2 * x01*y01 + 2 * (-(x12*y01) + (1 - x01)*y12)*(1 + (-1 + x01)*x12 - y01 * y12) + 2 * (-(x12*y01) + (1 - x01)*y12)*((1 - x01)*x12 + y01 * y12) +
				2 * (-y01 + x20 * y01 + x01 * y20)*(1 - x01 + x01 * x20 - y01 * y20) + 2 * (-y01 + x20 * y01 + x01 * y20)*(x01 - x01 * x20 + y01 * y20);
			F(3, 1) = 2 * (1 - x01)*x01 - 2 * pow(y01, 2) + 2 * (-(x12*y01) + (1 - x01)*y12)*(x12*y01 + (-1 + x01)*y12) + 2 * (1 + (-1 + x01)*x12 - y01 * y12)*((1 - x01)*x12 + y01 * y12) +
				2 * (y01 - x20 * y01 - x01 * y20)*(-y01 + x20 * y01 + x01 * y20) + 2 * (1 - x01 + x01 * x20 - y01 * y20)*(x01 - x01 * x20 + y01 * y20);
			F(3, 2) = 2 * (-(x12*y01) + (1 - x01)*y12)*(1 + (-1 + x01)*x12 - y01 * y12) + 2 * (x12*y01 + (-1 + x01)*y12)*(1 + (-1 + x01)*x12 - y01 * y12) +
				2 * (y01 - x20 * y01 - x01 * y20)*(x01 - x01 * x20 + y01 * y20) + 2 * (-y01 + x20 * y01 + x01 * y20)*(x01 - x01 * x20 + y01 * y20);
			F(3, 3) = 2 + 4 * pow(x01, 2) - 4 * x12 + 4 * x01*x12 + 2 * pow(x12, 2) - 4 * x01*pow(x12, 2) + 2 * pow(x01, 2)*pow(x12, 2) - 4 * pow(x01, 2)*x20 + 2 * pow(x01, 2)*pow(x20, 2) +
				4 * pow(y01, 2) + 2 * pow(x12, 2)*pow(y01, 2) - 4 * x20*pow(y01, 2) + 2 * pow(x20, 2)*pow(y01, 2) - 4 * y01*y12 + 2 * pow(y12, 2) - 4 * x01*pow(y12, 2) +
				2 * pow(x01, 2)*pow(y12, 2) + 2 * pow(y01, 2)*pow(y12, 2) + 2 * pow(x01, 2)*pow(y20, 2) + 2 * pow(y01, 2)*pow(y20, 2);
			F = F.inverse();

			C.resize(4, 6);
			C(0, 0) = -2 * ((1 - x01)*x12 + y01 * y12);
			C(0, 1) = -2 * (-(x12*y01) + (1 - x01)*y12);
			C(0, 2) = -2 * (1 - x01 + x01 * x20 - y01 * y20);
			C(0, 3) = -2 * (-y01 + x20 * y01 + x01 * y20);
			C(0, 4) = -2 * (1 - x01);
			C(0, 5) = 2 * y01;
			C(1, 0) = -2 * (x12*y01 + (-1 + x01)*y12);
			C(1, 1) = -2 * ((1 - x01)*x12 + y01 * y12);
			C(1, 2) = -2 * (y01 - x20 * y01 - x01 * y20);
			C(1, 3) = -2 * (1 - x01 + x01 * x20 - y01 * y20);
			C(1, 4) = -2 * y01;
			C(1, 5) = -2 * (1 - x01);
			C(2, 0) = -2 * (1 + (-1 + x01)*x12 - y01 * y12);
			C(2, 1) = -2 * (x12*y01 + (-1 + x01)*y12);
			C(2, 2) = -2 * (x01 - x01 * x20 + y01 * y20);
			C(2, 3) = -2 * (y01 - x20 * y01 - x01 * y20);
			C(2, 4) = -2 * x01;
			C(2, 5) = -2 * y01;
			C(3, 0) = -2 * (-(x12*y01) + (1 - x01)*y12);
			C(3, 1) = -2 * (1 + (-1 + x01)*x12 - y01 * y12);
			C(3, 2) = -2 * (-y01 + x20 * y01 + x01 * y20);
			C(3, 3) = -2 * (x01 - x01 * x20 + y01 * y20);
			C(3, 4) = 2 * y01;
			C(3, 5) = -2 * x01;
		}
	};

	struct Vertex
	{
		int id;
		Eigen::Vector3f coord;
		bool isU;
		Vertex()
		{

		}
		Vertex(const int &id_)
		{
			id = id_;
		}

		friend bool operator== (const Vertex &v1, const Vertex &v2)
		{
			return v1.id == v2.id;
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

		std::vector<Vertex> vertices;
		std::vector<Triangle> triangles;

		bool Read(const std::string &file_path);
		bool find(int original_id);
		void resetVerticesTo_uq();

		int q_size;
		Eigen::MatrixXf PreComputeScaleFreeMatrix();
		void AdjustScaleToTriangle(const int &triangle_id, std::vector<Eigen::Vector2f> &triangle_points);
		void PreComputeScaleAdjustmentMatrixHf(Eigen::MatrixXf &Hp, Eigen::MatrixXf &D);

	private:
		void computeLocalXY(Triangle &t);
	};
}