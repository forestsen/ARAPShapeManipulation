// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.1 (2018/10/20)

#pragma once

#include <Applications/MSW/GteMSWWindow.h>
#include <Graphics/GteGraphicsEngine.h>
#include <Graphics/DX11/GteDX11Include.h>

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
