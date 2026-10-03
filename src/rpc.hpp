#pragma once
#include <string>


class RPC {
public:
    RPC();
    ~RPC();
    RPC(const RPC&) = delete;
    RPC& operator=(const RPC&) = delete;

    void update(const std::string& game,const std::string& room);
    void setBasic();
    void clear();

private:
    struct State {
        std::string game, room;
        bool operator==(const State&) const = default;
    };
    std::optional<State> m_last;
    std::atomic<bool>    m_isReady{false};
};