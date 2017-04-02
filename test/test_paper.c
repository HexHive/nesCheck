#include <stdio.h>
#include <stdlib.h>

typedef struct foo {
    int a;
    int *bar;
} foo_t;

foo_t myfoo;

foo_t* testMT_aux(int* p) {
    foo_t* blurb = &myfoo;
    blurb->bar = p;
    return blurb;
}
void testMetadataTable(int* p) {
    foo_t* bla = testMT_aux(p);
    (bla->bar)[2] = 13;
}

void assignLoop(int* c) {
    int i;
    for (i = 0; i < 4; i++)
        *(c + i) = i;
}

void testDynamicAliasing(int c) {
    int* a;
    int foo[4];
    int bar[12];

    if (c < 1) a = foo;
    else       a = bar;

    assignLoop(&(a[1]));
}

int main() {
    int* myarray = malloc(5 * sizeof(int));
    testMetadataTable(myarray);
    testDynamicAliasing(0);
}
