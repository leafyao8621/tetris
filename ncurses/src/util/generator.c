#include <time.h>
#include "generator.h"
#include "mt19937.h"

struct MT19937 gen;

void generator_initialize(void) {
    mt19937_initialize(&gen, time(0));
}

char generator_generate(void) {
    return (mt19937_gen(&gen) % 7) << 2;
}
