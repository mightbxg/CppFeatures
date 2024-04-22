
static void func1() {}
[[maybe_unused]] static void func2() {}

int main() {
  int v1 = 0;
  [[maybe_unused]] int v2 = 0;
}
