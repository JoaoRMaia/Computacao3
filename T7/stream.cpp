#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

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



#ifdef NDEBUG


int main () {

    int tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 };
    vector<int> v{ 2 , 6, 8 };
    for_each( tab, tab+10,  []( int x ) { cout << x*x << endl; } );
    v | []( int x ) { cout << x*x << endl; };
    return 0;
}
#endif


