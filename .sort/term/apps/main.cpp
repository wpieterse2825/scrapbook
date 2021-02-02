#include <string>
#include <thread>
#include <chrono>
#include <memory>

#include "term/rxterm/terminal.hpp"
#include "term/rxterm/style.hpp"
#include "term/rxterm/image.hpp"
#include "term/rxterm/reflow.hpp"
#include "term/rxterm/components/text.hpp"
#include "term/rxterm/components/stacklayout.hpp"
#include "term/rxterm/components/flowlayout.hpp"
#include "term/rxterm/components/progress.hpp"
#include "term/rxterm/components/maxwidth.hpp"

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
