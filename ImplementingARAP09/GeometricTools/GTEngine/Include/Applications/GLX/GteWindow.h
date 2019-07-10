// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.2 (2018/02/08)

#pragma once

#include <Applications/GteWindowBase.h>
#include <Graphics/GteGraphicsEngine.h>

// Forward declarations to avoid name conflicts caused by #include-ing X11/Xlib.h.
struct _XDisplay;

namespace gte
{

class GTE_IMPEXP Window : public WindowBase
{
public:
    struct GTE_IMPEXP Parameters : public WindowBase::Parameters
    {
        Parameters();

        Parameters(std::wstring const& inTitle,
            int inXOrigin, int inYOrigin, int inXSize, int inYSize);

        _XDisplay* display;
        unsigned long window;
        unsigned int deviceCreationFlags;
    };

protected:
    // Abstract base class.  Only WindowSystem may create windows.
    friend class WindowSystem;
    Window(Parameters& parameters);
public:
    virtual ~Window();

    virtual void SetTitle(std::wstring const& title);

    // Draw the window.
    void ShowWindow();

    // Mouse position information.
    virtual void SetMousePosition(int x, int y) override;
    virtual void GetMousePosition(int& x, int& y) const override;

    // Actions to take before the window closes.
    virtual void OnClose() override;

    // The event handler.  TODO: This should not be public, but for now
    // WindowSystem needs to call it.  Make WindowSystem a friend?
    enum
    {
        EVT_NONE_PENDING,
        EVT_PROCESSED,
        EVT_QUIT
    };
    int ProcessedEvent();

protected:
    _XDisplay* mDisplay;
    unsigned long mWindow;
    std::array<bool, 8> mButtonDown;
    bool mShiftDown;
    bool mControlDown;
    bool mAltDown;
    bool mCommandDown;
    std::shared_ptr<GraphicsEngine> mEngine;
};

}
