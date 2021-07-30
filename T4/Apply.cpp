#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <map>
#include <type_traits>

//#include "apply.cc"

using namespace std;

double seno( double n ) { return sin(n); }
int id( int n ) { return n; }
string roman( int n ) {
    map<int,string> rom = { { 1, "I" }, { 2, "II" }, { 3, "III" }, { 4, "IV" }, { 5, "V" }, { 6, "VI" }, { 7, "VII" }, { 8, "VIII" } } ; 

    return rom[n]; 
}

struct FunctorSimples { 
    string operator()( int n ) { return roman( n ) + "!"; }
};

struct FunctorTemplate { 
    template <typename T>
    T operator()( T n ) { return n+n; }
};

template <typename T>
ostream& operator << ( ostream& o, const vector<T>& v ) {
    o << "[ ";
    for( auto x : v )
        o << x << " ";
        
    return o << "]";
}

using namespace std;

template <typename T, typename F>
auto apply( T array, F func) -> vector<decltype(func(array[0]))>{
	vector<decltype(func(array[0]))> r;
	for (auto e : array){
		r.push_back(func(e));
	}
	
	return r;
}

template <typename T, typename F>
vector<invoke_result_t<F,T>> apply( initializer_list<T> array, F func) {
	vector<invoke_result_t<F,T>> r;
	for (auto e : array){
		r.push_back(func(e));
	}
	
	return r;
}

template <typename T, typename F>
vector<invoke_result_t<F,T>> apply( int* array, F func) {
	vector<int> a{array};
	vector<invoke_result_t<F,T>> r;
	for (auto e : a){
		r.push_back(func(e));
	}
	
	return r;
}

int main( int argc, char* argv[]) {
	     
	int v[] = { 1, 2, 3, 4, 5 };
	vector<int> r = ::apply( v, id );
	cout << r;
}
