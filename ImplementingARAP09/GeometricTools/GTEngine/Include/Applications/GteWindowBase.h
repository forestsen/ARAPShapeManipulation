// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.1 (2017/06/23)

#pragma once

#include <Applications/GteEnvironment.h>
#include <Applications/GteOnIdleTimer.h>
#include <Graphics/GteBaseEngine.h>
#include <Graphics/GteProgramFactory.h>

namespace gte
{

class GTE_IMPEXP WindowBase
{
public:
    // All parameters for constructing windows are in this structure.  Derived
    // classes may define nested classes to derive from this.  The creation by
    // WindowSystem requires you to pass such a structure.
    struct GTE_IMPEXP Parameters
    {
        Parameters();

        Parameters(std::wstring const& inTitle,
            int inXOrigin, int inYOrigin, int inXSize, int inYSize);

        std::wstring title;
        int xOrigin, yOrigin, xSize, ySize;
        bool allowResize, created, useDepth24Stencil8;
        std::shared_ptr<BaseEngine> engine;
        std::shared_ptr<ProgramFactory> factory;
    };

protected:
    // Abstract base class.  Only WindowSystem may create windows.
    WindowBase(Parameters& parameters);
public:
    virtual ~WindowBase();

    // Member access.
    virtual void SetTitle(std::wstring const& title);
    inline std::wstring GetTitle() const;
    inline int GetXOrigin() const;
    inline int GetYOrigin() const;
    inline int GetXSize() const;
    inline int GetYSize() const;
    inline bool IsMinimized() const;
    inline bool IsMaximized() const;
    inline float GetAspectRatio() const;

    // Display callbacks.
    virtual void OnMove(int x, int y);
    virtual bool OnResize(int xSize, int ySize);
    virtual void OnMinimize();
    virtual void OnMaximize();
    virtual void OnDisplay();
    virtual void OnIdle();

    // Keyboard callbacks.  OnCharPress allows you to distinguish between
    // upper-case and lower-case letters; OnKeyDown and OnKeyUp do not.
    // For OnCharPress, pressing KEY_ESCAPE terminates the application.
    // Pressing ' ' resets the application timer.
    virtual bool OnCharPress(unsigned char key, int x, int y);
    virtual bool OnKeyDown(int key, int x, int y);
    virtual bool OnKeyUp(int key, int x, int y);

    // Mouse callbacks and state information.
    // TODO: HACK FOR NOW.  Once these are removed, all the sample applications
    // must have their signatures changed.
    typedef int MouseButton;
    typedef int MouseState;
    // END TODO;
    virtual bool OnMouseClick(int button, int state, int x, int y, unsigned int modifiers);
    virtual bool OnMouseMotion(int button, int x, int y, unsigned int modifiers);
    virtual bool OnMouseWheel(int delta, int x, int y, unsigned int modifiers);
    virtual void SetMousePosition(int x, int y);
    virtual void GetMousePosition(int& x, int& y) const;

    // Actions to take before the window closes.
    virtual void OnClose();

    // Key identifiers.  These are platform-specific, so classes that
    // implement the WindowApplication interfaces must define these
    // variables.  They are not defined by WindowApplication.
    static int const KEY_ESCAPE;
    static int const KEY_LEFT;
    static int const KEY_RIGHT;
    static int const KEY_UP;
    static int const KEY_DOWN;
    static int const KEY_HOME;
    static int const KEY_END;
    static int const KEY_PAGE_UP;
    static int const KEY_PAGE_DOWN;
    static int const KEY_INSERT;
    static int const KEY_DELETE;
    static int const KEY_F1;
    static int const KEY_F2;
    static int const KEY_F3;
    static int const KEY_F4;
    static int const KEY_F5;
    static int const KEY_F6;
    static int const KEY_F7;
    static int const KEY_F8;
    static int const KEY_F9;
    static int const KEY_F10;
    static int const KEY_F11;
    static int const KEY_F12;
    static int const KEY_BACKSPACE;
    static int const KEY_TAB;
    static int const KEY_ENTER;
    static int const KEY_RETURN;

    // Keyboard modifiers.
    static int const KEY_SHIFT;
    static int const KEY_CONTROL;
    static int const KEY_ALT;
    static int const KEY_COMMAND;

    // Mouse buttons.
    static int const MOUSE_NONE;
    static int const MOUSE_LEFT;
    static int const MOUSE_MIDDLE;
    static int const MOUSE_RIGHT;

    // Mouse state.
    static int const MOUSE_UP;
    static int const MOUSE_DOWN;

    // Mouse modifiers.
    static int const MODIFIER_CONTROL;
    static int const MODIFIER_LBUTTON;
    static int const MODIFIER_MBUTTON;
    static int const MODIFIER_RBUTTON;
    static int const MODIFIER_SHIFT;

protected:
    // Get the GTE_PATH environment variable has been set.  Derived classes
    // use this variable to ensure that any input data sets necessary for the
    // sample application exist.  If the function returns "", the GTE_PATH
    // variable has not been set and the derived class should fail gracefully
    // by setting parameters.created to 'false' and returning.
    std::string GetGTEPath();

    // Standard window information.
    std::wstring mTitle;
    int mXOrigin, mYOrigin, mXSize, mYSize;
    bool mAllowResize;
    bool mIsMinimized;
    bool mIsMaximized;

    Environment mEnvironment;
    OnIdleTimer mTimer;

    // Graphics device and camera.
    std::shared_ptr<BaseEngine> mBaseEngine;
    std::shared_ptr<ProgramFactory> mProgramFactory;
};


inline std::wstring WindowBase::GetTitle() const
{
    return mTitle;
}

inline int WindowBase::GetXOrigin() const
{
    return mXOrigin;
}

inline int WindowBase::GetYOrigin() const
{
    return mYOrigin;
}

inline int WindowBase::GetXSize() const
{
    return mXSize;
}

inline int WindowBase::GetYSize() const
{
    return mYSize;
}

inline bool WindowBase::IsMinimized() const
{
    return mIsMinimized;
}

inline bool WindowBase::IsMaximized() const
{
    return mIsMaximized;
}

inline float WindowBase::GetAspectRatio() const
{
    return (float)mXSize / (float)mYSize;
}

}
