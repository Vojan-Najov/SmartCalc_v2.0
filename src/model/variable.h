#ifndef MODEL_VARIABLE_H_
#define MODEL_VARIABLE_H_

namespace s21 {

class Variable final {
 public:
  Variable(void);

  void SetValue(double x);
  void UnsetValue(void);

  int GetValue(double &x);

  void SaveValue(void);
  void RestoreValue(void);

 private:
  double value;
  double saved_value;
  bool is_defined;
  bool is_saved;
};

}  // namespace s21

#endif  // MODEL_VARIABLE_H_
