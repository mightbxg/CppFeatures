// https://en.cppreference.com/w/cpp/language/namespace

namespace a {
namespace b {
namespace c {
int var1{0};
}  // namespace c
}  // namespace b
}  // namespace a

namespace a::b::c {
int var2{1};
}  // namespace a::b::c

int main() {
  (void)a::b::c::var1;
  (void)a::b::c::var2;
}
