// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteGEObject.h>
#include <Graphics/DX11/GteDX11Include.h>

namespace gte
{

class GTE_IMPEXP DX11GraphicsObject : public GEObject
{
public:
    // Abstract base class.
    virtual ~DX11GraphicsObject();
protected:
    DX11GraphicsObject(GraphicsObject const* gtObject);

public:
    // Member access.
    inline ID3D11DeviceChild* GetDXDeviceChild() const;

    // Support for the DX11 debug layer.  Set the name if you want to have
    // ID3D11DeviceChild destruction messages show your name rather than
    // "<unnamed>".  The typical usage is
    //   std::shared_ptr<Texture2> texture = std::make_shared<Texture2>(...);
    //   engine->Bind(texture)->SetName("MyTexture");
    // The virtual override is used to allow derived classes to use the
    // same name for associated resources.
    virtual void SetName(std::string const& name) override;

protected:
    ID3D11DeviceChild* mDXObject;
};

inline ID3D11DeviceChild* DX11GraphicsObject::GetDXDeviceChild() const
{
    return mDXObject;
}

}
