#include <cstddef>
#include <iostream>
#include <ostream>
#include <random>
#include <stdexcept>
#include <vector>

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

auto operator*(Complex z1, Complex z2) -> Complex {
  auto new_re = (z1.real() * z2.real()) - (z1.imag() * z2.imag());
  auto new_im = (z1.real() * z2.imag()) + (z1.imag() * z2.real());

  return Complex{new_re, new_im};
}

auto operator<<(std::ostream &os, const Complex &z) -> std::ostream & {
  os << z.real() << " + " << z.imag() << "i";

  return os;
}

template <typename T> class Matrix {
public:
  Matrix() : rows_{0}, cols_{0} {}
  Matrix(std::size_t rows, std::size_t cols)
      : rows_{rows}, cols_{cols}, data_(rows * cols) {}
  Matrix(std::size_t rows, std::size_t cols, const T &initial_data)
      : rows_{rows}, cols_{cols}, data_(rows * cols, initial_data) {}

  auto operator()(std::size_t row, std::size_t col) -> T & {
    return data_.at((row * cols_) + col);
  }

  auto operator()(std::size_t row, std::size_t col) const -> const T & {
    return data_.at((row * cols_) + col);
  }

  [[nodiscard]] auto rows() const -> std::size_t { return rows_; }
  [[nodiscard]] auto cols() const -> std::size_t { return cols_; }

  auto at(std::size_t row, std::size_t col) -> T & {
    if (row >= rows_ || col >= cols_) {
      throw std::out_of_range{"Matrix indexes out of range."};
    }

    return (*this)(row, col);
  }

private:
  std::size_t rows_;
  std::size_t cols_;
  std::vector<T> data_;
};

template <typename T>
auto operator+(const Matrix<T> &m1, const Matrix<T> &m2) -> Matrix<T> {
  if (m1.rows() != m2.rows() || m1.cols() != m2.cols()) {
    throw std::out_of_range{
        "Matrices must have the same number of rows and columns."};
  }

  Matrix<T> result{m1.rows(), m1.cols()};

  for (std::size_t r = 0; r < m1.rows(); ++r) {
    for (std::size_t c = 0; c < m1.cols(); ++c) {
      result(r, c) = m1(r, c) + m2(r, c);
    }
  }

  return result;
}

template <typename T>
auto operator-(const Matrix<T> &m1, const Matrix<T> &m2) -> Matrix<T> {
  if (m1.rows() != m2.rows() || m1.cols() != m2.cols()) {
    throw std::out_of_range{
        "Matrices must have the same number of rows and columns."};
  }

  Matrix<T> result{m1.rows(), m1.cols()};

  for (std::size_t r = 0; r < m1.rows(); ++r) {
    for (std::size_t c = 0; c < m1.cols(); ++c) {
      result(r, c) = m1(r, c) - m2(r, c);
    }
  }

  return result;
}

template <typename T>
auto operator*(const Matrix<T> &m1, const Matrix<T> &m2) -> Matrix<T> {
  if (m1.cols() != m2.rows()) {
    throw std::out_of_range{
        "First matrix columns must match the second matrix rows."};
  }

  Matrix<T> result{m1.rows(), m2.cols()};

  for (std::size_t r = 0; r < m1.rows(); ++r) {
    for (std::size_t c = 0; c < m2.cols(); ++c) {
      T sum{};
      for (std::size_t idx = 0; idx < m1.cols(); ++idx) {
        sum += m1(r, idx) * m2(idx, c);
      }
      result(r, c) = sum;
    }
  }

  return result;
}

template <typename T>
auto generate_random_matrix(std::size_t rows, std::size_t cols, double range)
    -> Matrix<T> {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dist(-range, range);

  Matrix<T> mat(rows, cols);
  for (std::size_t r = 0; r < rows; ++r) {
    for (std::size_t c = 0; c < cols; ++c) {
      mat(r, c) = T{dist(gen), dist(gen)};
    }
  }
  return mat;
}

void run_matrix_benchmark() {
  constexpr std::size_t MATRIX_SIZE{512};
  constexpr int NUM_RUNS{1000};
  constexpr double RANGE{10};

  std::cout << "Generating random data...\n";
  std::vector<Matrix<Complex>> left_matrices;
  std::vector<Matrix<Complex>> right_matrices;

  for (int i = 0; i < NUM_RUNS; ++i) {
    left_matrices.push_back(
        generate_random_matrix<Complex>(MATRIX_SIZE, MATRIX_SIZE, RANGE));
    right_matrices.push_back(
        generate_random_matrix<Complex>(MATRIX_SIZE, MATRIX_SIZE, RANGE));
  }

  std::cout << "Running " << NUM_RUNS << " multiplications...\n";

  double checksum = 0.0;

  for (int i = 0; i < NUM_RUNS; ++i) {
    Matrix<Complex> result = left_matrices[i] * right_matrices[i];

    checksum += result(0, 0).real();
  }

  std::cout << "Optimization guard checksum: " << checksum << "\n";
}

// NOLINTNEXTLINE
auto main() -> int {
  run_matrix_benchmark();

  return EXIT_SUCCESS;
}