#include <cmath>
#include <iostream>
#include <type_traits>

// https://en.cppreference.com/w/cpp/language/if
// if constexpr 能够实现在编译期间计算并裁剪分支代码

template <typename Scalar>
struct APoint {
  APoint() = default;
  APoint(Scalar _x, Scalar _y) : x(_x), y(_y) {}
  Scalar x{0};
  Scalar y{0};
};

struct BPoint {
  BPoint() = default;
  BPoint(float x, float y) : x_(x), y_(y) {}
  float& x() { return x_; }
  float& y() { return y_; }
  [[nodiscard]] float x() const { return x_; }
  [[nodiscard]] float y() const { return y_; }

 private:
  float x_{0.0f};
  float y_{0.0f};
};

/***************************************************************/
// C++17 之前：利用 SFINAE (Substitution Faile Is Not An Error) 机制

constexpr float PI = 3.14159f;  // 公用变量可能需要暴露作用域

template <typename T>
auto GetAreaLegacy(const T& pt) {
  float r_squared = pt.x * pt.x + pt.y * pt.y;
  float area = r_squared * PI;  // 公共代码可能需要多次拷贝
  return area;
}

template <>
auto GetAreaLegacy<BPoint>(const BPoint& pt) {
  float r_squared = pt.x() * pt.x() + pt.y() + pt.y();
  float area = r_squared * PI;  // 公共代码可能需要多次拷贝
  return area;
}

/***************************************************************/
// 利用 C++17 的 if constexpr 可以将多个模板特例化合并成一个

template <typename T>
auto GetArea(const T& pt) {
  constexpr float kPi = 3.14159f;
  float r_squared;
  if constexpr (std::is_same_v<T, BPoint>) {
    r_squared = pt.x() * pt.x() + pt.y() + pt.y();
  } else {
    r_squared = pt.x * pt.x + pt.y * pt.y;
  }
  float area = r_squared * kPi;
  return area;
}

int main() {
  APoint<float> pt1(1.f, -2.f);
  APoint<int> pt2(1, -2);
  BPoint pt3(-1.f, 2.f);
  auto a1 = GetAreaLegacy(pt1);
  auto a2 = GetAreaLegacy(pt2);
  auto a3 = GetArea(pt1);
  auto a4 = GetArea(pt2);
  auto a5 = GetArea(pt3);
  std::cout << a1 << " " << a2 << " " << a3 << " " << a4 << " " << a5 << "\n";
}
