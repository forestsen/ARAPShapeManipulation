// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteBlendState.h>
#include <Graphics/GteBuffer.h>
#include <Graphics/GteDepthStencilState.h>
#include <Graphics/GteFont.h>
#include <Graphics/GteOverlayEffect.h>
#include <Graphics/GteRasterizerState.h>
#include <Graphics/GteTextureSingle.h>
#include <array>
#include <memory>

namespace gte
{

class GTE_IMPEXP BaseEngine
{
public:
    // Abstract base class.
    virtual ~BaseEngine();

    // Viewport management.  The measurements are in window coordinates.  The
    // origin of the window is (x,y), the window width is w, and the window
    // height is h.  The depth range for the view volume is [zmin,zmax].  The
    // DX12 viewport is left-handed with origin the upper-left corner of the
    // window, the x-axis is directed rightward, the y-axis is directed
    // downward, and the depth range is a subset of [0,1].
    virtual void SetViewport(int x, int y, int w, int h) = 0;
    virtual void GetViewport(int& x, int& y, int& w, int& h) const = 0;
    virtual void SetDepthRange(float zmin, float zmax) = 0;
    virtual void GetDepthRange(float& zmin, float& zmax) const = 0;

    // Window resizing.
    virtual bool Resize(unsigned int w, unsigned int h) = 0;

    // Support for clearing the color, depth, and stencil back buffers.
    inline void SetClearColor(std::array<float, 4> const& clearColor);
    inline void SetClearDepth(float clearDepth);
    inline void SetClearStencil(unsigned int clearStencil);
    inline std::array<float, 4> const& GetClearColor() const;
    inline float GetClearDepth() const;
    inline unsigned int GetClearStencil() const;
    virtual void DisplayColorBuffer(unsigned int syncInterval) = 0;

    // Support for bitmapped fonts used in text rendering.  The default font
    // is Arial (height 18, no italics, no bold).
    virtual void SetFont(std::shared_ptr<Font> const& font);
    inline std::shared_ptr<Font> const& GetFont() const;
    inline void SetDefaultFont();
    inline std::shared_ptr<Font> const& GetDefaultFont() const;

    // Global drawing state.  The default states are shown in GteBlendState.h,
    // GteDepthStencil.h, and GteRasterizerState.h.
    virtual void SetBlendState(std::shared_ptr<BlendState> const& state) = 0;
    inline std::shared_ptr<BlendState> const& GetBlendState() const;
    inline void SetDefaultBlendState();
    inline std::shared_ptr<BlendState> const& GetDefaultBlendState() const;

    virtual void SetDepthStencilState(std::shared_ptr<DepthStencilState> const& state) = 0;
    inline std::shared_ptr<DepthStencilState> const& GetDepthStencilState() const;
    inline void SetDefaultDepthStencilState();
    inline std::shared_ptr<DepthStencilState> const& GetDefaultDepthStencilState() const;

    virtual void SetRasterizerState(std::shared_ptr<RasterizerState> const& state) = 0;
    inline std::shared_ptr<RasterizerState> const& GetRasterizerState() const;
    inline void SetDefaultRasterizerState();
    inline std::shared_ptr<RasterizerState> const& GetDefaultRasterizerState() const;

    // Support for copying from CPU to GPU via mapped memory.
    virtual bool Update(std::shared_ptr<Buffer> const& buffer) = 0;
    virtual bool Update(std::shared_ptr<TextureSingle> const& texture) = 0;

    // TODO: Include this here for now until DX12 engine has drawing
    // encapsulated.
    virtual uint64_t Draw(std::shared_ptr<OverlayEffect> const& effect) = 0;

protected:
    // Abstract base class.  Base engine objects may not be copied.
    BaseEngine();
    BaseEngine(BaseEngine const&) = delete;
    BaseEngine& operator=(BaseEngine const&) = delete;

    // Helpers for construction and destruction.
    void CreateDefaultGlobalState();
    virtual void DestroyDefaultGlobalState();

    // The window size.
    unsigned int mXSize, mYSize;

    // Clear values.
    std::array<float, 4> mClearColor;
    float mClearDepth;
    unsigned int mClearStencil;

    // Fonts for text rendering.
    std::shared_ptr<Font> mDefaultFont;
    std::shared_ptr<Font> mActiveFont;

    // Global state.
    std::shared_ptr<BlendState> mDefaultBlendState;
    std::shared_ptr<BlendState> mActiveBlendState;
    std::shared_ptr<DepthStencilState> mDefaultDepthStencilState;
    std::shared_ptr<DepthStencilState> mActiveDepthStencilState;
    std::shared_ptr<RasterizerState> mDefaultRasterizerState;
    std::shared_ptr<RasterizerState> mActiveRasterizerState;
};


inline void BaseEngine::SetClearColor(std::array<float, 4> const& clearColor)
{
    mClearColor = clearColor;
}

inline void BaseEngine::SetClearDepth(float clearDepth)
{
    mClearDepth = clearDepth;
}

inline void BaseEngine::SetClearStencil(unsigned int clearStencil)
{
    mClearStencil = clearStencil;
}

inline std::array<float, 4> const& BaseEngine::GetClearColor() const
{
    return mClearColor;
}

inline float BaseEngine::GetClearDepth() const
{
    return mClearDepth;
}

inline unsigned int BaseEngine::GetClearStencil() const
{
    return mClearStencil;
}

inline std::shared_ptr<Font> const& BaseEngine::GetFont() const
{
    return mActiveFont;
}

inline void BaseEngine::SetDefaultFont()
{
    SetFont(mDefaultFont);
}

inline std::shared_ptr<Font> const& BaseEngine::GetDefaultFont() const
{
    return mDefaultFont;
}

inline std::shared_ptr<BlendState> const& BaseEngine::GetBlendState() const
{
    return mActiveBlendState;
}

inline void BaseEngine::SetDefaultBlendState()
{
    SetBlendState(mDefaultBlendState);
}

inline std::shared_ptr<BlendState> const& BaseEngine::GetDefaultBlendState() const
{
    return mDefaultBlendState;
}

inline std::shared_ptr<DepthStencilState> const& BaseEngine::GetDepthStencilState() const
{
    return mActiveDepthStencilState;
}

inline void BaseEngine::SetDefaultDepthStencilState()
{
    SetDepthStencilState(mDefaultDepthStencilState);
}

inline std::shared_ptr<DepthStencilState> const& BaseEngine::GetDefaultDepthStencilState() const
{
    return mDefaultDepthStencilState;
}

inline std::shared_ptr<RasterizerState> const& BaseEngine::GetRasterizerState() const
{
    return mActiveRasterizerState;
}

inline void BaseEngine::SetDefaultRasterizerState()
{
    SetRasterizerState(mDefaultRasterizerState);
}

inline std::shared_ptr<RasterizerState> const& BaseEngine::GetDefaultRasterizerState() const
{
    return mDefaultRasterizerState;
}

}
