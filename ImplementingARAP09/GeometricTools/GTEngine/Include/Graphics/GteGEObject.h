// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteGraphicsObject.h>

namespace gte
{

class GTE_IMPEXP GEObject
{
public:
    // Abstract base class.
    virtual ~GEObject();
protected:
    GEObject(GraphicsObject const* gtObject);

public:
    // Member access.
    inline GraphicsObject* GetGraphicsObject() const;

    // Support for debugging.
    virtual void SetName(std::string const& name) = 0;
    inline std::string const& GetName() const;

protected:
    GraphicsObject* mGTObject;
    std::string mName;
};

inline GraphicsObject* GEObject::GetGraphicsObject() const
{
    return mGTObject;
}

inline std::string const& GEObject::GetName() const
{
    return mName;
}

}
