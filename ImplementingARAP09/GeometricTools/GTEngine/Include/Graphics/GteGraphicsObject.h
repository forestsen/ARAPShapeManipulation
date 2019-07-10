// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <GTEngineDEF.h>
#include <memory>
#include <mutex>
#include <set>
#include <string>

namespace gte
{

// The current hierarchy of GTEngine 6 graphics objects is
//  GraphicsObject
//      Resource
//          Buffer
//              ConstantBuffer
//              TextureBuffer
//              VertexBuffer
//              IndexBuffer
//              StructuredBuffer
//              TypedBuffer
//              RawBuffer
//              IndirectArgumentsBuffer
//          Texture
//              TextureSingle
//                  Texture1
//                  Texture2
//                      TextureRT
//                      TextureDS
//                  Texture3
//              TextureArray
//                  Texture1Array
//                  Texture2Array
//                  TextureCube
//                  TextureCubeArray
//      Shader
//          VertexShader
//          GeometryShader
//          PixelShader
//          ComputeShader
//      DrawingState
//          SamplerState
//          BlendState
//          DepthStencilState
//          RasterizerState
//
// The corresponding hierarchy of GTEngine DX11* bridge objects is the same
// but with class names prepended by DX11 (e.g. DX11GraphicsObject).
//
// The hierarchy of DX11 interfaces is the following
//  ID3D11DeviceChild
//      ID3D11Resource
//          ID3D11Buffer
//          ID3D11Texture1D
//          ID3D11Texture2D
//          ID3D11Texture3D
//      ID3D11VertexShader
//      ID3D11GeometryShader
//      ID3D11PixelShader
//      ID3D11ComputeShader
//      ID3D11SamplerState
//      ID3D11BlendState
//      ID3D11DepthStencilState
//      ID3D11RasterizerState
//
// The GraphicsObjectType enumeration is for run-time type information.
// The typeid() mechanism does not work in DX11Engine::Unbind(...), because
// the listeners receive 'this' from a base class during a destructor call.

enum GTE_IMPEXP GraphicsObjectType
{
    GT_GRAPHICS_OBJECT,  // abstract
        GT_RESOURCE,  // abstract
            GT_BUFFER,  // abstract
                GT_CONSTANT_BUFFER,
                GT_TEXTURE_BUFFER,
                GT_VERTEX_BUFFER,
                GT_INDEX_BUFFER,
                GT_STRUCTURED_BUFFER,
                GT_TYPED_BUFFER,
                GT_RAW_BUFFER,
                GT_INDIRECT_ARGUMENTS_BUFFER,
            GT_TEXTURE,  // abstract
                GT_TEXTURE_SINGLE,  // abstract
                    GT_TEXTURE1,
                    GT_TEXTURE2,
                        GT_TEXTURE_RT,
                        GT_TEXTURE_DS,
                    GT_TEXTURE3,
                GT_TEXTURE_ARRAY,  // abstract
                    GT_TEXTURE1_ARRAY,
                    GT_TEXTURE2_ARRAY,
                    GT_TEXTURE_CUBE,
                    GT_TEXTURE_CUBE_ARRAY,
        GT_SHADER,  // abstract
            GT_VERTEX_SHADER,
            GT_GEOMETRY_SHADER,
            GT_PIXEL_SHADER,
            GT_COMPUTE_SHADER,
        GT_DRAWING_STATE,  // abstract
            GT_SAMPLER_STATE,
            GT_BLEND_STATE,
            GT_DEPTH_STENCIL_STATE,
            GT_RASTERIZER_STATE,
    GT_NUM_TYPES
};

class GTE_IMPEXP GraphicsObject
{
public:
    // This is an abstract base class that is used for bridging GTEngine
    // graphics objects with DX11 graphics objects.  The latter are
    // represented by the ID3D11DeviceChild interface.
    virtual ~GraphicsObject();

    // Run-time type information.
    inline GraphicsObjectType GetType() const;
    inline bool IsBuffer() const;
    inline bool IsTexture() const;
    inline bool IsTextureArray() const;
    inline bool IsShader() const;
    inline bool IsDrawingState() const;

    // Naming support, used in the DX11 debug layer.  The default name is "".
    // If you want the name to show up in the DX11 destruction messages when
    // the associated DX11GraphicsObject is destroyed, set the name to
    // something other than "".
    inline void SetName(std::string const& name);
    inline std::string const& GetName() const;

    // Listeners subscribe to receive notification when a GraphicsObject is
    // about to be destroyed.  The intended use is for the DX11Engine objects
    // to destroy corresponding ID3D11DeviceChild objects.
    class GTE_IMPEXP ListenerForDestruction
    {
    public:
        virtual ~ListenerForDestruction() { /**/ }
        ListenerForDestruction() { /**/ }
        virtual void OnDestroy(GraphicsObject const*) { /**/ }
    };

    static void SubscribeForDestruction(std::shared_ptr<ListenerForDestruction> const& listener);
    static void UnsubscribeForDestruction(std::shared_ptr<ListenerForDestruction> const& listener);

protected:
    // This is an abstract base class.
    GraphicsObject();

    GraphicsObjectType mType;
    std::string mName;

private:
    // Support for listeners for destruction (LFD).
    static std::mutex msLFDMutex;
    static std::set<std::shared_ptr<ListenerForDestruction>> msLFDSet;
};

inline GraphicsObjectType GraphicsObject::GetType() const
{
    return mType;
}

inline bool GraphicsObject::IsBuffer() const
{
    return GT_BUFFER <= mType && mType <= GT_INDIRECT_ARGUMENTS_BUFFER;
}

inline bool GraphicsObject::IsTexture() const
{
    return GT_TEXTURE_SINGLE <= mType && mType <= GT_TEXTURE3;
}

inline bool GraphicsObject::IsTextureArray() const
{
    return GT_TEXTURE_ARRAY <= mType && mType <= GT_TEXTURE_CUBE_ARRAY;
}

inline bool GraphicsObject::IsShader() const
{
    return GT_SHADER <= mType && mType <= GT_COMPUTE_SHADER;
}

inline bool GraphicsObject::IsDrawingState() const
{
    return GT_DRAWING_STATE <= mType && mType <= GT_RASTERIZER_STATE;
}

inline void GraphicsObject::SetName(std::string const& name)
{
    mName = name;
}

inline std::string const& GraphicsObject::GetName() const
{
    return mName;
}

}
