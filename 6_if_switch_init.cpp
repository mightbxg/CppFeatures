#include <deque>
#include <iostream>
#include <mutex>

// https://en.cppreference.com/w/cpp/language/if
// https://en.cppreference.com/w/cpp/language/switch

class MyClass {
 public:
  [[nodiscard]] double GetLastDataLegacy() const {
    double d = -1.0;
    {  // 为了使 mutex 自动解锁，需要额外加一层大括号
      std::scoped_lock lock(mutex_data_);
      if (!data_.empty()) {
        d = data_.back();
      }
    }
    d *= 2.0;
    return d;
  }

  [[nodiscard]] double GetLastData() const {
    double d = -1.0;
    // C++17 的 init-statement 可以省去一层大括号
    if (std::scoped_lock lock(mutex_data_); !data_.empty()) {
      d = data_.back();
    }
    d *= 2.0;
    return d;
  }

 private:
  mutable std::mutex mutex_data_;
  std::deque<double> data_;
};

enum ErrorCode {
  kNoErr = 0,
  kErrA,
  kErrB,
};

ErrorCode SomeAwesomeFunction(int v) {
  return v > 0 ? kErrA : v < 0 ? kErrB : kNoErr;
}

int main() {
  // 利用 init-statement 做临时变量的作用域隔离
  if (auto ec = SomeAwesomeFunction(1); ec != kNoErr) {
    std::cout << "error: " << ec << "\n";
  }
  switch (auto ec = SomeAwesomeFunction(-1); ec) {
    case kNoErr:
      std::cout << "no err\n";
      break;
    case kErrA:
      std::cout << "err A\n";
      break;
    case kErrB:
      std::cout << "err B\n";
      break;
    default:
      std::cout << "unknown err " << ec << "\n";
  }
}