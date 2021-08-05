#include <initializer_list>
#include <iostream>

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
	  p = new ImplPair<A,B>(a,b);
	  
  }
  
  AbstractPair *p;
};


void print( ostream& o, initializer_list<Pair> lista ) {
	for (auto e : lista){
		e.p->print(o);
	}
}

int main() {
 
    Pair p( "1", 2 );
    cout << typeid(p).name() << endl;
  
    print( cout, { { "jan", 1 }, { 2, "fev" }, { string( "pi" ), 3.14 } } );

  return 0;  
}
