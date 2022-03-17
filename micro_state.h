#pragma once

#include <array>
#include <functional>

namespace micro_state {
    template <class... Fs>
    class state_machine {
    public:
        constexpr explicit state_machine(Fs&&... fs) {
            std::function<int()> _states[] = {std::move(fs)...};
            for (int i = 0; i < states.size(); i++)
                states[i] = std::move(_states[i]);
        }

        constexpr void operator()() { state = states[state](); }

    private:
        int state = 0;
        std::array<std::function<int()>, sizeof...(Fs)> states;
    };
}