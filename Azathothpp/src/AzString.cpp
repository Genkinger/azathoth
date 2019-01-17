#include "string/AzString.hpp"

namespace Az{

    bool StartsWith(const String& string, const String& prefix){
        return string.rfind(prefix,0) == 0;
    }

    bool Replace(const String& string, const String& search, const String& replace, String& out_string){
        out_string = string;
        auto pos = out_string.find(search);
        if(pos != String::npos){
            out_string.replace(pos,replace.length(),replace);
            return true;
        }
        return false;
    }
    
    bool ReplaceInPlace(String& string, const String& search, const String& replace){
        Replace(string,search,replace,string);
    }
    
    StringVector Split(const String& string, const String& delimiter){
        String str = string;
        StringVector result;
        size_t pos = 0;
        String token;
        while ((pos = str.find(delimiter)) != String::npos) {
            token = str.substr(0, pos);
            result.emplace_back(token);
            str.erase(0, pos + delimiter.length());
        }
        result.emplace_back(str);
        return result;
    }

    bool Trim(const String& string, String& out_string, bool left, bool right){
        
        static auto ltrim = [](String s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;};

        static auto rtrim = [](String s) {
            s.erase(std::find_if(s.rbegin(), s.rend(),
                std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
            return s;};

        if(left && right)
        {
            out_string = ltrim(rtrim(string));
            return true;
        }
        if(left)
        {
            out_string = ltrim(string);
            return true;
        }
        else if(right)
        {
            out_string = rtrim(string);
            return true;
        }
        return false;
    }

    bool TrimInPlace(String& string, bool left, bool right){
        return Trim(string,string,left,right);
    }

}