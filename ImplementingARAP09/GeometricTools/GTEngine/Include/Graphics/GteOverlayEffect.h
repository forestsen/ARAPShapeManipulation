// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Mathematics/GteVector2.h>
#include <Graphics/GteIndexBuffer.h>
#include <Graphics/GteProgramFactory.h>
#include <Graphics/GteSamplerState.h>
#include <Graphics/GteTexture2.h>
#include <Graphics/GteVertexBuffer.h>
#include <Graphics/GteVisualEffect.h>

namespace gte
{

class GTE_IMPEXP OverlayEffect
{
public:
    // Create an overlay that allows you to use a simple color shader or a
    // simple gray-scale shader.
    OverlayEffect(std::shared_ptr<ProgramFactory> const& factory,
        int windowWidth, int windowHeight, int textureWidth, int textureHeight,
        SamplerState::Filter filter, SamplerState::Mode mode0, SamplerState::Mode mode1,
        bool useColorPShader);

    // Create an overlay that uses a pixel shader other than the color or
    // gray default shaders.  The caller is responsible for creating a
    // sampler for the pixel shader.
    OverlayEffect(std::shared_ptr<ProgramFactory> const& factory,
        int windowWidth, int windowHeight, int textureWidth, int textureHeight,
        std::string const& psSource);

    // Access to the overlay rectangle (px,py,pw,ph), which is in client
    // window coordinates.  The upper-left corner of the overlay rectangle
    // is (px,py).  The width and height of the rectangle are pw and ph,
    // respectively.  The width and height must be positive.  The corner
    // (px,py) may be chosen outside the client window, allowing you to clip
    // overlays against the window boundaries.
    inline void SetOverlayRectangle(std::array<int,4> const& rectangle);
    inline std::array<int,4> GetOverlayRectangle() const;

    // Access to the texture rectangle (tx,ty,tw,th), which is in texture
    // image coordinates.  The upper-left corner of the texture rectangle
    // is (tx,ty).  The width and height of the rectangle are tw and th,
    // respectively.  The width and height must be positive.  The corner
    // (tx,ty) may be chosen outside the texture image, but be aware that the
    // colors drawn outside will depend on the sampler state mode.
    void SetTextureRectangle(std::array<int,4> const& rectangle);
    inline std::array<int,4> GetTextureRectangle() const;

    // Joint setting of rectangles (rare case), allowing for a single vertex
    // buffer update.
    void SetRectangles(std::array<int,4> const& overlayRectangle,
        std::array<int,4> const& textureRectangle);

    // Test whether the input (x,y) is contained by the overlay rectangle.
    // This is useful for hit testing in user interfaces.
    bool Contains(int x, int y) const;

    // For DX11Engine::Draw(VertexBuffer*,IndexBuffer*,VisualEffect*).  The
    // vertex buffer is also needed for CPU-to-GPU copies when the overlay
    // and/or texture rectangles are modified.
    inline std::shared_ptr<VisualProgram> const& GetProgram() const;
    inline std::shared_ptr<VertexBuffer> const& GetVertexBuffer() const;
    inline std::shared_ptr<IndexBuffer> const& GetIndexBuffer() const;
    inline std::shared_ptr<VisualEffect> const& GetEffect() const;

    // Dynamically update the overlay textures.  The first function uses
    // the default name "imageTexture".  The second function allows you
    // to set textures when you create an overlay with your own pixel
    // shader.
    void SetTexture(std::shared_ptr<Texture2> const& texture);
    void SetTexture(std::string const& textureName,
        std::shared_ptr<Texture2> const& texture);

protected:
    void Initialize(int windowWidth, int windowHeight, int textureWidth,
        int textureHeight);

    struct Vertex
    {
        Vector2<float> position;
        Vector2<float> tcoord;
    };

    void UpdateVertexBuffer();

    float mWindowWidth, mWindowHeight;
    float mInvTextureWidth, mInvTextureHeight;
    int mFactoryAPI;
    std::array<int,4> mOverlayRectangle;
    std::array<int,4> mTextureRectangle;
    std::shared_ptr<VertexBuffer> mVBuffer;
    std::shared_ptr<IndexBuffer> mIBuffer;
    std::shared_ptr<VisualProgram> mProgram;
    std::shared_ptr<VisualEffect> mEffect;

    // Shader source code as strings.
    static std::string const msGLSLVSSource;
    static std::string const msGLSLPSColorSource;
    static std::string const msGLSLPSGraySource;
    static std::string const msHLSLVSSource;
    static std::string const msHLSLPSColorSource;
    static std::string const msHLSLPSGraySource;
    static std::string const* msVSSource[ProgramFactory::PF_NUM_API];
    static std::string const* msPSColorSource[ProgramFactory::PF_NUM_API];
    static std::string const* msPSGraySource[ProgramFactory::PF_NUM_API];
};


inline void OverlayEffect::SetOverlayRectangle(
    std::array<int, 4> const& rectangle)
{
    mOverlayRectangle = rectangle;
    UpdateVertexBuffer();
}

inline std::array<int, 4> OverlayEffect::GetOverlayRectangle() const
{
    return mOverlayRectangle;
}

inline std::array<int, 4> OverlayEffect::GetTextureRectangle() const
{
    return mTextureRectangle;
}

inline std::shared_ptr<VisualProgram> const&
OverlayEffect::GetProgram() const
{
    return mProgram;
}

inline std::shared_ptr<VertexBuffer> const&
OverlayEffect::GetVertexBuffer() const
{
    return mVBuffer;
}

inline std::shared_ptr<IndexBuffer> const&
OverlayEffect::GetIndexBuffer() const
{
    return mIBuffer;
}

inline std::shared_ptr<VisualEffect> const&
OverlayEffect::GetEffect() const
{
    return mEffect;
}


}
