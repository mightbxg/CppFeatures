#include "5_inline_variable.h"

int a_extern{0};
int MyStruct::m_static{0};

void PrintVarAddress1() {
  Print("       a_static", a_static);
  Print("        a_const", a_const);
  Print("       a_extern", a_extern, true);
  Print("       a_inline", a_inline, true);
  Print("a_inline_static", a_inline_static);
  Print("       m_static", MyStruct::m_static, true);
  Print("m_inline_static", MyStruct::m_inline_static, true);
}
