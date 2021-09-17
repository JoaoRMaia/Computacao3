#include <iostream>
#include <cmath>
#include <type_traits>
#include <string>
#include <sstream>

using namespace std;

// X

class X {
public:
    string str() const {
        return "(x)";
    }
    string dx_str() const {
        return "(1)";
    }
    double e(double v) const {
        return v;
    }
    double dx(double x) const {
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
    string str() const { 
        stringstream ss;
        ss << "(" << c << ")";
        return ss.str(); 
    }
    string dx_str() const { 
        stringstream ss;
        ss << "(" << 0 << ")"; 
        return ss.str();
    }
    double e(double v) const {
        return c;
    }

    double dx(double x) const {
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
    string str() const {
        stringstream ss;
        ss << "(" << f1.str() << "*" << f2.str() << ")";
        return ss.str();
    }
    string dx_str() const {
        stringstream ss;
        ss << "(" << f2.dx_str() << "*" << f1.str() << "+" << f2.str() << "*" << f1.dx_str() << ")";
        return ss.str();
    }

    double e(double v) const {
        return f1.e(v) * f2.e(v);
    }

    double dx(double v) const {
        return f1.e(v) * f2.dx(v) + f1.dx(v) * f2.e(v);
    }

private:
    F1 f1;
    F2 f2;
};


template <typename F1, typename F2>
auto operator * (F1 f1, F2 f2) {
    if constexpr (is_integral_v<F1> || is_floating_point_v<F1>) return Multiplica<Cte, F2>(f1, f2);
    else if constexpr (is_integral_v<F2> || is_floating_point_v<F2>) return Multiplica<F1, Cte>(f1, f2);
    else return Multiplica<F1, F2>(f1, f2);
}



// Divisao
template <typename F1, typename F2>
class Divide {
public:
    Divide(F1 f1, F2 f2) : f1(f1), f2(f2) {}
    string str() const {
        stringstream ss;
        ss << "(" << f1.str() << "/" << f2.str() << ")";
        return ss.str();
    }
    string dx_str() const {
        stringstream ss;
        ss << "(" << f1.dx_str() << "*" << f2.str() << "-" << f1.str() << "*" << f2.dx_str() << "/" <<f2.str() << "*" << f2.str() << ")";
        return ss.str();
    }

    double e(double v) const {
        return f1.e(v) / f2.e(v);
    }

    double dx(double v) const {
        return (f1.dx(v) * f2.e(v) - f1.e(v) * f2.dx(v)) / (f2.e(v) * f2.e(v));
    }

private:
    F1 f1;
    F2 f2;
};

template <typename F1, typename F2>
auto operator / (F1 f1, F2 f2) {
    if constexpr (is_integral_v<F1> || is_floating_point_v<F1>) return Divide<Cte, F2>(f1, f2);
    else if constexpr (is_integral_v<F2> || is_floating_point_v<F2>) return Divide<F1, Cte>(f1, f2);
    else return Divide<F1, F2>(f1, f2);
}

// Soma

template <typename F1, typename F2>
class Soma {
public:
    Soma(F1 f1, F2 f2) : f1(f1), f2(f2) {}
    string str() const { 
        return "(" + f1.str() + "+" + f2.str() + ")";
    }
    string dx_str() const { 
        return "(" + f1.dx_str() + "+" + f2.dx_str() + ")";
    }

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
auto operator + (F1 f1, F2 f2) {
    if constexpr (is_integral_v<F1> || is_floating_point_v<F1>) return Soma<Cte, F2>(f1, f2);
    else if constexpr (is_integral_v<F2> || is_floating_point_v<F2>) return Soma<F1, Cte>(f1, f2);
    else return Soma<F1, F2>(f1, f2);
}
//Subt

template <typename F1, typename F2>
class Subtrai {
public:
    Subtrai(F1 f1, F2 f2) : f1(f1), f2(f2) {}
    string str() const { return "(" + f1.str() + "-" + f2.str() + ")"; }
    string dx_str() const { return "(" + f1.dx_str() + "-" + f2.dx_str() + ")"; }

    double e(double v) const {
        return f1.e(v) - f2.e(v);
    }

    double dx(double v) const {
        return f1.dx(v) - f2.dx(v);
    }

private:
    F1 f1;
    F2 f2;
};


template <typename F1, typename F2>
auto operator - (F1 f1, F2 f2) {
    if constexpr (is_integral_v<F1> || is_floating_point_v<F1>) return Subtrai<Cte, F2>(f1, f2);
    else if constexpr (is_integral_v<F2> || is_floating_point_v<F2>) return Subtrai<F1, Cte>(f1, f2);
    else return Subtrai<F1, F2>(f1, f2);
}
// Sen

template <typename T>
class Seno {
public:
    Seno(T f1) : f1(f1) {}
    string str() const {
        stringstream ss;
        ss << "sin(" << f1.str() << ")";
        return ss.str();
    }
    string dx_str() const {
        stringstream ss;
        ss << "cos(" << f1.str() << "*" << f1.dx_str() << ")";
        return ss.str();
    }

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
    string str() const {

        stringstream ss;
        ss  << "cos(" << f1.str() << ")";
        return ss.str();
    }
    string dx_str() const {
        stringstream ss;
        ss << "-sin(" << f1.str() << "*" << f1.dx_str() << ")";
        return ss.str();
    }

    double e(double v) {
        return cos(f1.e(v));
    }

    double dx(double v) {
        return -sin(f1.e(v)) * f1.dx(v);
    }

private:
    T f1;
};

template <typename T>
Cos<T> cos(T v) {
    return Cos<T>(v);
}
// Potenciação

template <typename F1, typename F2>
class Expoente {
public:
    Expoente(F1 f1, F2 f2) : f1(f1), f2(f2) {}
    string str() const {
        stringstream ss;
        ss << f1.str() << "^" << f2.e(1);
        return ss.str();
    }
    string dx_str() const {
        stringstream ss;
        auto exp = f2.e(1) - 1;
        ss << "(" << exp+1 << "*" << f1.dx_str() << "*" << f1.str() << "^" << exp << ")";
        return ss.str();
    }

    double e(double v) {
        return pow(f1.e(v), f2.e(v));
    }

    double dx(double v) {
        return f2.e(v) * pow(f1.e(v), f2.e(v) - 1) * f1.dx(v);
    }

private:
    F1 f1;
    F2 f2;
};

template <typename T, typename Int>
auto operator ->*(T v, Int n) {
    if constexpr (is_same_v<Int, int>) {
        return Expoente<T, Cte>(v, Cte(n));
    }
    else static_assert(is_same_v<Int, int>, "Operador de potenciação definido apenas para inteiros");
}

/* Recursivo
template <typename F, typename Int>
auto operator ->* (F f, Int n) {
    if constexpr (is_same_v<Int, int>) {
        if (n == 1) return Multiplica<F,int>(f,1);
        else {
            return f * f->*(n - 1);
        }
    }
    else static_assert("Operador de potenciação definido apenas para inteiros");
}
*/
// E^x
template <typename T>
class Exp {
public:
    Exp(T f1) : f1(f1) {}

    string str() const {
        stringstream ss;
        ss << "exp(" << f1.str() << ")";
        return ss.str();
    }
    string dx_str() const {
        stringstream ss;
        ss << "(" << "exp(" << f1.str() << ")*" << f1.dx_str() << ")";
        return ss.str();
    }

    double e(double v) {
        return exp(f1.e(v));
    }

    double dx(double v) {
        return exp(f1.e(v)) * f1.dx(v);
    }

private:
    T f1;
};

template <typename T>
Exp<T> exp(T v) {
    return Exp<T>(v);
}
// log

template <typename T>
class Log {
public:
    Log(T f1) : f1(f1) {}

    string str() const {
        stringstream ss;
        ss << "(log(" << f1.str() << "))";
        return ss.str();
    }
    string dx_str() const {
        stringstream ss;
        ss << "(" << "1/" << f1.str() << ")*" << f1.dx_str() << ")";
        return ss.str();
    }

    double e(double v) {
        return log(f1.e(v));
    }

    double dx(double v) {
        return 1 / f1.e(v) * f1.dx(v);
    }

private:
    T f1;
};

template <typename T>
Log<T> log(T v) {
    return Log<T>(v);
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
    auto f5 = sin(x) / cos(x);
    auto f6 = x->*3;
    auto f8 = 1 / (1 + exp(-2 * (x - 1)->*4));
    auto f9 = exp(x * log(x - 8.0) + 1.0);
    double v = 3;
    //auto f10 = x->*1.1;

    cout << "f(x) = "<< f9.str() << ", f'(x) = " << f9.dx_str() << endl;


    return 0;
}

#endif
