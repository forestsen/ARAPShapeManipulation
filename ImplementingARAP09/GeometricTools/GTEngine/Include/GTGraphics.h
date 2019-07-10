// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.6 (2019/02/06)

#pragma once

// Abstract bases class for DX11 and OpenGL.
#include <Graphics/GteGEDrawTarget.h>
#include <Graphics/GteGEInputLayoutManager.h>
#include <Graphics/GteGEObject.h>
#include <Graphics/GteGraphicsEngine.h>

// Effects
#include <Graphics/GteAmbientLightEffect.h>
#include <Graphics/GteConstantColorEffect.h>
#include <Graphics/GteDirectionalLightEffect.h>
#include <Graphics/GteDirectionalLightTextureEffect.h>
#include <Graphics/GteFont.h>
#include <Graphics/GteFontArialW400H18.h>
#include <Graphics/GteLightCameraGeometry.h>
#include <Graphics/GteLighting.h>
#include <Graphics/GteLightingEffect.h>
#include <Graphics/GteMaterial.h>
#include <Graphics/GteOverlayEffect.h>
#include <Graphics/GtePlanarReflectionEffect.h>
#include <Graphics/GtePointLightEffect.h>
#include <Graphics/GtePointLightTextureEffect.h>
#include <Graphics/GteSpotLightEffect.h>
#include <Graphics/GteTextEffect.h>
#include <Graphics/GteTexture2Effect.h>
#include <Graphics/GteTexture3Effect.h>
#include <Graphics/GteVertexColorEffect.h>
#include <Graphics/GteVisualEffect.h>

// Resources
#include <Graphics/GteDataFormat.h>
#include <Graphics/GteGraphicsObject.h>
#include <Graphics/GteResource.h>

// Resources/Buffers
#include <Graphics/GteBuffer.h>
#include <Graphics/GteConstantBuffer.h>
#include <Graphics/GteIndexBuffer.h>
#include <Graphics/GteIndexFormat.h>
#include <Graphics/GteIndirectArgumentsBuffer.h>
#include <Graphics/GteMemberLayout.h>
#include <Graphics/GteRawBuffer.h>
#include <Graphics/GteStructuredBuffer.h>
#include <Graphics/GteTypedBuffer.h>
#include <Graphics/GteVertexBuffer.h>
#include <Graphics/GteVertexFormat.h>

// Resources/Textures
#include <Graphics/GteDrawTarget.h>
#include <Graphics/GteTexture.h>
#include <Graphics/GteTexture1.h>
#include <Graphics/GteTexture1Array.h>
#include <Graphics/GteTexture2.h>
#include <Graphics/GteTexture2Array.h>
#include <Graphics/GteTexture3.h>
#include <Graphics/GteTextureArray.h>
#include <Graphics/GteTextureBuffer.h>
#include <Graphics/GteTextureCube.h>
#include <Graphics/GteTextureCubeArray.h>
#include <Graphics/GteTextureDS.h>
#include <Graphics/GteTextureRT.h>
#include <Graphics/GteTextureSingle.h>

// SceneGraph
#include <Graphics/GteMeshFactory.h>

// SceneGraph/Controllers
#include <Graphics/GteBlendTransformController.h>
#include <Graphics/GteControlledObject.h>
#include <Graphics/GteController.h>
#include <Graphics/GteIKController.h>
#include <Graphics/GteKeyframeController.h>
#include <Graphics/GteMorphController.h>
#include <Graphics/GteParticleController.h>
#include <Graphics/GtePointController.h>
#include <Graphics/GteSkinController.h>
#include <Graphics/GteTransformController.h>

// SceneGraph/Detail
#include <Graphics/GteBillboardNode.h>

// SceneGraph/Hierarchy
#include <Graphics/GteBoundingSphere.h>
#include <Graphics/GteCamera.h>
#include <Graphics/GteCameraRig.h>
#include <Graphics/GteLight.h>
#include <Graphics/GteNode.h>
#include <Graphics/GteParticles.h>
#include <Graphics/GtePVWUpdater.h>
#include <Graphics/GteSpatial.h>
#include <Graphics/GteTrackball.h>
#include <Graphics/GteTrackcylinder.h>
#include <Graphics/GteTransform.h>
#include <Graphics/GteViewVolume.h>
#include <Graphics/GteViewVolumeNode.h>
#include <Graphics/GteVisual.h>

// SceneGraph/Picking
#include <Graphics/GtePicker.h>
#include <Graphics/GtePickRecord.h>

// SceneGraph/Sorting
#include <Graphics/GteBspNode.h>

// SceneGraph/Terrain
#include <Graphics/GteTerrain.h>

// SceneGraph/Visibility
#include <Graphics/GteCuller.h>
#include <Graphics/GteCullingPlane.h>

// Shaders
#include <Graphics/GteComputeProgram.h>
#include <Graphics/GteComputeShader.h>
#include <Graphics/GteGeometryShader.h>
#include <Graphics/GtePixelShader.h>
#include <Graphics/GteProgramDefines.h>
#include <Graphics/GteProgramFactory.h>
#include <Graphics/GteShader.h>
#include <Graphics/GteVertexShader.h>
#include <Graphics/GteVisualProgram.h>

// State
#include <Graphics/GteBlendState.h>
#include <Graphics/GteDepthStencilState.h>
#include <Graphics/GteDrawingState.h>
#include <Graphics/GteRasterizerState.h>
#include <Graphics/GteSamplerState.h>
