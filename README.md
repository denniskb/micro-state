# <i>&mu;</i>state
The tiniest state machine library on GitHub!

I often find myself in need of state machines because they are the cleanest and most appropriate abstractions to model certain processes. However, even "tiny" libraries have tons of features and are complete overkill for my needs. So I created GitHub's tiniest state machine library in **15 loc**.

## Usage
```c++
state_machine sm([] { printf("ping\n"); return 1; },
                 [] { printf("pong\n"); return 0; });
sm();
sm();
sm();
...
```
outputs
```
ping
pong
ping
...
```

## How it works
You create a `state_machine` and pass it a bunch of lambdas representing state transition functions. The first lambda corresponds to state 0, the second lambda to state 1, ... Each lambda returns the next state. The starting state is always 0.

## Requirements
- `#include "micro_state.h"`
- C++11 (Simply remove `constexpr` from the function signatures if it gives you trouble on an older compiler.)

## Implementation
```c++
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
```
