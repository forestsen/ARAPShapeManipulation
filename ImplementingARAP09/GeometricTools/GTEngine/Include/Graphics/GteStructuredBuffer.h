// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteBuffer.h>

namespace gte
{

class GTE_IMPEXP StructuredBuffer : public Buffer
{
public:
    // Construction.
    StructuredBuffer(unsigned int numElements, size_t elementSize,
        bool createStorage = true);

    enum GTE_IMPEXP CounterType
    {
        CT_NONE,  // default, 
        CT_APPEND_CONSUME,
        CT_COUNTER
    };

    CounterType GetCounterType() const;

    // Call one of these functions before binding the buffer to the engine.
    // These will set the CounterType and set the usage to SHADER_OUTPUT.
    void MakeAppendConsume();
    void MakeCounter();

    // Let the GPU know whether or not to change its internal count when
    // the buffer has a counter (CT_APPEND_CONSUME or CT_COUNTER).  An input
    // of 'true' means the GPU will let the counter keep its current value.
    // This function is ignored when the buffer has counter type CT_NONE.
    void SetKeepInternalCount(bool keepInternalCount);
    bool GetKeepInternalCount() const;

    // To access the active number of elements maintained by the GPU for the
    // CT_APPEND_CONSUME or CT_COUNTER buffers, you must call
    //   DX11Engine* engine = <your engine>;
    //   StructuredBuffer* buffer = <your buffer>;
    //   engine->GetNumActiveElements(buffer);  // copy count from GPU to CPU
    //   int numElements = buffer->GetNumActiveElements();
    // Also
    //   engine->CopyGpuToCpu(buffer);
    // will fetch the buffer contents as well as the active number.

protected:
    CounterType mCounterType;
    bool mKeepInternalCount;

public:
    // For use by the Shader class for storing reflection information.
    static int const shaderDataLookup = 2;
};

}
