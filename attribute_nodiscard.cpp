
struct MyStruct {
  explicit MyStruct(int val) : val_(val) {}
  [[nodiscard]] int get_val() const { return val_; }

 private:
  int val_{0};
};

int main() {
  MyStruct s(10);
  s.get_val();
}
