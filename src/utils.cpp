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

std::wstring GetLocalAppData() {
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