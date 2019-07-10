// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.22.0 (2019/02/02)

#pragma once

#include <Mathematics/GteVector3.h>
#include <Graphics/GteController.h>
#include <Graphics/GteVertexBuffer.h>

// There are N morph targets, each target an array of M points.  The points
// are organized in a 2-dimensional array X[N][M].  The target index n
// satisfies 0 <= n < N and the vertex index m satisfies 0 <= m < M.
//
// The morphed object is a weighted combination of the targets, the weights
// stored as the 1-dimensional array F[N], where F[n] is in [0,1] and
// sum_{n=0}^{N-1} F[n] = 1.  Each vertex of the combination is
// sum_{n=0}^{N-1} F[n] * X[n][m], where X[n][m] is a vertex of the n-th
// target.  The weight F[n] applies to all points in the target; that is, the
// summation defines the combination for all X[n][m] where 0 <= m < M.
//
// The morphed object varies over time t by making the weights in the weighted
// combination dependent on time.  Generally, the weights are represented by
// an N-dimensional curve parameterized by time, say, G(t) which is an
// N-tuple for each time t and for which G(t)[n] is in [0,1] and
// sum_{n=0}^{N-1} G(t)[n] = 1.  The vertex combinations are
// sum_{n=0}^{N-1} G(t)[n] * X[n][m] for 0 <= m < N.
//
// The simplest curve to choose for the weights is an N-dimensional polyline
// with K samples.  The sample times are a 1-dimensional array T[K] for
// 0 <= k < K and T[0] < T[1] < ... < T[K-1].  The index k is called a "key."
// The sample N-tuples at time T[k] are weights W[k][n], where 0 <= k < K and
// 0 <= n < N.  Given a continuous time t in the interval [T[k],T[k+1]], the
// normalized time associated with t is s = (t - T[k]) / (T[k+1] - T[k]) and
// is in [0,1].  The weights to use are w[n] = (1-s) * W[k][n] + s * W[k+1][n]
// for 0 <= n < N, so the combination is sum_{n=0}^{N-1} w[n] * X[n][m].

namespace gte
{
    class GTE_IMPEXP MorphController : public Controller
    {
    public:
        // Construction and destruction.  The numbers of vertices, morph
        // targets and times are constant for the lifetime of the object.
        // The constructor allocates the storage for these, but the vertices,
        // times and weights must all be assigned by the appropriate Set*(...)
        // member accessors.
        typedef std::function<void(std::shared_ptr<VertexBuffer> const&)> Updater;

        virtual ~MorphController();

        MorphController(size_t numTargets, size_t numVertices, size_t numTimes, Updater const& postUpdate);

        // Deferred construction.
        void SetVertices(size_t target, std::vector<Vector3<float>> const& vertices);
        void SetTimes(std::vector<float> const& times);
        void SetWeights(size_t key, std::vector<float> const& weights);

        // Member access.  After calling the constructor, you must set the vertex
        // arrays, times, and weights using these functions.
        inline size_t GetNumTargets() const
        {
            return mNumTargets;
        }

        inline size_t GetNumVertices() const
        {
            return mNumVertices;
        }

        inline size_t GetNumTimes() const
        {
            return mNumTimes;
        }

        inline std::vector<Vector3<float>> const& GetAllVertices() const
        {
            return mVertices;
        }

        inline std::vector<float> const& GetAllTimes() const
        {
            return mTimes;
        }

        inline std::vector<float> const& GetAllWeights() const
        {
            return mWeights;
        }

        void GetVertices(size_t target, std::vector<Vector3<float>>& vertices);
        void GetTimes(std::vector<float>& times);
        void GetWeights(size_t key, std::vector<float>& weights);

        // The animation update.  The application time is in milliseconds.
        virtual bool Update(double applicationTime);

    protected:
        // Override the base-class member function in order to verify that
        // the object is Visual with a vertex format and vertex buffer that
        // satisfy the preconditions of the MorphController.
        virtual void SetObject(ControlledObject* object) override;

        // Lookup on bounding keys.
        void GetKeyInfo(float ctrlTime, float& normTime, size_t& key0, size_t& key1);

        size_t mNumTargets;                     // N
        size_t mNumVertices;                    // M
        size_t mNumTimes;                       // K
        std::vector<Vector3<float>> mVertices;  // X[N][M], row-major
        std::vector<float> mTimes;              // T[K]
        std::vector<float> mWeights;            // W[K][N]

        // Support for O(1) lookup on bounding times of a specified time
        // that is increasing during execution.
        size_t mLastIndex;

        // The caller specifies an update function that is used to copy the
        // vertex buffer of mObject from the CPU to GPU.
        Updater mPostUpdate;
    };
}
