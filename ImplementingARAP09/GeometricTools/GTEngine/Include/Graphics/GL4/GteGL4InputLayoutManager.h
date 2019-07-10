// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <LowLevel/GteThreadSafeMap.h>
#include <Graphics/GteGEInputLayoutManager.h>
#include <Graphics/GL4/GteGL4InputLayout.h>

namespace gte
{

class GTE_IMPEXP GL4InputLayoutManager : public GEInputLayoutManager
{
public:
    // Construction and destruction.
    virtual ~GL4InputLayoutManager();
    GL4InputLayoutManager();

    // Management functions.  The Unbind(vbuffer) removes all layouts that
    // involve vbuffer.  The Unbind(vshader) is stubbed out because GL4 does
    // not require it, but we wish to have Unbind(GraphicsObject const*) as
    // a base-class GraphicsEngine function.
    GL4InputLayout* Bind(GLuint programHandle, GLuint vbufferHandle, VertexBuffer const* vbuffer);
    virtual bool Unbind(VertexBuffer const* vbuffer) override;
    virtual bool Unbind(Shader const* vshader) override;
    virtual void UnbindAll() override;
    virtual bool HasElements() const override;

private:
    typedef std::pair<VertexBuffer const*, GLuint> VBPPair;

    class LayoutMap : public ThreadSafeMap<VBPPair, std::shared_ptr<GL4InputLayout>>
    {
    public:
        virtual ~LayoutMap();
        LayoutMap();

        void GatherMatch(VertexBuffer const* vbuffer, std::vector<VBPPair>& matches);
    };

    LayoutMap mMap;
};

}
