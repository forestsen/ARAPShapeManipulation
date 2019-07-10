// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteTexture.h>

namespace gte
{

class GTE_IMPEXP TextureSingle : public Texture
{
protected:
    // Abstract base class.
    TextureSingle(DFType format, unsigned int numDimensions,
        unsigned int dim0, unsigned int dim1, unsigned int dim2,
        bool hasMipmaps, bool createStorage);

public:
    // Mipmap information.
    inline unsigned int GetOffsetFor(unsigned int level) const;
    inline char const* GetDataFor(unsigned int level) const;
    inline char* GetDataFor(unsigned int level);
    template <typename T> inline T const* GetFor(unsigned int level) const;
    template <typename T> inline T* GetFor(unsigned int level);

public:
    // For use by the Shader class for storing reflection information.
    static int const shaderDataLookup = 4;
};


inline unsigned int TextureSingle::GetOffsetFor(unsigned int level) const
{
    return Texture::GetOffsetFor(0, level);
}

inline char const* TextureSingle::GetDataFor(unsigned int level) const
{
    return Texture::GetDataFor(0, level);
}

inline char* TextureSingle::GetDataFor(unsigned int level)
{
    return Texture::GetDataFor(0, level);
}

template <typename T> inline
T const* TextureSingle::GetFor(unsigned int level) const
{
    return Texture::GetFor<T>(0, level);
}

template <typename T> inline
T* TextureSingle::GetFor(unsigned int level)
{
    return Texture::GetFor<T>(0, level);
}


}
