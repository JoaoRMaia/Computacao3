#include <iostream>
#include <vector>

using namespace std;

template<int n, typename T>
struct Vetor {
	struct MeioOp{
		MeioOp( Vetor* v ): u(v) {}
		
		MeioOp operator , ( T a ){
			*u = n;
			return *this;
		}
		Vetor 
		
	};
	
	Vetor(){
	}
	Vetor(initializer_list<T> v){
		
		
	}
	void operator =( initializer_list<T> v ) {
		
	}
	
	MeioOp operator = ( T a ) {
		u.push_back(a);
		return MeioOp(this);
	}
		
	vector<T> u;
	

	
	
};

template<typename T>
initializer_list<T>& operator ,(T a, T b){
	return {a,b};
	
}

template<typename T>
initializer_list<T>& operator ,(initializer_list<T>& a, T b){
	return {*a.begin(),*a.end(),b};
	
}




#ifdef NDEBUG

int main () {
	
	Vetor <2,int> a;
	Vetor<2,double> v;
	v = 4.5, 6.1;
	return 0;
}

#endif
