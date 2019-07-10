// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <GTEngineDEF.h>
#include <string>
#include <vector>

// Construct definitions used by shader compilers.

namespace gte
{

class GTE_IMPEXP ProgramDefines
{
public:
    // Construction.
    ProgramDefines();

    // Set a definition.  Each is stored as a std::pair of std::string.  The
    // firstelement of the pair is the 'name' and the second element of the
    // pair is the string representation of 'value'.
    inline void Set(std::string const& name, int value);
    inline void Set(std::string const& name, unsigned int value);
    inline void Set(std::string const& name, float value);
    inline void Set(std::string const& name, double value);
    inline void Set(std::string const& name, std::string const& value);
    inline std::vector<std::pair<std::string,std::string>> const& Get() const;

    // Remove definitions, which allows the ProgramDefines object to be
    // shared in a scope.
    void Remove(std::string const& name);
    void Clear();

private:
    void Update(std::string const& name, std::string const& value);

    std::vector<std::pair<std::string, std::string>> mDefinitions;
};


inline void ProgramDefines::Set(std::string const& name, int value)
{
    Update(name, std::to_string(value));
}

inline void ProgramDefines::Set(std::string const& name, unsigned int value)
{
    Update(name, std::to_string(value));
}

inline void ProgramDefines::Set(std::string const& name, float value)
{
    Update(name, std::to_string(value));
}

inline void ProgramDefines::Set(std::string const& name, double value)
{
    Update(name, std::to_string(value));
}

inline void ProgramDefines::Set(std::string const& name,
    std::string const& value)
{
    Update(name, value);
}

inline std::vector<std::pair<std::string, std::string>> const&
ProgramDefines::Get() const
{
    return mDefinitions;
}


}
