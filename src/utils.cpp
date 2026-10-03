#include "utils.hpp"

#include <cstdlib>
#include <string>
#include <stdexcept>

#ifdef __linux__

#include <unistd.h>

#endif

#ifdef _WIN32

#include <windows.h>
#include <Shlobj.h>

#endif

namespace fs = std::filesystem;

#ifdef _WIN32

std::wstring getLocalAppData() {
    PWSTR pszPath = NULL;
    std::wstring result = L"";

    HRESULT hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &pszPath);

    if (SUCCEEDED(hr)) {
        result = pszPath;
        CoTaskMemFree(pszPath);
    }

    return result; // empty if fail
}

#endif 

fs::path getDataDir(std::string_view appName) {
#ifdef __linux__
    const char* xdgHome = std::getenv("XDG_DATA_HOME");
    fs::path dataDir = xdgHome ? fs::path(xdgHome) : fs::path(std::getenv("HOME")) / ".local" / "share";
    return dataDir / appName;
#endif

#ifdef _WIN32
    std::wstring localAppData = getLocalAppData();

    if (localAppData.empty()) {
        throw std::runtime_error("windows error: failed to get local appdata folder");
    }

    fs::path dataDir(localAppData);

    return dataDir / appName;
#endif
}

std::optional<std::string> parseGameName(std::string_view url) {
    constexpr std::string_view host = "ynoproject.net/";

    auto pos = url.find(host);
    if (pos == std::string_view::npos)
        return {};

    auto rest = url.substr(pos + host.size());
    auto end = rest.find_first_of("/?#");
    auto name = rest.substr(0, end);

    if (name.empty())
        return {};

    return std::string(name);
}

std::string urlEncode(std::string_view s) {
    static constexpr char hex[] = "0123456789ABCDEF";
    std::string out;
    for (unsigned char c : s) {
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
            out += static_cast<char>(c);
        else {
            out += '%';
            out += hex[c >> 4];
            out += hex[c & 15];
        }
    }
    return out;
}