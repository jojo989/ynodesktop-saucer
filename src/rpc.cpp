#include "./rpc.hpp"
#include <discord-rpc.hpp>
#include "./utils.hpp"

#define APP_ID "1554975882517413968"

void RPC::start() {
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

void RPC::update(const std::string& game, const std::string& room) {
    if (!m_isReady) return;

    const std::string state = room.empty() ? "Going to bed…" : room;

    std::string largeImage = game.empty() ? "yno-logo" : game;

    std::println("game: {}, largeimage: {}", game, largeImage);

    const std::string key = game + '\n' + state;
    if (key == m_lastKey) return;
    m_lastKey = key;

    discord::RPCManager::get()
        .getPresence()
        .setState("Yume Nikki Online")
        .setLargeImageKey(largeImage)
        .setLargeImageText(game)
        .setSmallImageKey("yno-logo")
        .setSmallImageText("YNOProject")
        .setDetails(std::format("Dreaming on {}…", game))
        .setState(state)
        .refresh();
}

void RPC::setBasic() {
    if (!m_isReady) return;
    m_lastGame.clear();

    const std::string key = "\nbasic";
    if (key == m_lastKey) return;
    m_lastKey = key;

    discord::RPCManager::get()
        .getPresence()
        .setLargeImageKey("yno-logo")
        .setLargeImageText("Yume Nikki Online Project")
        .setState("Choosing a door...")
        .refresh();
}

void RPC::clear() {
    discord::RPCManager::get().clearPresence();
};