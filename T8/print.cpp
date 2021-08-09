#include <initializer_list>
#include <iostream>
#include <memory>

using namespace std;

struct AbstractPair {	
	virtual void print( ostream& o ){}
};

template <typename A, typename B>
struct ImplPair : AbstractPair {
	ImplPair(A a, B b) : a(a), b(b) {}
	
	void print( ostream& o ) {
		o << a << " = " << b << endl;
	}
	
private:
	A a;
	B b;
	
};

struct Pair {
  template <typename A, typename B>
  Pair( A a, B b ) {
	  p = shared_ptr<ImplPair<A,B>>(a,b);
	  
  }
  
  shared_ptr<AbstractPair> p;
};


void print( ostream& o, initializer_list<Pair> lista ) {
	for (auto e : lista){
		e.p->print(o);
	}
}

#ifdef NDEBUG

int main (){
	
	return 0;
}

#endif
