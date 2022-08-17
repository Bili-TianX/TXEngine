#include <windows.h>
#include <TXEngine/Util/String.hpp>

namespace tx
{

std::string wstring_to_string(const std::wstring& s)
{
    std::string result{};
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    auto len = WideCharToMultiByte(CP_UTF8, 0, s.data(), s.size(), nullptr, 0, nullptr, nullptr);
    
    result.resize(len);

    WideCharToMultiByte(CP_UTF8, 0, s.data(), s.size(), result.data(), result.size(), nullptr, nullptr);
    return result;
}

}