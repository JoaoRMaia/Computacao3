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
  Pair( A a, B b ){
	  p = shared_ptr<AbstractPair>{new ImplPair<A,B>(a,b)};
  }
  shared_ptr<AbstractPair> p;
};


void print( ostream& o, initializer_list<Pair> lista ) {
	for (auto e : lista){
		e.p->print(o);
	}
}

#ifdef NDEBUG

class Leak {
    public:
        Leak(): n( ++contador ) {
            cout << "Criou: " << n << endl;
        }

        Leak( const Leak& p ): n( ++contador ) {
            cout << "Criou: " << n << " copiando de " << p.n << endl;
        }

        ~Leak() {
            cout << "Destruiu: " << n << endl;
        }

        ostream& print( ostream& o ) const {
            return o << "lk(" << n << ")";
        }

        static int contador;
        int n;
};

void operator <<( ostream& o, Leak l ) {
    o << "lk(" << l.n << ")";
}

int Leak::contador = 0;

int main (){
    print( cout, { { "jan", Leak() }, { string( "pi" ), Leak() } } );

	return 0;
}

#endif
