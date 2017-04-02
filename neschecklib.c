#include <stdio.h>
#include <stdlib.h>

extern unsigned int TOS_NODE_ID;
unsigned long checksexecuted = 0;

// #define IS_DEBUGGING 1

struct metadata_table_entry {
    long ptr;
    long size;
};

long metadatatablecount = 0;
struct metadata_table_entry** metadatatable = NULL;

struct metadata_table_entry* findMetadataTableEntry(long p) {
    struct metadata_table_entry* entry = NULL;
    int i;

    // printf("Lookup for %p\n", p);
    for (i = 0; i < metadatatablecount; i++) {
        // printf("\t%p == %p ?\n", (void*)(metadatatable[i]->ptr), (void*)p);
        if (metadatatable[i]->ptr == p) {
            entry = metadatatable[i];
            break;
        }
    }
    return entry;
}
void setMetadataTableEntry(long p, long size, long addr) {
    struct metadata_table_entry* entry = findMetadataTableEntry(p);
    if (entry == NULL) { // not found, create it
        // printf("\tNot found %p\n", (void*)p);
#ifdef IS_DEBUGGING
            // printf("[%p] Creating entry for %p, size = %ld\n", (void*)addr, (void*)p, size);
            printf("[%p,%p,%ld]\n", (void*)addr, (void*)p, size);
#endif
        entry = malloc(sizeof(struct metadata_table_entry));
        entry->ptr = p;
        entry->size = size;
        metadatatablecount++;
        metadatatable = realloc(metadatatable, metadatatablecount * sizeof(struct metadata_table_entry *));
        metadatatable[metadatatablecount - 1] = entry;
    }

    entry->size = size;
}
long lookupMetadataTableEntry(long p) {
    struct metadata_table_entry* entry = findMetadataTableEntry(p);
    if (entry == NULL) {
        // printf("\tNot found %p\n", (void*)p);
        return 0;
    } else {
        // printf("\tFound %p, size = %ld\n", (void*)p, entry->size);
        return entry->size;
    }
}

void printErrorLine(long l) {
    printf("Memory error near line %ld.\n", l);
}
void printCheck(/*long l, long r*/) {
#ifdef IS_DEBUGGING
    // disable this or the output will be GigaBytes big for real programs!
    // if (l < r) printf("%ld <= %ld ?\n", r, l);
    printf("?");
#endif
}
void printFaultInjectionExecuted(long l) {
    printf("Executing injected fault at line %ld.\n", l);
}
