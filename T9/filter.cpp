#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;


template <typename T, typename F>
auto operator |(vector<T>& v, function<bool(T)> func ){
    cout << "Entrou aqui" << endl;
    vector<T> r;
    for ( auto& e : v) {
        if (func(e))
            r.push_back(e);

    }


    return r;

}

template <typename T, int n, typename F>
auto operator |(T (&v)[n], F func ){
    cout << "Entrou aqui" << endl;
    vector<T> r;
    for ( auto& e : v) {
        if (func(e))
            r.push_back(e);
    }
    return r;

}

/*
template <typename T, typename F >
auto& operator |(vector<T>& v, F func ){
    for_each(v.begin(),v.end(),func);

    return v;

}

template <typename T, typename F, int n>
auto& operator |(T (&v)[n], F func ){
    for_each(v, v+n ,func);
    return v;

}
*/


#ifdef NDEBUG


int main () {

    vector<int> v1 = { 2, 9, 8, 8, 7, 4 };
    auto result = v1 | []( int x ) { return x % 2 == 0; };
    for( auto x : result )
        cout << x << " ";
}
#endif


