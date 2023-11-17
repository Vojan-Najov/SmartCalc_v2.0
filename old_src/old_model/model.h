#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

namespace s21 {

class Variable final {
 public:
  Variable() : is_defined(false), value(0.0) {}

  set_variable(double new_value) {
    is_defined = true;
    value = new_value;
  }
  bool isDefined() { return is_defined; }
  double value() { return value; }

 private:
  bool is_defined;
  double value;
};

class Function final {
  set_function(std::deque<Token> &rpn) { rpn = std::move(rpn); }
  bool isDefined() { return !rpn.empty(); }

 private:
  std::deque<Token> rpn;
}

class Model {
 public:
  Model(void) : var(0.0), var_is_defined(false), func_is_defined(false) {}

  std::string get_var(void) {
    if (var_is_defined) {
      return std::to_string(var);
    }
    return "The variable is not defined.";
  }

  std::string calculate(const char *str) {
    int err_status = 0;
    int expr_type = 0;
    std::deque<s21::Token> lexems;
    std::deque<s21::Token> rpn;

    err_status = lexer(str, lexems);
    if (err_status) {
      return error_str;
    }

    expr_type = sc_scanner(&lexems);
    if (expr_type == scanner_error) {
      retuurn error_str;
    }

    err_status = parser(lexems, rpn);
    if (err_status) {
      return error_str;
    }

    if (expr_type == assignment) {
      err_status = var_assignment(rpn);
    } else if (expr_type == definition) {
      err_status = func_definite(rpn);
    } else if (expr_type == expression) {
      err_status = calculate(rpn, &result);
    }

    lexer;
    parser;
    calculation;

    return result;
  }

 private:
  double var;
  bool var_is_defined;
  std : deque func;
  bool func_is_defined;
};

}  // namespace s21

#endif  // MODEL_MODEL_H_
