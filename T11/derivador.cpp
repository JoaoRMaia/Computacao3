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



// Divisao
template <typename F1, typename F2>
class Divide {
public:
    Divide(F1 f1, F2 f2) : f1(f1), f2(f2) {}

    double e(double v) {
        return f1.e(v) / f2.e(v);
    }

    double dx(double v) {
        return (f1.dx(v) * f2.e(v) - f1.e(v) * f2.dx(v)) / (f2.e(v) * f2.e(v)) ;
    }

private:
    F1 f1;
    F2 f2;
};


template <typename F1, typename F2>
Divide<F1, F2> operator / (F1 f1, F2 f2) {
    return Divide<F1, F2>(f1, f2);
}

template <typename F2>
Divide<Cte, F2> operator / (double n, F2 f2) {
    return Divide<Cte, F2>(n, f2);
}

template <typename F1>
Divide<F1, Cte> operator / (F1 f1, double n) {
    return Divide<F1, Cte>(f1, n);
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
// Subt
// Sub

template <typename F1, typename F2>
class Subtrai {
public:
    Subtrai(F1 f1, F2 f2) : f1(f1), f2(f2) {}

    double e(double v) {
        return f1.e(v) - f2.e(v);
    }

    double dx(double v) {
        return f1.dx(v) - f2.dx(v);
    }

private:
    F1 f1;
    F2 f2;
};


template <typename F1, typename F2>
Subtrai<F1, F2> operator - (F1 f1, F2 f2) {
    return Subtrai<F1, F2>(f1, f2);
}

template <typename F2>
Subtrai<Cte, F2> operator - (double n, F2 f2) {
    return Subtrai<Cte, F2>(n, f2);
}

template <typename F1>
Subtrai<F1, Cte> operator - (F1 f1, double n) {
    return Subtrai<F1, Cte>(f1, n);
}
// Sen

template <typename T>
class Seno {
public:
    Seno(T f1) : f1(f1) {}

    double e(double v) {
        return sin(f1.e(v));
    }

    double dx(double v) {
        return cos(f1.e(v)) * f1.dx(v);
    }

private:
    T f1;
};

template <typename T>
Seno<T> sin(T v) {
    return Seno<T>(v);
}
// Cos
template <typename T>
class Cos {
public:
    Cos(T f1) : f1(f1) {}

    double e(double v) {
        return cos(f1.e(v));
    }

    double dx(double v) {
        return -sin(f1.e(v))*f1.dx(v);
    }

private:
    T f1;
};

template <typename T>
Cos<T> cos(T v) {
    return Cos<T>(v);
}

X x;
Cte c;




#ifdef NDEBUG

int main() {
    c = Cte(3);

    auto f1 = 3.0 * x * x;
    auto f2 = x * x * (x + 8.0) + x;
    auto f3 = sin(x * x * cos(3.14 * x + 1.0));
    auto f4 = sin(x * x - cos(3.14 * x + 1.0));
    double v = 3.14159;
    auto f = sin(x) / cos(x);
    cout << f.e(v) << endl;

    return 0;
}

#endif
