// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteDataFormat.h>
#include <Graphics/GteResource.h>
#include <array>
#include <functional>
#include <vector>

namespace gte
{

class GTE_IMPEXP Texture : public Resource
{
protected:
    // Abstract base class.  All items in the array have the same format,
    // number of dimensions, dimension values, and mipmap status.
    Texture(unsigned int numItems, DFType format, unsigned int numDimensions,
        unsigned int dim0, unsigned int dim1, unsigned int dim2,
        bool hasMipmaps, bool createStorage);

public:
    // Member access.
    inline unsigned int GetNumItems() const;
    inline DFType GetFormat() const;
    inline unsigned int GetNumDimensions() const;
    inline unsigned int GetDimension(int i) const;

    // Subresource information.
    struct Subresource
    {
        unsigned int item;
        unsigned int level;
        char* data;
        unsigned int rowPitch;
        unsigned int slicePitch;
    };

    // Mipmap information.
    enum { MAX_MIPMAP_LEVELS = 16 };
    inline bool HasMipmaps() const;
    inline unsigned int GetNumLevels() const;
    inline unsigned int GetDimensionFor(unsigned int level, int i) const;
    inline unsigned int GetNumElementsFor(unsigned int level) const;
    inline unsigned int GetNumBytesFor(unsigned int level) const;
    inline unsigned int GetOffsetFor(unsigned int item,
        unsigned int level) const;
    inline char const* GetDataFor(unsigned int item,
        unsigned int level) const;
    inline char* GetDataFor(unsigned int item, unsigned int level);
    template <typename T> inline T const* GetFor(unsigned int item,
        unsigned int level) const;
    template <typename T> inline T* GetFor(unsigned int item,
        unsigned int level);

    // Subresource indexing:  index = numLevels*item + level
    inline unsigned int GetNumSubresources() const;
    unsigned int GetIndex(unsigned int item, unsigned int level) const;
    Subresource GetSubresource(unsigned int index) const;

    // Request that the GPU compute mipmap levels when the base-level texture
    // data is modified.  The AutogenerateMipmaps call should be made before
    // binding the texture to the engine.  If the texture does not have mipmaps,
    // the AutogenerateMipmaps call will not set mAutogenerateMipmaps to true.
    void AutogenerateMipmaps();
    inline bool WantAutogenerateMipmaps() const;

protected:
    // Support for computing the numElements parameter for the Resource
    // constructor.  This is necessary when mipmaps are requested.
    static unsigned int GetTotalElements(unsigned int numItems,
        unsigned int dim0, unsigned int dim1, unsigned int dim2,
        bool hasMipmaps);

    unsigned int mNumItems;
    DFType mFormat;
    unsigned int mNumDimensions;
    unsigned int mNumLevels;
    std::array<std::array<unsigned int, 3>, MAX_MIPMAP_LEVELS> mLDimension;
    std::array<unsigned int, MAX_MIPMAP_LEVELS> mLNumBytes;
    std::vector<std::array<unsigned int, MAX_MIPMAP_LEVELS>> mLOffset;
    bool mHasMipmaps;
    bool mAutogenerateMipmaps;
};

typedef std::function<void(std::shared_ptr<Texture> const&)> TextureUpdater;
typedef std::function<void(std::shared_ptr<Texture> const&, unsigned int)> TextureLevelUpdater;

inline unsigned int Texture::GetNumItems() const
{
    return mNumItems;
}

inline DFType Texture::GetFormat() const
{
    return mFormat;
}

inline unsigned int Texture::GetNumDimensions() const
{
    return mNumDimensions;
}

inline unsigned int Texture::GetDimension(int i) const
{
    return mLDimension[0][i];
}

inline bool Texture::HasMipmaps() const
{
    return mHasMipmaps;
}

inline unsigned int Texture::GetNumLevels() const
{
    return mNumLevels;
}

inline unsigned int Texture::GetDimensionFor(unsigned int level, int i)
const
{
    return mLDimension[level][i];
}

inline unsigned int Texture::GetNumElementsFor(unsigned int level) const
{
    return mLNumBytes[level] / mElementSize;
}

inline unsigned int Texture::GetNumBytesFor(unsigned int level) const
{
    return mLNumBytes[level];
}

inline unsigned int Texture::GetOffsetFor(unsigned int item,
    unsigned int level) const
{
    return mLOffset[item][level];
}

inline char const* Texture::GetDataFor(unsigned int item,
    unsigned int level) const
{
    return mData ? (mData + mLOffset[item][level]) : nullptr;
}

inline char* Texture::GetDataFor(unsigned int item, unsigned int level)
{
    return mData ? (mData + mLOffset[item][level]) : nullptr;
}

template <typename T> inline T
const* Texture::GetFor(unsigned int item, unsigned int level) const
{
    return reinterpret_cast<T const*>(GetDataFor(item, level));
}

template <typename T> inline
T* Texture::GetFor(unsigned int item, unsigned int level)
{
    return reinterpret_cast<T*>(GetDataFor(item, level));
}

inline unsigned int Texture::GetNumSubresources() const
{
    return mNumItems * mNumLevels;
}

inline bool Texture::WantAutogenerateMipmaps() const
{
    return mAutogenerateMipmaps;
}


}
