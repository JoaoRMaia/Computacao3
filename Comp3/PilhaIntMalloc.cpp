using namespace std;

struct PilhaInt {

    PilhaInt() {
        topo = 0;
        elementos = (int*)malloc(tam * sizeof(int));

    }
    PilhaInt(int n) {
        topo = 0;
        tam = n;
        elementos = (int*)malloc(tam * sizeof(int));

    }
    PilhaInt(PilhaInt& p) {
        elementos = (int*)malloc(p.capacidade() * sizeof(int));
        tam = p.capacidade();
        topo = 0;
        for (int i = p.count() - 1; i >= 0; i--) {
            elementos[i] = p.desempilha();
            topo++;
        }
        p.alteraTopo(topo);

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
    void dobraCap() {
        int* novoElementos = (int*)malloc(2 * tam * sizeof(int));
        for (int i = 0; i < tam; i++) {
            novoElementos[i] = elementos[i];
        }
        free(elementos);
        elementos = novoElementos;
        tam *= 2;
    }
    void empilha(int n) {
        if (topo == tam) {
            this->dobraCap();
        }
        elementos[topo++] = n;
    }

    int desempilha() {
        return elementos[--topo];
    }

    void alteraTopo(int n) {
        topo = n;
    }
    void redimensiona(int n) {
        while (topo > n) {
            this->desempilha();
        }
        tam = n;
    }
    int count() {
        return topo;
    }
    int capacidade() {
        return tam;
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
        if (elementos == p.elementos) return;  // bug da autoatribuição
        topo = 0;
        free(elementos);
        elementos = (int*)malloc(p.capacidade() * sizeof(int));
        tam = p.capacidade();
        for (int i = p.count() - 1; i >= 0; i--) {
            elementos[i] = p.desempilha();
            topo++;
        }
        p.alteraTopo(topo);
    }
private:
    int topo;
    int* elementos;
    int tam = 100;
};