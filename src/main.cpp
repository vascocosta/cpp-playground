#include <cmath>
#include <iostream>

constexpr auto Pi = 3.14;

class Shape {
public:
  virtual ~Shape() = default;
  virtual void draw() = 0;
  virtual double area() const = 0;
};

class Circle : public Shape {
public:
  Circle(double radius) : radius_{radius} {}
  void draw() override { std::cout << "Circle\n"; }
  double area() const override { return Pi * std::pow(radius_, 2); }

private:
  double radius_;
};

class Rectangle : public Shape {
public:
  Rectangle(double width, double height) : width_{width}, height_{height} {}
  void draw() override { std::cout << "Rectangle\n"; }
  double area() const override { return width_ * height_; }

private:
  double width_;
  double height_;
};

int main() {
  Circle c{10.5};

  Shape &s = c;

  s.draw();
}