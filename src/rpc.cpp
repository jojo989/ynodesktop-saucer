#include <discord-rpc.hpp>
#include <print>
#include <string_view>

#include "./rpc.hpp"
#include <discord-rpc.hpp>
#include "./utils.hpp"

#define APP_ID "1554975882517413968"

RPC::RPC() {
    discord::RPCManager::get()
        .setClientID(APP_ID)
        .onReady([](discord::User user) {
        std::println("discord rpc connected to user: {} ; {} #{}", user.username, user.discriminator, user.id);

            })
        .onDisconnected([](int errorCode, std::string_view message) {
        std::println("disconnected with error code {} ; msg: {}", errorCode, message);
            })
        .initialize();

    m_isReady = true;
};

RPC::~RPC(){
    discord::RPCManager::get().clearPresence();
    discord::RPCManager::get().shutdown();
}

void RPC::update(const std::string& game, const std::string& room) {
    if (!m_isReady) return;

    State next{ std::string(game), std::string(room) };
    if (m_last == next) return;
    m_last = std::move(next);

    const std::string state = m_last->room.empty()
        ? std::string("Going to bed…")
        : m_last->room;

    discord::RPCManager::get()
        .getPresence()
        .setLargeImageKey(m_last->game)
        .setLargeImageText(m_last->game)
        .setSmallImageKey("yno-logo")
        .setSmallImageText("YNOProject")
        .setDetails(std::format("Dreaming on {}…", m_last->game))
        .setState(state)
        .refresh();
}

void RPC::setBasic() {
    if (!m_isReady) return;

    State next{};
    if (m_last == next) return;
    m_last = std::move(next);

    discord::RPCManager::get()
        .getPresence()
        .setLargeImageKey("yno-logo")
        .setLargeImageText("Yume Nikki Online Project")
        .setState("Choosing a door...")
        .refresh();
}