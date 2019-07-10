// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.1 (2016/09/24)

#pragma once

#include <Graphics/GteGraphicsObject.h>
#include <vector>

namespace gte
{

class GTE_IMPEXP Resource : public GraphicsObject
{
public:
    // Abstract base class.
    virtual ~Resource();
protected:
    // The default usage is GPU_R.
    Resource(unsigned int numElements, size_t elementSize, bool createStorage = true);

public:
    // Create or destroy the system-memory storage associated with the
    // resource.  A resource does not necessarily require system memory
    // if it is intended only to provide information for GPU-resource
    // creation.
    void CreateStorage();
    void DestroyStorage();

    // Basic member access.
    inline unsigned int GetNumElements() const;
    inline unsigned int GetElementSize() const;
    inline unsigned int GetNumBytes() const;

    // The resource usage.  These control how the GPU versions are created.
    // You must set the usage type before binding the resource to an engine.
    enum GTE_IMPEXP Usage
    {
        IMMUTABLE,       // D3D11_USAGE_IMMUTABLE (default)
        DYNAMIC_UPDATE,  // D3D11_USAGE_DYNAMIC
        SHADER_OUTPUT    // D3D11_USAGE_DEFAULT
    };

    inline void SetUsage(Usage usage);
    inline Usage GetUsage() const;

    // Internal staging buffer generation.  These control creation of staging
    // buffers to support copies between CPU, staging buffers, and GPU.  You
    // must set the copy type before binding the resource to an engine.
    enum GTE_IMPEXP CopyType
    {
        COPY_NONE,           // 0 (default)
        COPY_CPU_TO_STAGING, // D3D11_CPU_ACCESS_WRITE
        COPY_STAGING_TO_CPU, // D3D11_CPU_ACCESS_READ
        COPY_BIDIRECTIONAL   // D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ
    };

    inline void SetCopyType(CopyType copyType);
    inline CopyType GetCopyType() const;

    // Member access to the raw data of the resource.  The ResetData call sets
    // mData to the storage (or to nullptr if storage does not exist.)  The
    // caller of SetData is responsible for ensuring 'data' has at least
    // mNumBytes elements.  The template member functions are a convenience for
    // accessing the raw data as a specified type.
    inline void ResetData();
    inline void SetData(char* data);
    inline char const* GetData() const;
    inline char* GetData();
    template <typename T> inline T const* Get() const;
    template <typename T> inline T* Get();

    // Specify a contiguous block of active elements in the resource.  An
    // element occupies mElementSize bytes.  Treating the data array as an
    // array of elements, mOffset is the index of the first active element;
    // that is, the first element has address mData + mOffset * mElementSize.
    // The offset must satisfy
    //   mOffset < mNumElements
    // The number of active elements is mNumActiveElements.  It must satisfy
    //   mNumActiveElements <= mNumElements - mOffset
    // If you plan on modifying both mOffset and mNumActiveElements for the
    // same object, call SetOffset() before SetNumActiveElements() because
    // of the dependency of the num-active constraint on offset.
    void SetOffset(unsigned int offset);
    inline unsigned int GetOffset() const;
    void SetNumActiveElements(unsigned int numActiveElements);
    inline unsigned int GetNumActiveElements() const;
    inline unsigned int GetNumActiveBytes() const;

protected:
    unsigned int mNumElements;
    unsigned int mElementSize;
    unsigned int mNumBytes;
    Usage mUsage;
    CopyType mCopyType;
    unsigned int mOffset;
    unsigned int mNumActiveElements;
    std::vector<char> mStorage;
    char* mData;
};


inline unsigned int Resource::GetNumElements() const
{
    return mNumElements;
}

inline unsigned int Resource::GetElementSize() const
{
    return mElementSize;
}

inline unsigned int Resource::GetNumBytes() const
{
    return mNumBytes;
}

inline void Resource::SetUsage(Usage usage)
{
    mUsage = usage;
}

inline Resource::Usage Resource::GetUsage() const
{
    return mUsage;
}

inline void Resource::SetCopyType(CopyType copyType)
{
    mCopyType = copyType;
}

inline Resource::CopyType Resource::GetCopyType() const
{
    return mCopyType;
}

inline void Resource::ResetData()
{
    mData = (mStorage.size() > 0 ? mStorage.data() : nullptr);
}

inline void Resource::SetData(char* data)
{
    mData = data;
}

inline char const* Resource::GetData() const
{
    return mData;
}

inline char* Resource::GetData()
{
    return mData;
}

template <typename T>
inline T const* Resource::Get() const
{
    return reinterpret_cast<T const*>(mData);
}

template <typename T>
inline T* Resource::Get()
{
    return reinterpret_cast<T*>(mData);
}

inline unsigned int Resource::GetOffset() const
{
    return mOffset;
}

inline unsigned int Resource::GetNumActiveElements() const
{
    return mNumActiveElements;
}

inline unsigned int Resource::GetNumActiveBytes() const
{
    return mNumActiveElements*mElementSize;
}


}
