// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/DX11/GteDXGIOutput.h>

namespace gte
{

// A simple wrapper for IDXGIAdapter1 objects and enumeration of them.

class GTE_IMPEXP DXGIAdapter
{
public:
    // Construction and destruction.
    ~DXGIAdapter();
    DXGIAdapter(DXGIAdapter const& object);
    DXGIAdapter(IDXGIAdapter1* adapter = nullptr);

    // Assignment.
    DXGIAdapter& operator=(DXGIAdapter const& object);

    // Member access.
    IDXGIAdapter1* GetAdapter() const;
    DXGI_ADAPTER_DESC1 const& GetDescription() const;
    std::vector<DXGIOutput> const& GetOutputs() const;

    // Enumeration of adapters on a machine.
    static void Enumerate(std::vector<DXGIAdapter>& adapters);

private:
    IDXGIAdapter1* mAdapter;
    DXGI_ADAPTER_DESC1 mDescription;
    std::vector<DXGIOutput> mOutputs;
};

}
