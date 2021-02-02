#include <string>
#include <thread>
#include <chrono>
#include <memory>

#include "third_party/rxterm/terminal.hpp"
#include "third_party/rxterm/style.hpp"
#include "third_party/rxterm/image.hpp"
#include "third_party/rxterm/reflow.hpp"
#include "third_party/rxterm/components/text.hpp"
#include "third_party/rxterm/components/stacklayout.hpp"
#include "third_party/rxterm/components/flowlayout.hpp"
#include "third_party/rxterm/components/progress.hpp"
#include "third_party/rxterm/components/maxwidth.hpp"

using namespace rxterm;

auto renderToTerm = [](auto const& vt, unsigned const w, Component const& c) {
    // TODO: get actual terminal width
    return vt.flip(c.render(w).toString());
};

int main() {
    using namespace std::chrono_literals;
    using namespace std::string_literals;

    VirtualTerminal vt;

    auto superProgressBar = [](auto x, auto y, auto z) -> StackLayout<> {
        if (x > 0.75) {
            return {StackLayout<> {
              FlowLayout<> {
                Text(Style{FontColor::Green}, "INFO: "),
                Text(Style{FontColor::White}, "Finalizing                                                         "),
              },
            }};
        }

        if (x > 0.5) {
            return {StackLayout<> {
              FlowLayout<> {
                Text(Style{FontColor::Green}, "INFO: "),
                Text(Style{FontColor::White}, "Building 1                                                         "),
              },
              FlowLayout<> {
                Text(Style{FontColor::Green}, "INFO: "),
                Text(Style{FontColor::White}, "Building 2                                                         "),
              },
              FlowLayout<> {
                Text(Style{FontColor::Green}, "INFO: "),
                Text(Style{FontColor::White}, "Building 3                                                         "),
              },
            }};
        }

        return {StackLayout<> {
          FlowLayout<> {
                Text(Style{FontColor::Green}, "INFO: "),
                Text(Style{FontColor::White}, "Analyzing build graph...                                                         "),
              },
        }};
    };

    for (int i = 0; i < 101; ++i) {
        vt = renderToTerm(vt, 120, superProgressBar(0.01 * i, 0.02 * i, 0.03 * i));
        std::this_thread::sleep_for(75ms);
    }

    return 0;
}
