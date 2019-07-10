// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.1 (2017/06/23)

#pragma once

#include <GTEngineDEF.h>
#include <string>

namespace gte
{

// Data format types; these map directly to DX11 DXGI_FORMAT.
enum GTE_IMPEXP DFType
{
    // DX11.0 formats listed below
    DF_UNKNOWN,
    DF_R32G32B32A32_TYPELESS,
    DF_R32G32B32A32_FLOAT,
    DF_R32G32B32A32_UINT,
    DF_R32G32B32A32_SINT,
    DF_R32G32B32_TYPELESS,
    DF_R32G32B32_FLOAT,
    DF_R32G32B32_UINT,
    DF_R32G32B32_SINT,
    DF_R16G16B16A16_TYPELESS,
    DF_R16G16B16A16_FLOAT,
    DF_R16G16B16A16_UNORM,
    DF_R16G16B16A16_UINT,
    DF_R16G16B16A16_SNORM,
    DF_R16G16B16A16_SINT,
    DF_R32G32_TYPELESS,
    DF_R32G32_FLOAT,
    DF_R32G32_UINT,
    DF_R32G32_SINT,
    DF_R32G8X24_TYPELESS,
    DF_D32_FLOAT_S8X24_UINT,
    DF_R32_FLOAT_X8X24_TYPELESS,
    DF_X32_TYPELESS_G8X24_UINT,
    DF_R10G10B10A2_TYPELESS,
    DF_R10G10B10A2_UNORM,
    DF_R10G10B10A2_UINT,
    DF_R11G11B10_FLOAT,
    DF_R8G8B8A8_TYPELESS,
    DF_R8G8B8A8_UNORM,
    DF_R8G8B8A8_UNORM_SRGB,
    DF_R8G8B8A8_UINT,
    DF_R8G8B8A8_SNORM,
    DF_R8G8B8A8_SINT,
    DF_R16G16_TYPELESS,
    DF_R16G16_FLOAT,
    DF_R16G16_UNORM,
    DF_R16G16_UINT,
    DF_R16G16_SNORM,
    DF_R16G16_SINT,
    DF_R32_TYPELESS,
    DF_D32_FLOAT,
    DF_R32_FLOAT,
    DF_R32_UINT,
    DF_R32_SINT,
    DF_R24G8_TYPELESS,
    DF_D24_UNORM_S8_UINT,
    DF_R24_UNORM_X8_TYPELESS,
    DF_X24_TYPELESS_G8_UINT,
    DF_R8G8_TYPELESS,
    DF_R8G8_UNORM,
    DF_R8G8_UINT,
    DF_R8G8_SNORM,
    DF_R8G8_SINT,
    DF_R16_TYPELESS,
    DF_R16_FLOAT,
    DF_D16_UNORM,
    DF_R16_UNORM,
    DF_R16_UINT,
    DF_R16_SNORM,
    DF_R16_SINT,
    DF_R8_TYPELESS,
    DF_R8_UNORM,
    DF_R8_UINT,
    DF_R8_SNORM,
    DF_R8_SINT,
    DF_A8_UNORM,
    DF_R1_UNORM,
    DF_R9G9B9E5_SHAREDEXP,
    DF_R8G8_B8G8_UNORM,
    DF_G8R8_G8B8_UNORM,
    DF_BC1_TYPELESS,
    DF_BC1_UNORM,
    DF_BC1_UNORM_SRGB,
    DF_BC2_TYPELESS,
    DF_BC2_UNORM,
    DF_BC2_UNORM_SRGB,
    DF_BC3_TYPELESS,
    DF_BC3_UNORM,
    DF_BC3_UNORM_SRGB,
    DF_BC4_TYPELESS,
    DF_BC4_UNORM,
    DF_BC4_SNORM,
    DF_BC5_TYPELESS,
    DF_BC5_UNORM,
    DF_BC5_SNORM,
    DF_B5G6R5_UNORM,
    DF_B5G5R5A1_UNORM,
    DF_B8G8R8A8_UNORM,
    DF_B8G8R8X8_UNORM,
    DF_R10G10B10_XR_BIAS_A2_UNORM,
    DF_B8G8R8A8_TYPELESS,
    DF_B8G8R8A8_UNORM_SRGB,
    DF_B8G8R8X8_TYPELESS,
    DF_B8G8R8X8_UNORM_SRGB,
    DF_BC6H_TYPELESS,
    DF_BC6H_UF16,
    DF_BC6H_SF16,
    DF_BC7_TYPELESS,
    DF_BC7_UNORM,
    DF_BC7_UNORM_SRGB,
    // DX11.1 formats listed below
    DF_AYUV,
    DF_Y410,
    DF_Y416,
    DF_NV12,
    DF_P010,
    DF_P016,
    DF_420_OPAQUE,
    DF_YUY2,
    DF_Y210,
    DF_Y216,
    DF_NV11,
    DF_AI44,
    DF_IA44,
    DF_P8,
    DF_A8P8,
    DF_B4G4R4A4_UNORM,
    DF_NUM_FORMATS
};

// Enumerations for GL4.
enum GTE_IMPEXP DFChannelType
{
    DF_UNSUPPORTED,
    DF_BYTE,
    DF_UBYTE,
    DF_SHORT,
    DF_USHORT,
    DF_INT,
    DF_UINT,
    DF_HALF_FLOAT,
    DF_FLOAT,
    DF_DOUBLE,
    DF_INT_10_10_2,
    DF_UINT_10_10_2,
    DF_FLOAT_11_11_10,
    DF_UINT_24_8,
    DF_NUM_CHANNEL_TYPES
};

class GTE_IMPEXP DataFormat
{
public:
    // All data formats are known at compile time.  This class provides
    // queries for format information given the type.

    // A string version of the DF_* enumeration.
    inline static std::string const& GetName(DFType type);

    // The number of bytes per struct.
    inline static unsigned int GetNumBytesPerStruct(DFType type);

    // The number of channels per struct.
    inline static unsigned int GetNumChannels(DFType type);

    // The type of the channel.
    inline static DFChannelType GetChannelType(DFType type);

    // The conversion semantics for the channel.  When true, signed integers
    // are converted to floats in [-1,1] and unsigned integers are converted
    // to floats in [0,1].  When false, integer data is converted directly to
    // floats.
    inline static bool ConvertChannel(DFType type);

    // Not all DX11 formats are currently supported.
    inline static bool IsSupported(DFType type);

    // The struct has a depth format.
    static bool IsDepth(DFType type);

private:
    // Texel information.
    static std::string const msName[DF_NUM_FORMATS];
    static unsigned int const msNumBytesPerStruct[DF_NUM_FORMATS];
    static unsigned int const msNumChannels[DF_NUM_FORMATS];
    static DFChannelType const msChannelType[DF_NUM_FORMATS];
    static bool const msConvertChannel[DF_NUM_FORMATS];
    static bool const msSupported[DF_NUM_FORMATS];
};


inline std::string const& DataFormat::GetName(DFType type)
{
    return msName[type];
}

inline unsigned int DataFormat::GetNumBytesPerStruct(DFType type)
{
    return msNumBytesPerStruct[type];
}

inline unsigned int DataFormat::GetNumChannels(DFType type)
{
    return msNumChannels[type];
}

inline DFChannelType DataFormat::GetChannelType(DFType type)
{
    return msChannelType[type];
}

inline bool DataFormat::ConvertChannel(DFType type)
{
    return msConvertChannel[type];
}

inline bool DataFormat::IsSupported(DFType type)
{
    return msSupported[type];
}

inline bool DataFormat::IsDepth(DFType type)
{
    return type == DF_D32_FLOAT_S8X24_UINT
        || type == DF_D32_FLOAT
        || type == DF_D24_UNORM_S8_UINT
        || type == DF_D16_UNORM;
}


}
