#include <iostream>
#include <vector>

using namespace std;

template<int n, typename T>
struct Vetor {
	Vetor(T x, T y, T z) {
	    u.push_back(x);
	    u.push_back(y);
	    u.push_back(z);
	}
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
	Vetor<n,T> operator +(Vetor<n,T> e) {
	    Vetor<n,T> v;
	    for (int i = 0 ; i < n ; i++){
             v.u.push_back(u[i] +  e.u[i]);
	    }

	    return v;
	}
	Vetor<n,T> operator *(T e) {
	    Vetor<n,T> v;
	    for (int i = 0 ; i < n ; i++){
             v.u.push_back(u[i] * e );
	    }

	    return v;
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
	Vetor<3,T> operator *(MeioOP v){
	    return Vetor<3,T>(this->u[1]*v.v[2] - this->u[2]*v.v[1], this->u[2]*v.v[0] - this->u[0]*v.v[2], this->u[0]*v.v[1] - this->u[1]*v.v[0]);
	}


	vector<T> u;
};

template<int n, typename T>
Vetor<n,T> operator * (double a, Vetor<n,T> v){
    return v*a;
    }

template <int n, typename T>
ostream& operator << (ostream& o, Vetor<n,T> v) {
    for (int i = 0; i < n ; i++)
        o << v.u[i] << " ";
    return o;
}



#ifdef NDEBUG

using namespace std;
int main( int argc, char* argv[]) {
  Vetor< 3, double> a(1,2,3), b(4,5,6);
  double x, y, z;
  cout << a << endl;
  cout << a + b << endl;



  return 0;
}

#endif
