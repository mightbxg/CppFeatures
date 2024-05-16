#include "5_inline_variable.h"

void PrintVarAddress2() {
  Print("       a_static", a_static);
  Print("        a_const", a_const);
  Print("       a_extern", a_extern, true);
  Print("       a_inline", a_inline, true);
  Print("a_inline_static", a_inline_static);
  Print("       m_static", MyStruct::m_static, true);
  Print("m_inline_static", MyStruct::m_inline_static, true);
}

int main() {
  a_static = a_extern = a_inline = a_inline_static = MyStruct::m_static =
      MyStruct::m_inline_static = 1;

  PrintVarAddress1();
  std::cout << "---------------------------------\n";
  PrintVarAddress2();
}