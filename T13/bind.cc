#include <iostream>
#include <algorithm>
#include <array>

using namespace std;


template <typename F>
auto bind(F f) {
    return f;
}

template <typename F, typename ...Arg>
auto bind(F f, Arg... args) {
    auto func = [f, args...](auto arg) { return f(args..., arg); };
    return func;
}

#ifdef NDEBUG


long mdc(long a, long b) { return b == 0 ? a : mdc(b, a % b); }

struct MMC {
    auto operator()(long a, long b) { return a * b / mdc(a, b); }
};

struct BarraPesada {
    template <typename A, typename B>
    auto operator()(A a, B b) {
        return a + b;
    }
};

string ordena(string a, string b, string c, string d, string e, string f, string g, string h, string i, string j, string k, string l) {
    std::array<string, 12> tab = { a, b, c, d, e, f, g, h, i, j, k, l };
    string result;

    std::sort(tab.begin(), tab.end());
    for (auto itr = tab.begin(); itr != tab.end(); ++itr)
        result += *itr + " ";

    return result;
}

int main() {

    //using ::bind;

    auto f2 = bind(mdc);
    auto f1 = f2(18);
    for (int i = 2; i <= 18; i++)
        cout << f1(i) << " ";


    return 0;
}

#endif
