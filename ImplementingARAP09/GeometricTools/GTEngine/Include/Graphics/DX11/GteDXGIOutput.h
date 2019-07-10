// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/DX11/GteDX11Include.h>
#include <vector>

namespace gte
{

// A simple wrapper for IDXGIOutput objects and enumeration of them.

class GTE_IMPEXP DXGIOutput
{
public:
    // Construction and destruction.
    ~DXGIOutput();
    DXGIOutput(DXGIOutput const& object);
    DXGIOutput(IDXGIOutput* output = nullptr);

    // Assignment.
    DXGIOutput& operator=(DXGIOutput const& object);

    // Member access.
    IDXGIOutput* GetOutput() const;
    DXGI_OUTPUT_DESC const& GetDescription() const;

    // Queries for information about the output/monitor.  The modes that
    // support the format are returned, possibly an empty list.  The returned
    // HRESULT is one of the DXGI_ERROR values.
    HRESULT GetDisplayModes(DXGI_FORMAT format,
        std::vector<DXGI_MODE_DESC>& modeDescriptions);

    // Find a mode that matches as closely as possible the requested mode.
    // The returned HRESULT is one of the DXGI_ERROR values.
    HRESULT FindClosestMatchingMode(DXGI_MODE_DESC const& requested,
        DXGI_MODE_DESC& closest);

private:
    IDXGIOutput* mOutput;
    DXGI_OUTPUT_DESC mDescription;
};

}
