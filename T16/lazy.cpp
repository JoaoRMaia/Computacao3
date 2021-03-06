#include <iostream>
#include <cmath>
#include <type_traits>
#include <string>
#include <sstream>
#include <vector>
#include <functional>

using namespace std;

vector<int> Intervalo(int ini, int fim) {
    vector<int> v;
    for (int i = ini; i < fim; i++)
        v.push_back(i);
    return  v;
}
auto Intervalo(int ini) {
    vector<int> v;
    for (int i = ini; i < 1000; i++)
        v.push_back(i);
    return  v;
}


struct Nprimeiros {
    Nprimeiros() {
        n = 3;
    }

    auto operator() (int n) {
        this->n = n;
        return *this;
    }
    
    int n;
};

Nprimeiros NPrimeiros;

template <typename T>
auto operator | (vector<T> v, Nprimeiros n) {
    vector<T> ret;
    for (int i = 0; i < n.n; i++)
        ret.push_back(v[i]);

    return  ret;

}
auto operator | (string* v, Nprimeiros n) {
    vector<string> ret;
    for (int i = 0; i < n.n; i++)
        ret.push_back(*(v+i));

    return  ret;

}

template <typename V, typename F>
auto operator | (const V& v, F func) {
    if constexpr (is_same_v< bool, invoke_result_t< F, decltype(*begin(v)) > >) {
        vector< decay_t< decltype(*begin(v)) > > res;

        for (auto x : v)
            if (invoke(func, x))
                res.push_back(x);

        return res;
    }
    else if constexpr (is_same_v< void, invoke_result_t< F, decltype(*begin(v)) > >) {
        for (auto x : v)
            func(x);
    }
    else {
        vector< decay_t< invoke_result_t< F, decltype(*begin(v)) > > > res;

        for (auto x : v)
            res.push_back(invoke(func, x));

        return res;
    }
}

#ifdef NDEBUG

int main() {

    string st[] = { "a", "e", "i", "o", "u" };
    st | NPrimeiros(3) | [](auto x) { cout << x + "!" << ";"; };

    return 0;
}

#endif
