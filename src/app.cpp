#include "./app.hpp"

namespace fs = std::filesystem;

namespace
{
  fs::path userscriptsDirectory() {
    std::error_code error;
    const auto executable = fs::read_symlink("/proc/self/exe", error);
    if (!error)
    {
      const auto adjacent = executable.parent_path() / "userscripts";
      if (fs::exists(adjacent, error) && fs::is_directory(adjacent, error))
      {
        return adjacent;
      }
    }

    return fs::current_path() / "userscripts";
  }

  bool isAllowedUrl(const saucer::url& url) {
    const auto host = url.host();
    if (url.scheme() != "https" || !host) {
      return false;
    }

    const auto& name = *host;
    return name == "ynoproject.net" ||
      (name.size() > 14 && name.ends_with(".ynoproject.net")) ||
      name == "cloudflare.com" ||
      (name.size() > 14 && name.ends_with(".cloudflare.com"));
  }
}

void installUserScriptCompatibility(saucer::smartview& webview) {
  webview.inject({
    .code = R"js(
      (() => {
        if (!window.unsafeWindow) {
          window.unsafeWindow = window;
        }

        if (!window.GM_registerMenuCommand) {
          window.GM_registerMenuCommand = () => undefined;
        }

        if (!window.GM_unregisterMenuCommand) {
          window.GM_unregisterMenuCommand = () => undefined;
        }
      })();
    )js",
    .run_at = saucer::script::time::creation,
    });
}

void loadUserScripts(saucer::smartview& webview) {
  const auto userscriptsPath = userscriptsDirectory();
  std::error_code error;
  fs::create_directories(userscriptsPath, error);

  if (error)
  {
    std::println(stderr, "Failed to create userscripts directory: {}", error.message());
    return;
  }

  std::vector<fs::path> scriptPaths;
  for (const auto& entry : fs::directory_iterator(userscriptsPath, error))
  {
    if (error)
    {
      std::println(stderr, "Failed to read userscripts directory: {}", error.message());
      return;
    }

    if (!entry.is_regular_file() || entry.path().extension() != ".js")
    {
      continue;
    }

    scriptPaths.push_back(entry.path());
  }

  if (error)
  {
    std::println(stderr, "Failed to read userscripts directory: {}", error.message());
    return;
  }

  std::ranges::sort(scriptPaths);

  for (const auto& scriptPath : scriptPaths)
  {
    std::ifstream scriptFile(scriptPath);
    const std::string code((std::istreambuf_iterator<char>(scriptFile)), {});
    if (!scriptFile)
    {
      std::println(stderr, "Failed to read userscript: {}", scriptPath.string());
      continue;
    }

    webview.inject({
        .code = code,
        .run_at = saucer::script::time::ready,
      });
  }
}

coco::stray start(saucer::application* app) {
  auto window = saucer::window::create(app).value();
  const bool hardwareAcceleration =
    std::getenv("YNO_DISABLE_HARDWARE_ACCELERATION") == nullptr;
  auto webview = saucer::smartview::create(
    {
        .window = window,
        .persistent_cookies = true,
        .hardware_acceleration = hardwareAcceleration,
    })
    .value();

  webview.expose("yno_set_fullscreen", [window](bool enabled) {
    window->set_fullscreen(enabled);
    });

  window->set_title("Yume Nikki Online Project");
  window->set_size({ .w = 1052, .h = 798 });
  window->set_background({ .r = 0, .g = 0, .b = 0, .a = 255 });
  webview.set_background({ .r = 0, .g = 0, .b = 0, .a = 255 });

  window->set_decorations(saucer::window::decoration::none);

  webview.set_context_menu(true);
  installUserScriptCompatibility(webview);
  loadUserScripts(webview);
  webview.set_url("https://ynoproject.net/");


  //  CREDIT BY https://github.com/affectioned/ynodesktop
  webview.inject({
    .code = R"js(
            (() => {
                if (document.getElementById("ynod-titlebar")) return;

                const titlebar = document.createElement("div");
                titlebar.id = "ynod-titlebar";
                titlebar.innerHTML = `
                    <div data-webview-drag id="ynod-titlebar-drag">
                        <span>Yume Nikki Online Project</span>
                    </div>
                    <div id="ynod-titlebar-buttons">
                        <button data-webview-minimize aria-label="Minimize">&minus;</button>
                        <button data-webview-maximize aria-label="Maximize">&#9633;</button>
                        <button data-webview-close aria-label="Close">&times;</button>
                    </div>`;

                const style = document.createElement("style");
                style.textContent = `
                    #ynod-titlebar {
                        align-items: center;
                        background: #000;
                        color: rgba(194, 146, 200, 1);
                        display: flex;
                        height: 30px;
                        position: fixed;
                        inset: 0 0 auto;
                        z-index: 2147483647;
                        font: 14px sans-serif;
                    }
                    #ynod-titlebar-drag {
                        align-items: center;
                        display: flex;
                        flex: 1;
                        height: 100%;
                        padding-left: 10px;
                    }
                    #ynod-titlebar-buttons { display: flex; height: 100%; }
                    #ynod-titlebar button {
                        background: transparent;
                        border: 0;
                        color: inherit;
                        cursor: pointer;
                        font: inherit;
                        height: 100%;
                        width: 42px;
                    }
                    #ynod-titlebar button:hover { background: #333; }
                    #ynod-titlebar button:last-child:hover { background: #b91c1c; }
                `;
                document.head.append(style);
                document.body.prepend(titlebar);

            })();
        )js",
        .run_at = saucer::script::time::ready,
    });

  webview.on<saucer::webview::event::navigate>(
    [&webview, app](const saucer::navigation& nav) -> saucer::policy {
      const auto url = nav.url();

      if (nav.new_window()) {
        if (!isAllowedUrl(url)) {
          return saucer::policy::block;
        }

        auto* webviewPtr = &webview;
        app->post([webviewPtr, url] { webviewPtr->set_url(url); });
        return saucer::policy::block;
      }

      /* return is_allowed_url(url) ? saucer::policy::allow
                                 : saucer::policy::block; */
      return saucer::policy::allow;
    });

  webview.on<saucer::webview::event::fullscreen>([](bool fullscreened) -> saucer::policy {
    if (fullscreened) {
      std::println("Fullscreened");
      return saucer::policy::allow;
    }
    return saucer::policy::allow;
    });

  window->show();

  co_await app->finish();
}
