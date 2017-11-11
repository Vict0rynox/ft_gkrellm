//
// Created by Victor Vasiliev on 12.11.2017.
//

#ifndef FT_GKRELLM_UTILS_HPP
#define FT_GKRELLM_UTILS_HPP

#include <string>
#include <sstream>

namespace Utils
{
    template <typename T>
    std::string to_string(T val)
    {
        std::stringstream ss;
        ss << val;
        return ss.str();
    }

}

#endif //FT_GKRELLM_UTILS_HPP
