#include <cmath>
#include <iostream>

constexpr auto Pi = 3.14;

class Shape {
public:
  virtual ~Shape() = default;
  virtual void draw() = 0;
  virtual double area() = 0;
};

class Circle : public Shape {
public:
  Circle(double radius) : radius_{radius} {}
  void draw() override { std::cout << "Circle\n"; }
  double area() override { return Pi * std::pow(radius_, 2); }

private:
  double radius_;
};

int main() {}