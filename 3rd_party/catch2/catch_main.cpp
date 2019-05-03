#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


// Taken from https://stackoverflow.com/a/77336/4447365
void handler(int sig) {
  void *array[100];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 100);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

int main( int argc, char* argv[] ) {
  signal(SIGSEGV, handler);
  signal(SIGTERM, handler);

  int result = Catch::Session().run( argc, argv );

  return result;
}
