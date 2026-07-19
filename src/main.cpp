#include <iostream>
#include <ostream>

// class Vector {
// public:
//   Vector(int size)
//       : elem{new double[static_cast<std::size_t>(size)]}, sz{size} {}
//   Vector(const Vector &other) = default;
//   ~Vector() { delete[] elem; }
//   // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
//   auto operator[](int idx) -> double & { return elem[idx]; }
//   [[nodiscard]] auto size() const -> int { return sz; }

// private:
//   double *elem;
//   int sz;
// };

class Complex {
public:
  // NOLINTNEXTLINE
  Complex(double r, double i) : re{r}, im{i} {}
  Complex(const double r) : re{r}, im{0} {}
  Complex() : re{0}, im{0} {}

  [[nodiscard]] auto real() const -> double { return re; }
  auto real(double r) -> void { re = r; }
  [[nodiscard]] auto imag() const -> double { return im; }
  auto imag(double i) -> void { im = i; }

  auto operator+=(Complex z) -> Complex & {
    re += z.re;
    im += z.im;

    return *this;
  }

  auto operator-=(Complex z) -> Complex & {
    re -= z.re;
    im -= z.im;

    return *this;
  }

  auto operator*=(Complex z) -> Complex & {
    auto new_re = (re * z.re) - (im * z.im);
    auto new_im = (re * z.im) + (im * z.re);

    re = new_re;
    im = new_im;

    return *this;
  }

  auto operator/=(Complex z) -> Complex & {
    double denominator = (z.re * z.re) + (z.im * z.im);

    double new_re = ((re * z.re) + (im * z.im)) / denominator;
    double new_im = ((im * z.re) - (re * z.im)) / denominator;

    re = new_re;
    im = new_im;

    return *this;
  }

private:
  double re, im;
};

auto operator+(Complex z1, Complex z2) -> Complex {
  return Complex{z1.real() + z2.real(), z1.imag() + z2.imag()};
}

auto operator<<(std::ostream &os, const Complex &z) -> std::ostream & {
  os << z.real() << " + " << z.imag() << "i";

  return os;
}

auto main() -> int {
  Complex z1{1, 2};
  const Complex z2{3, 4};

  auto sum = z1 + z2;

  std::cout << sum << "\n";

  std::cout << (z1 += z2);

  return EXIT_SUCCESS;
}