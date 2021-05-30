#include "presenter.hpp"

int main() {
  auto presenter = Presenter::create(0);
  presenter->run();
}
