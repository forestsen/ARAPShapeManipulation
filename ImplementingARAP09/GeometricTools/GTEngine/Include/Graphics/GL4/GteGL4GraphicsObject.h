// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteGEObject.h>
#include <Graphics/GL4/GteOpenGL.h>

namespace gte
{

class GTE_IMPEXP GL4GraphicsObject : public GEObject
{
protected:
    // Abstract base class.
    GL4GraphicsObject(GraphicsObject const* gtObject);

public:
    // Member access.
    inline GLuint GetGLHandle() const;

    // Support for debugging.
    virtual void SetName(std::string const& name) override;

protected:
    GLuint mGLHandle;
};

inline GLuint GL4GraphicsObject::GetGLHandle() const
{
    return mGLHandle;
}

}
