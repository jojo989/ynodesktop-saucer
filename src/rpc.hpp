#pragma once
#include <string>
#include <discord-rpc.hpp>
#include <print>
#include <string_view>

class RPC {
public:
    RPC() = default;
    RPC(const RPC&) = delete;

    void start();
    void update(const std::string& game,const std::string& room);
    void setBasic();
    void clear();

private:
    bool m_isReady{ false };
    std::string m_lastKey{};
    std::string m_lastGame{};
    std::string m_lastRoom{};
};