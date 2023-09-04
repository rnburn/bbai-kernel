#include "bbai/base/error/panic.h"

#include <string>

int main(int argc, char* argv[]) {
  switch(argc) {
    case 1:
      bbai::panic(std::string{"abc"} + std::string{"123"});
    case 2:
      bbai::panic("{}", argv[1]);
    case 3:
      bbai::panic("{} -- {}", argv[1], argv[2]);
    default:
      bbai::panic("no no");
  }
  return 0;
}
