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

auto RenderToTerminal = [](auto const& terminal, unsigned const width, Component const& component) {
    // TODO(wpieterse): get actual terminal width
    return terminal.flip(component.render(width).toString());
};

int main() {
    using namespace std::chrono_literals;
    using namespace std::string_literals;

    VirtualTerminal terminal;

    auto super_progress_bar = [](auto x, auto y, auto z) -> StackLayout<> {
        if (x > 0.75) {
            return {StackLayout<> {
              FlowLayout<> {
                Text(Style {FontColor::Green}, "INFO: "),
                Text(Style {FontColor::White}, "Finalizing                                                         "),
              },
            }};
        }

        if (x > 0.5) {
            return {StackLayout<> {
              FlowLayout<> {
                Text(Style {FontColor::Green}, "INFO: "),
                Text(Style {FontColor::White}, "Building 1                                                         "),
              },
              FlowLayout<> {
                Text(Style {FontColor::Green}, "INFO: "),
                Text(Style {FontColor::White}, "Building 2                                                         "),
              },
              FlowLayout<> {
                Text(Style {FontColor::Green}, "INFO: "),
                Text(Style {FontColor::White}, "Building 3                                                         "),
              },
            }};
        }

        return {StackLayout<> {
          FlowLayout<> {
            Text(Style {FontColor::Green}, "INFO: "),
            Text(Style {FontColor::White}, "Analyzing build graph...                                                         "),
          },
        }};
    };

    for (auto index = 0; index < 101; ++index) {
        terminal = RenderToTerminal(terminal, 120, super_progress_bar(0.01 * index, 0.02 * index, 0.03 * index));

        std::this_thread::sleep_for(75ms);
    }

    return 0;
}
