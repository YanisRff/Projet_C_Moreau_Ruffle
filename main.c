#include <stdlib.h>
#include <stdio.h>

#include "fir.h"
#include "iir.h"
#include "tests/autotests.h"
#include "mesure.h"

int main (int argc, char** argv) {
  testBlocAffichage();
  testBlocMesure();

  return 0;
}

