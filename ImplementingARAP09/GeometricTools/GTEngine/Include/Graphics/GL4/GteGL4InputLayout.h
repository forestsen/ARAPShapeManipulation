// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteVertexBuffer.h>
#include <Graphics/GL4/GteOpenGL.h>

namespace gte
{

class GTE_IMPEXP GL4InputLayout
{
public:
    // Construction and destruction.
    ~GL4InputLayout();
    GL4InputLayout(GLuint programHandle, GLuint vbufferHandle,
        VertexBuffer const* vbuffer);

    // Support for drawing geometric primitives.
    void Enable();
    void Disable();

private:
    GLuint mProgramHandle;
    GLuint mVBufferHandle;
    GLuint mVArrayHandle;

    struct Attribute
    {
        VASemantic semantic;
        GLint numChannels;
        GLint channelType;
        GLboolean normalize;
        GLint location;
        GLintptr offset;
        GLsizei stride;
    };

    int mNumAttributes;
    Attribute mAttributes[VA_MAX_ATTRIBUTES];

    // Conversions from GTEngine values to GL4 values.
    static GLenum const msChannelType[];
};

}
