#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

namespace Az{
    
    using String = std::string;
    using StringVector = std::vector<String>;

    bool StartsWith(const String& string, const String& prefix);
    bool Replace(const String& string, const String& search, const String& replace, String& out_string);
    bool ReplaceInPlace(String& string, const String& search, const String& replace);
    StringVector Split(const String& string, const String& delimiter);
    bool Trim(const String& string, String& out_string, bool left = true, bool right = true);
    bool TrimInPlace(String& string, bool left = true, bool right = true);
}