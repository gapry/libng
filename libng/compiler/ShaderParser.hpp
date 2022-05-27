#pragma once

#include <libcxx/util/util.hpp>

namespace libng {

class ShaderParser {
public:
  class ExprAST {
  public:
    virtual ~ExprAST() = default;
  };

  template<typename T>
  class NumberExprAST : public ExprAST {
    T Val;

  public:
    NumberExprAST(double Val)
      : Val(Val) {
    }
  };

  class VariableExprAST : public ExprAST {
    String Name;

  public:
    VariableExprAST(const String& Name)
      : Name(Name) {
    }
  };
};

} // namespace libng