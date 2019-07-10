// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 3.0.0 (2016/06/19)

#pragma once

#include <GTEngineDEF.h>
#include <cstdarg>
#include <string>
#include <vector>

namespace gte
{

class GTE_IMPEXP Environment
{
public:
    // Construction and destruction.
    ~Environment();
    Environment();

    // Get the string corresponding to an environment variable.
    std::string GetVariable(std::string const& name);

    // Support for paths to locate files.  For platform independence, use
    // "/" for the path separator.  The input 'directory' will automatically
    // be appended with a trailing "/" if it does not end in '/' or '\\'. 
    // The Insert*/Remove* functions return 'true' iff the operation was
    // successful.
    int GetNumDirectories() const;
    std::string Get(int i) const;
    bool Insert(std::string const& directory);
    bool Remove(std::string const& directory);
    void RemoveAll();

    // The GetPath function searches the list of directories and returns the
    // fully decorated file name if the file exists and can be opened for
    // reading.
    std::string GetPath(std::string const& name) const;

private:
    // The list of directories for GetPath to search.
    std::vector<std::string> mDirectories;
};

}
