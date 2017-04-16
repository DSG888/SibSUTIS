#ifndef FFT_H_
#define FFT_H_

struct Complex;
struct ShortComplex;

extern void fft(ShortComplex *x, int T, bool complement);

struct ShortComplex
{
    double re, im;
    inline void operator=(const Complex &y);
};

struct Complex
{
    long double re, im;
    inline void operator= (const Complex &y);
    inline void operator= (const ShortComplex &y);
};


inline void ShortComplex::operator=(const Complex &y)    { re = (double)y.re; im = (double)y.im;  }
inline void Complex::operator= (const Complex &y)       { re = y.re; im = y.im; }
inline void Complex::operator= (const ShortComplex &y)  { re = y.re; im = y.im; }

#endif

//This is minimized version of type 'complex'. All operations is inline
static long double temp;
inline void operator+=(ShortComplex &x, const Complex &y)        { x.re += (double)y.re; x.im += (double)y.im; }
inline void operator-=(ShortComplex &x, const Complex &y)        { x.re -= (double)y.re; x.im -= (double)y.im; }
inline void operator*=(Complex &x,        const Complex &y)        { temp = x.re; x.re = temp * y.re - x.im * y.im; x.im = temp * y.im + x.im * y.re; }
inline void operator*=(Complex &x,        const ShortComplex &y)    { temp = x.re; x.re = temp * y.re - x.im * y.im; x.im = temp * y.im + x.im * y.re; }
inline void operator/=(ShortComplex &x, double div)                { x.re /= div; x.im /= div; }

