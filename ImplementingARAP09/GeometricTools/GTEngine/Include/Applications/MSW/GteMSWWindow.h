// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Applications/GteWindowBase.h>
#include <Windows.h>

namespace gte
{

class GTE_IMPEXP MSWWindow : public WindowBase
{
public:
    struct GTE_IMPEXP Parameters : public WindowBase::Parameters
    {
        Parameters();

        Parameters(std::wstring const& inTitle,
            int inXOrigin, int inYOrigin, int inXSize, int inYSize);

        HWND handle;
        bool hscrollBar, vscrollBar;
    };

protected:
    // Abstract base class.  Only WindowSystem may create windows.
    MSWWindow(Parameters& parameters);
public:
    virtual ~MSWWindow();

    // Member access.
    inline HWND GetHandle() const;
    virtual void SetTitle(std::wstring const& title) override;

    // Mouse position information.
    virtual void SetMousePosition(int x, int y) override;
    virtual void GetMousePosition(int& x, int& y) const override;

    // Actions to take before the window closes.
    virtual void OnClose() override;

    // Scroll support.  The 'bar' value is 0 for horizontal scroll bars or 1
    // for vertical scroll bars.
    void SetScrollInterval(int bar, int minValue, int maxValue);
    void GetScrollInterval(int bar, int& minValue, int& maxValue) const;
    int SetScrollPosition(int bar, int value);
    int GetScrollPosition(int bar) const;

    // The return value of the increment/decrement functions is the delta of
    // the slider thumb.  If zero, the scroll state did not change.  For the
    // tracking functions, the return value is the current slider thumb
    // position.  A derived-class override must call the base-class function
    // first.
    int OnScrollIncrementLoRes(int bar);
    int OnScrollDecrementLoRes(int bar);
    int OnScrollIncrementHiRes(int bar);
    int OnScrollDecrementHiRes(int bar);
    int OnScrollTracking(int bar);
    int OnScrollEndTracking(int bar);

protected:
    // Standard window information.
    HWND mHandle;

    // Scroll bar support.
    bool mHasScroll[2];
    mutable SCROLLINFO mScrollInfo[2];
    int mScrollLoResDelta[2];
    int mScrollHiResDelta[2];
};


inline HWND MSWWindow::GetHandle() const
{
    return mHandle;
}

}
