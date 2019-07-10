// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteTextureArray.h>

namespace gte
{

class GTE_IMPEXP TextureCubeArray : public TextureArray
{
public:
    // Construction.  Cube maps must be square; the 'length' parameter is the
    // shared value for width and height of a face.  The 'numCubes' is the
    // number of 6-tuples of cube maps.
    TextureCubeArray(unsigned int numCubes, DFType format, unsigned int length,
        bool hasMipmaps = false, bool createStorage = true);

    // Member access.
    unsigned int GetNumCubes() const;

    // The texture width and height are the same value.
    unsigned int GetLength() const;

    // Faces for all the of the cubes are stored contiguously in one large array so
    // GetNumItems() will return a number that is the same as 6*GetNumCubes().
    // These methods allow mapping between the array itemIndex and the corresponding
    // (cubeIndex, faceIndex) pair.
    inline unsigned int GetItemIndexFor(unsigned int cube, unsigned int face) const;
    inline unsigned int GetCubeIndexFor(unsigned int item) const;
    inline unsigned int GetFaceIndexFor(unsigned int item) const;

    // Mipmap information.
    inline unsigned int GetOffsetFor(unsigned int cube, unsigned int face, unsigned int level) const;
    inline char const* GetDataFor(unsigned int cube, unsigned int face, unsigned int level) const;
    inline char* GetDataFor(unsigned int cube, unsigned int face, unsigned int level);
    template <typename T> inline T const* GetFor(unsigned int cube, unsigned int face, unsigned int level) const;
    template <typename T> inline T* GetFor(unsigned int cube, unsigned int face, unsigned int level);

    // Subresource indexing:  index = numLevels*item + level
    // where item = cube*6 + face
    inline unsigned int GetIndex(unsigned int cube, unsigned int face, unsigned int level) const;

private:
    unsigned int mNumCubes;
};

inline unsigned int TextureCubeArray::GetItemIndexFor(unsigned int cube, unsigned int face) const
{
    return cube * 6 + face;
}

inline unsigned int TextureCubeArray::GetCubeIndexFor(unsigned int item) const
{
    return item / 6;
}

inline unsigned int TextureCubeArray::GetFaceIndexFor(unsigned int item) const
{
    return item % 6;
}

inline unsigned int TextureCubeArray::GetOffsetFor(unsigned int cube, unsigned int face, unsigned int level) const
{
    return TextureArray::GetOffsetFor(GetItemIndexFor(cube, face), level);
}

inline char const* TextureCubeArray::GetDataFor(unsigned int cube, unsigned int face, unsigned int level) const
{
    return TextureArray::GetDataFor(GetItemIndexFor(cube, face), level);
}

inline char* TextureCubeArray::GetDataFor(unsigned int cube, unsigned int face, unsigned int level)
{
    return TextureArray::GetDataFor(GetItemIndexFor(cube, face), level);
}

template <typename T> inline T
const* TextureCubeArray::GetFor(unsigned int cube, unsigned int face, unsigned int level) const
{
    return TextureArray::GetFor<T>(GetItemIndexFor(cube, face), level);
}

template <typename T> inline
T* TextureCubeArray::GetFor(unsigned int cube, unsigned int face, unsigned int level)
{
    return TextureArray::GetFor<T>(GetItemIndexFor(cube, face), level);
}

}
