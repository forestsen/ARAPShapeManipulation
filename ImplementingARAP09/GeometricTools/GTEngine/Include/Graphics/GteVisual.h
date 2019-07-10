// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.1 (2019/03/06)

#pragma once

#include <Graphics/GteIndexBuffer.h>
#include <Graphics/GteSpatial.h>
#include <Graphics/GteVertexBuffer.h>
#include <Graphics/GteVisualEffect.h>

namespace gte
{
    class GTE_IMPEXP Visual : public Spatial
    {
    public:
        // Construction and destruction.
        virtual ~Visual();
        Visual(
            std::shared_ptr<VertexBuffer> const& vbuffer =
            std::shared_ptr<VertexBuffer>(),
            std::shared_ptr<IndexBuffer> const& ibuffer =
            std::shared_ptr<IndexBuffer>(),
            std::shared_ptr<VisualEffect> const& effect =
            std::shared_ptr<VisualEffect>());

        // Member access.
        inline void SetVertexBuffer(std::shared_ptr<VertexBuffer> const& vbuffer)
        {
            mVBuffer = vbuffer;
        }

        inline void SetIndexBuffer(std::shared_ptr<IndexBuffer> const& ibuffer)
        {
            mIBuffer = ibuffer;
        }

        inline void SetEffect(std::shared_ptr<VisualEffect> const& effect)
        {
            mEffect = effect;
        }

        inline std::shared_ptr<VertexBuffer> const& GetVertexBuffer() const
        {
            return mVBuffer;
        }

        inline std::shared_ptr<IndexBuffer> const& GetIndexBuffer() const
        {
            return mIBuffer;
        }

        inline std::shared_ptr<VisualEffect> const& GetEffect() const
        {
            return mEffect;
        }

        // Support for geometric updates.
        bool UpdateModelBound();
        bool UpdateModelNormals();

        // Public member access.
        BoundingSphere<float> modelBound;

    protected:
        // Support for geometric updates.
        inline virtual void UpdateWorldBound()
        {
            modelBound.TransformBy(worldTransform, worldBound);
        }

        // Support for hierarchical culling.
        inline virtual void GetVisibleSet(Culler& culler,
            std::shared_ptr<Camera> const& camera, bool noCull)
        {
            (void)camera;
            (void)noCull;
            culler.Insert(this);
        }

        std::shared_ptr<VertexBuffer> mVBuffer;
        std::shared_ptr<IndexBuffer> mIBuffer;
        std::shared_ptr<VisualEffect> mEffect;
    };
}
