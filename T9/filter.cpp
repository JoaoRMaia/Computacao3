#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <iterator>
#include <string>
#include <map>

using namespace std;


template <typename T, typename F>
auto operator |( T& v, F func) {

    if constexpr (is_same_v<invoke_result_t<F,decltype(*std::begin(v))>, void>) {
        for (auto e : v) {
            func(e);
        }
    }
    else if constexpr (is_same_v<invoke_result_t<F, decltype(*std::begin(v))>, bool>) {
        auto f = *std::begin(v);
        vector<decltype(f)> r;
        for (auto e : v) {
            if (invoke(func, e)) {
                r.push_back(e);
            }
        }
        return r;
    }
    else {
        auto f = *std::begin(v);
        vector<invoke_result_t<F,decltype(f)>> r;
        for (auto e : v) {
            r.push_back(invoke(func,e));
        }
        return r;
    }
}


template <typename T, int n, typename F>
auto operator |( T(&v)[n], F func) {
    if constexpr (is_same_v<invoke_result_t<F, T>, bool>) {

        vector<T> r;
        for (int i = 0; i < n; i++) {
            if (func(v[i]))
                r.push_back(v[i]);
        }
        return r;
    }
    else {

        for_each(v, v + n, func);
        return v;
    }

}

#ifdef NDEBUG



int main() {

    map<string, string> v = { { "a", "1" }, { "b", "2" }, { "c", "3" }, { "d", "4" }, { "e", "5" }, { "f", "6" } };
    auto par = [](auto x) { return stoi(x.second) % 2 == 0; };
    auto upper_first = [](auto x) { string st = x.first; transform(st.begin(), st.end(), st.begin(), ::toupper); return st; };
    v | par | upper_first | [](auto st) { cout << st + "! "; };


}
#endif
