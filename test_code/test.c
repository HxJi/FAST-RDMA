#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>


#define NUM_PAGES       (1 << 15)
#define BYTE_PER_PAGE   4096

#define RAND    0
#define INC     1
#define ALL_ONE 2

char* page_list[NUM_PAGES];

void malloc_pages(char** page_ptr_arr, int num_pages) {
        int i;
        for (i = 0; i < num_pages; i++) {
                page_ptr_arr[i] = malloc(BYTE_PER_PAGE);
        }
        printf("malloced %d pages, total size: %d KB\n", NUM_PAGES, (NUM_PAGES * BYTE_PER_PAGE) >> 10);
}

void fill_page(char* page, int type) {
        int i;
        for (i = 0; i < BYTE_PER_PAGE; i++) {
                switch (type) {
                        case RAND:
                                page[i] = (char)(rand() & 0xFF);
                                break;
                        case INC:
                                page[i] = (char)i;
                                break;
                        case ALL_ONE:
                                page[i] = 0xFF;
                                break;
                }
        }
}

void fill_pages(char** page_ptr_arr, int num_pages) {
        int i;
        for (i = 0; i < num_pages; i++) {
                fill_page(page_ptr_arr[i], i % 3);
        }
        printf("filled %d pages\n", NUM_PAGES);
}

void update_pages(char** page_ptr_arr, int num_pages, int iter, int usec) {
        int i, j, cnt;
        cnt = 0;
        for (j = 0; j < iter; j++) {
                for (i = 0; i < num_pages; i++) {
                        fill_page(page_ptr_arr[i], i % 3);
                        cnt++;
                        if (cnt % 1000 == 0) {
                                printf("=== updated %d pages === \n", cnt);
                        }
                        usleep(usec);
                }
        }
}


void free_pages(char** page_ptr_arr, int num_pages) {
        int i;
        for (i = 0; i < num_pages; i++) {
                free(page_ptr_arr[i]);
        }
        printf("freed %d pages, total size: %d KB\n", NUM_PAGES, (NUM_PAGES * BYTE_PER_PAGE) >> 10);
}

int main() {
        srand(time(NULL));
        malloc_pages(page_list, NUM_PAGES);

        fill_pages(page_list, NUM_PAGES);

        update_pages(page_list, NUM_PAGES, 50, 100);

        free_pages(page_list, NUM_PAGES);
        return 0;
}
