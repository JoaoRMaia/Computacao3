#include <iostream>
#include <cmath>

using namespace std;

// X

class X {
public:
    double e(double v) {
        return v;
    }
    double dx(double x) {
        return 1;
    }
};
// Cte
class Cte {
public:
    Cte() {
        c = 0;
    }
    Cte(double c) : c(c) {}
    double e(double v) {
        return c;
    }

    double dx(double x) {
        return 0;
    }

private:
    double c;
};
// Multiplicação

template <typename F1, typename F2>
class Multiplica {
public:
    Multiplica(F1 f1, F2 f2) : f1(f1), f2(f2) {}

    double e(double v) {
        return f1.e(v) * f2.e(v);
    }

    double dx(double v) {
        return f1.e(v) * f2.dx(v) + f1.dx(v) * f2.e(v);
    }

private:
    F1 f1;
    F2 f2;
};


template <typename F1, typename F2>
Multiplica<F1, F2> operator * (F1 f1, F2 f2) {
    return Multiplica<F1, F2>(f1, f2);
}

template <typename F2>
Multiplica<Cte, F2> operator * (double n, F2 f2) {
    return Multiplica<Cte, F2>(n, f2);
}

template <typename F1>
Multiplica<F1, Cte> operator * (F1 f1, double n) {
    return Multiplica<F1, Cte>(f1, n);
}
// Soma

template <typename F1, typename F2>
class Soma {
public:
    Soma(F1 f1, F2 f2) : f1(f1), f2(f2) {}

    double e(double v) {
        return f1.e(v) + f2.e(v);
    }

    double dx(double v) {
        return f1.dx(v) + f2.dx(v);
    }

private:
    F1 f1;
    F2 f2;
};


template <typename F1, typename F2>
Soma<F1, F2> operator + (F1 f1, F2 f2) {
    return Soma<F1, F2>(f1, f2);
}

template <typename F2>
Soma<Cte, F2> operator + (double n, F2 f2) {
    return Soma<Cte, F2>(n, f2);
}

template <typename F1>
Soma<F1, Cte> operator + (F1 f1, double n) {
    return Soma<F1, Cte>(f1, n);
}


template <typename T>
class Seno {
public:
    Seno(T f1) : f1(f1) {}

    double e(double v) {
        return sin(v);
    }

    double dx(double v) {
        return cos(v);
    }

private:
    T f1;
};


/*
template <typename F1, typename F2>
Seno<F1, F2> operator + (F1 f1, F2 f2) {
    return Soma<F1, F2>(f1, f2);
}

template <typename F2>
Seno<Cte, F2> operator + (double n, F2 f2) {
    return Soma<Cte, F2>(n, f2);
}

template <typename F1>
Seno<F1, Cte> operator + (F1 f1, double n) {
    return Soma<F1, Cte>(f1, n);
}
*/

template <typename T>
Seno<T> sin(T v) {
    return Seno<T>(v);
}

X x;
Cte c;




#ifdef NDEBUG

int main() {
    c = Cte(3);

    auto f1 = 3.0 * x * x;
    auto f2 = x * x * (x + 8.0) + x;
    auto f3 = sin(x * x * 3.14 * x + 1.0);

    cout << f3.e(5.1) << endl;
    cout << f2.dx(5.1) << endl;

    return 0;
}

#endif
