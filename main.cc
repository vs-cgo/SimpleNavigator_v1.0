#include <clocale>

#include "./view/view.h"

int main() {
  setlocale(LC_NUMERIC, "en_US.UTF-8");
  s21::View v;
  v.Show();

  return 0;
}
