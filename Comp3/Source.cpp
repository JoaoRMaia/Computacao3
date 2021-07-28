

using namespace std;

struct PilhaInt {

    PilhaInt() {
        topo = 0;
        elementos = (int*)malloc(MAX_SIZE * sizeof(int));

    }
    void print(std::ostream& o) {
        o << "[ " << elementos[0];
        for (int i = 1; i < topo; i++) {
            o << ", " << elementos[i];
        }
        o << " ]";
    }
    void print(std::ostream& o, const char* msg) {
        o << msg << endl;
    }

    void empilha(int n) {
        elementos[topo++] = n;
    }

    int desempilha() {
        return elementos[--topo];
    }

    void alteraTopo(int n) {
        topo = n;
    }

    int count() {
        return topo;
    }

    bool isempty() {
        return topo == 0;
    }


    ~PilhaInt() {
        free(elementos);
    }

    PilhaInt& operator << (int n) {
        this->empilha(n);
        return *this;
    }
    void operator= (PilhaInt& p) {
        topo = 0;
        for (int i = p.count() - 1; i >= 0; i--) {
            elementos[i] = p.desempilha();
            topo++;
        }


        p.alteraTopo(topo);
    }
private:
    int topo;
    int* elementos;
    const int MAX_SIZE = 100;
};

