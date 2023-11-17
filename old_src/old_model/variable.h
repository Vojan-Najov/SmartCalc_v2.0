#ifndef MODEL_VARIABLE_H_
#define MODEL_VARIABLE_H_

namespace s21 {

class Variable final {
 public:
  Variable(void);

  void SetValue(double x);
  void UnsetValue(void);

  int GetValue(double &x) const;

  void SaveValue(void);
  void RestoreValue(void);

 private:
  double value_;
  double saved_value_;
  bool is_defined_;
  bool is_saved_;
};

}  // namespace s21

#endif  // MODEL_VARIABLE_H_
