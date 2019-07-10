// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.1 (2016/07/06)

#pragma once

#include <Graphics/GL4/GteGL4AtomicCounterBuffer.h>
#include <Graphics/GL4/GteGL4BlendState.h>
#include <Graphics/GL4/GteGL4Buffer.h>
#include <Graphics/GL4/GteGL4ConstantBuffer.h>
#include <Graphics/GL4/GteGL4DepthStencilState.h>
#include <Graphics/GL4/GteGL4DrawingState.h>
#include <Graphics/GL4/GteGL4DrawTarget.h>
#include <Graphics/GL4/GteGL4Engine.h>
#include <Graphics/GL4/GteGL4GraphicsObject.h>
#include <Graphics/GL4/GteGL4IndexBuffer.h>
#include <Graphics/GL4/GteGL4InputLayout.h>
#include <Graphics/GL4/GteGL4InputLayoutManager.h>
#include <Graphics/GL4/GteGL4RasterizerState.h>
#include <Graphics/GL4/GteGL4Resource.h>
#include <Graphics/GL4/GteGL4SamplerState.h>
#include <Graphics/GL4/GteGL4StructuredBuffer.h>
#include <Graphics/GL4/GteGL4Texture.h>
#include <Graphics/GL4/GteGL4Texture1.h>
#include <Graphics/GL4/GteGL4Texture1Array.h>
#include <Graphics/GL4/GteGL4Texture2.h>
#include <Graphics/GL4/GteGL4Texture2Array.h>
#include <Graphics/GL4/GteGL4Texture3.h>
#include <Graphics/GL4/GteGL4TextureArray.h>
#include <Graphics/GL4/GteGL4TextureCube.h>
#include <Graphics/GL4/GteGL4TextureCubeArray.h>
#include <Graphics/GL4/GteGL4TextureDS.h>
#include <Graphics/GL4/GteGL4TextureRT.h>
#include <Graphics/GL4/GteGL4TextureSingle.h>
#include <Graphics/GL4/GteGL4VertexBuffer.h>

#include <Graphics/GL4/GteGLSLComputeProgram.h>
#include <Graphics/GL4/GteGLSLProgramFactory.h>
#include <Graphics/GL4/GteGLSLReflection.h>
#include <Graphics/GL4/GteGLSLVisualProgram.h>

#include <Graphics/GL4/GteOpenGL.h>
#include <Graphics/GL4/GteOpenGLHelper.h>

#if defined(__MSWINDOWS__)
#include <Graphics/GL4/WGL/GteWGLEngine.h>
#endif

#if defined(__LINUX__)
#include <Graphics/GL4/GLX/GteGLXEngine.h>
#endif
