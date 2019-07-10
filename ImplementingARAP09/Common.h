#pragma once
#include <Eigen/Dense>

const float w = 1000.0f;
static const Eigen::MatrixXf constantM_boundary =(
	Eigen::MatrixXf(2, 6) <<
	-1, 0, 1, 0, 0, 0,
	0, -1, 0, 1, 0, 0).finished();
static const Eigen::MatrixXf constantM_inner = (
	Eigen::MatrixXf(2, 8) <<
	-1, 0, 1, 0, 0, 0, 0, 0,
	0, -1, 0, 1, 0, 0, 0, 0).finished();