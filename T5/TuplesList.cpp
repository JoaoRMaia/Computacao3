#include <initializer_list>
#include <iostream>

using namespace std;

struct AbstractPair;

struct ImplrPair{
	
}

class Pair {
public:
  template <typename A, typename B>
  Pair( A a, B b ) {
	  cout << a << b << endl;
	  p = new AbstractPair<A,B>(a,b);
	  
    
  }
private:
  AbstractPair *p;
};

struct AbstractPair : public Pair {
	
	template<typename A, typename B>
	AbstractPair ( A a, B b){
		cout << a << b << endl;
		
	}
	
	A a;
	B b;
	
	
	
};

void print( ostream& o, initializer_list<Pair> lista ) {
	}

int main() {
 
    Pair p( "1", 2 );
    cout << typeid(p).name();
  
    print( cout, { { "jan", 1 }, { 2, "fev" }, { string( "pi" ), 3.14 } } );

  return 0;  
}
