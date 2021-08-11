#include <iostream>
#include <vector>

using namespace std;

template<int n, typename T>
struct Vetor {
	Vetor(){}

	struct MeioOP{
	    MeioOP(vector<T> u) : v(u) {}

	    vector<T> v;
	};


	Vetor& operator =(T e) {
	    u.push_back(e);
	    return *this;
	}

	Vetor& operator ,(T e) {
	    u.push_back(e);
	    return *this;
	}
	Vetor operator +(Vetor v) {
	    Vetor<n,T> r;
	    for (int i = 0 ; i < n ; i++){
            r[i] = this[i] + v[i];
	    }

	    return r;
	}
	Vetor operator *(T v) {
	    Vetor<n,T> r;
	    for (int i = 0 ; i < n ; i++){
            r[i] = this[i] + v[i];
	    }

	    return r;
	}

	T operator *(Vetor<n,T> v){
	    T sum = 0;
	    for (int i = 0 ; i < n ; i++){
            sum += u.at(i)*v.u.at(i);
	    }
	    return sum;

	}



	MeioOP operator* (){
	    return MeioOP(u);
	}
	Vetor<n,T> operator *(MeioOP v){
	    return *this;
	}


	vector<T> u;
};

template <int n, typename T>
ostream& operator << (ostream& o, Vetor<n,T> v) {
    return o;
}



#ifdef NDEBUG

int main () {

	Vetor <2,double> a;
	Vetor<2,double> v;
	v = 4.5, 6.1;
	a = 5.5, 10.0;
	cout << a*v;
	return 0;
}

#endif
