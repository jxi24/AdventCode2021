#ifndef BRENT_HH
#define BRENT_HH

#include <cmath>
#include <limits>
#include <functional>
#include <stdexcept>
#include <string>
#include <iostream>

template<class ContainerT>
void tokenize(const std::string& str, ContainerT& tokens,
              const std::string& delimiters=" \n\t", bool trimEmpty=true) {
    std::string::size_type lastPos = 0, length = str.length();
    
    using value_type = typename ContainerT::value_type;
    using size_type = typename ContainerT::size_type;

    while(lastPos < length+1) {
        std::string::size_type pos = str.find_first_of(delimiters, lastPos);
        if(pos == std::string::npos) pos = length;

        if(pos != lastPos || !trimEmpty) {
            tokens.push_back(value_type(str.data()+lastPos,
                             static_cast<size_type>(pos)-lastPos));
        }
        lastPos = pos+1;
    }
}

class Brent {
    public:
        /// Constructor
        ///@param func: Function to find the root of
        ///@param tol: The tolerance in the solution
        Brent(std::function<double(double)>  _func, double tol=base_tol)
            : func(std::move(_func)), m_tol(tol) {}

        // Functions
        double Minimize(double min, double max) const {
            double x, w, v, u, delta, delta2, fu, fv, fw, fx, mid, fract1, fract2;
            x = w = v = max;
            fw = fv = fx = func(x);
            delta2 = delta = 0;
            size_t count = itmax;
            do {
                mid = (min + max) / 2;
                fract1 = m_tol * std::abs(x) + m_tol / 4;
                fract2 = 2 * fract1;
                if(std::abs(x - mid) <= (fract2 - (max - min) / 2))
                    break;

                if(std::abs(delta2) > fract1) {
                    double r = (x - w) * (fx - fv);
                    double q = (x - v) * (fx - fw);
                    double p = (x - v) * q - (x - w) * r;
                    q = 2 * (q - r);
                    if(q > 0) p = -p;
                    q = std::abs(q);
                    double td = delta2;
                    delta2 = delta;
                    if((std::abs(p) >= std::abs(q * td / 2)) || (p <= q * (min - x)) || (p >= q * (max - x))) {
                        delta2 = (x >= mid) ? min - x : max - x;
                        delta = cgold * delta2;
                    } else {
                        delta = p / q;
                        u = x + delta;
                        if(((u - min) < fract2) || ((max - u) < fract2))
                            delta = (mid - x) < 0 ? -std::abs(fract1) : std::abs(fract1);
                    }
                } else {
                    delta2 = (x >= mid) ? min - x : max - x;
                    delta = cgold*delta2;
                }
                u = (std::abs(delta) >= fract1) ? (x + delta) : (delta > 0 ? (x + std::abs(fract1)) : (x - std::abs(fract1)));
                fu = func(u);
                if(fu <= fx) {
                    if(u >= x) min = x;
                    else max = x;
                    v = w;
                    w = x;
                    x = u;
                    fv = fw;
                    fw = fx;
                    fx = fu;
                } else {
                    if(u < x) min = u;
                    else max = u;
                    if((fu <= fw) || (w == x)) {
                        v = w;
                        w = u;
                        fv = fw;
                        fw = fu;
                    } else if((fu <= fv) || (v == x) || (v == w)) {
                        v = u;
                        fv = fu;
                    }
                }
            } while(--count);

            return x;
        }

    private:
        // Variables
        std::function<double(double)> func;
        double m_tol;
        bool mflag;
        static constexpr double base_tol = 1e-6;
        static const size_t itmax = 100;
        static constexpr double tiny = 1.0E-20;
        static constexpr double glimit = 100.0;
        static constexpr double gold = 1.618034;
        static constexpr double cgold = 0.3819660;
        static constexpr double eps = std::numeric_limits<double>::epsilon()*1.0E-3;
};

#endif
