#include <stdlib.h>
#include <stdio.h>
#include "fir.h"
#include "tests/autotests.h"

int main (int argc, char** argv) {
  testBlocFIR();
  firTest("../log/log1/log1.dat");
  return 0;
}

