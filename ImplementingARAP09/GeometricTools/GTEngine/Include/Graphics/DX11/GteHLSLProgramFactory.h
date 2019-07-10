// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <Graphics/GteProgramFactory.h>

namespace gte
{

class GTE_IMPEXP HLSLProgramFactory : public ProgramFactory
{
public:
    // The 'defaultVersion' can be set once on application initialization if
    // you want an HLSL version different from our default when constructing a
    // program factory.
    static std::string defaultVersion;  // "5_0" (Shader Model 5)
    static std::string defaultVSEntry;  // "VSMain"
    static std::string defaultPSEntry;  // "PSMain"
    static std::string defaultGSEntry;  // "GSMain"
    static std::string defaultCSEntry;  // "CSMain"
    static unsigned int defaultFlags;
        // enable strictness, ieee strictness, optimization level 3

    // Construction.  The 'version' member is set to 'defaultVersion'.  The
    // 'defines' are empty.
    virtual ~HLSLProgramFactory();
    HLSLProgramFactory();

    // The returned value is used as a lookup index into arrays of strings
    // corresponding to shader programs.
    virtual int GetAPI() const;

    // Create a program for GPU display.
    std::shared_ptr<VisualProgram> CreateFromBytecode(
        std::vector<unsigned char> const& vsBytecode,
        std::vector<unsigned char> const& psBytecode,
        std::vector<unsigned char> const& gsBytecode);

    // Create a program for GPU computing.
    std::shared_ptr<ComputeProgram> CreateFromBytecode(
        std::vector<unsigned char> const& csBytecode);

private:
    // Create a program for GPU display.  The files are loaded, converted to
    // strings, and passed to CreateFromNamedSources.  The filenames are
    // passed as the 'xsName' parameters in case the shader compiler needs
    // this for #include path searches.
    virtual std::shared_ptr<VisualProgram> CreateFromNamedSources(
        std::string const& vsName, std::string const& vsSource,
        std::string const& psName, std::string const& psSource,
        std::string const& gsName, std::string const& gsSource);

    // Create a program for GPU computing.  The file is loaded, converted to
    // a string, and passed to CreateFromNamedSource.  The filename is passed
    // as the 'csName' parameters in case the shader compiler needs this for
    // #include path searches.
    virtual std::shared_ptr<ComputeProgram> CreateFromNamedSource(
        std::string const& csName, std::string const& csSource);
};

}
