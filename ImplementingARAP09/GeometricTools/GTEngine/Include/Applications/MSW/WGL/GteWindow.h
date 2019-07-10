// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.1 (2017/06/23)

#pragma once

#include <Applications/MSW/GteMSWWindow.h>
#include <Graphics/GteGraphicsEngine.h>

namespace gte
{

class GTE_IMPEXP Window : public MSWWindow
{
public:
    struct GTE_IMPEXP Parameters : public MSWWindow::Parameters
    {
        Parameters();

        Parameters(std::wstring const& inTitle,
            int inXOrigin, int inYOrigin, int inXSize, int inYSize);

        // The default value is 0.  When bit 0 is set to 1, a text file
        // is generated that contains the OpenGL driver information.
        UINT deviceCreationFlags;
    };

protected:
    // Abstract base class.  Only WindowSystem may create windows.
    Window(Parameters& parameters);
public:
    virtual ~Window();

protected:
    // This is assigned mBaseEngine, which allows development of the DX12
    // engine independently of DX11 and WGL.
    std::shared_ptr<GraphicsEngine> mEngine;
};

}
