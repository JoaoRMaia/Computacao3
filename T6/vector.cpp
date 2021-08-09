#include <iostream>
#include <vector>

using namespace std;

template<int n, typename T>
struct Vetor {
	Vetor(initializer_list<T> v){
		int num = v.size();
		if (num--) x = *(v.begin());
		if (num--) y = *(v.begin()+1); 
		if (num--) z = *(v.begin()+2);
		
		
	}
	void operator =(initializer_list<T> v) {
		int num = v.size();
		if (num--) x = *(v.begin());
		if (num--) y = *(v.begin()+1); 
		if (num--) z = *(v.begin()+2);
		
	}
		
	T x,y,z;
	int dim = n;
	

	
	
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
	//v = 4.5, 6.1;
	return 0;
}

#endif
