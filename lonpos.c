#include <stdio.h>
#include <stdint.h>

#define WIDTH (11)
#define HEIGHT (5)

#define MAX_ASYMMETRY_COUNT (8)

// Board layout

// +----------------------------------+
// |  0  5 10 15 20 25 30 35 40 45 50 |
// |  1  6 11 16 21 26 31 36 41 46 51 |
// |  2  7 12 17 22 27 32 37 42 47 52 |
// |  3  8 13 18 23 28 33 38 43 48 53 |
// |  4  9 14 19 24 29 34 39 44 49 54 |
// +----------------------------------+

struct piece_t {
    uint64_t mask;
    int type;
    int width;
    int height;
};

#define NUM_PIECES (60)

const struct piece_t PIECES[NUM_PIECES] = {
    {0x423, 0, 3, 2},
    {0xc21, 0, 3, 2},
    {0x843, 0, 3, 2},
    {0xc42, 0, 3, 2},
    {0x27, 0, 2, 3},
    {0x87, 0, 2, 3},
    {0xe1, 0, 2, 3},
    {0xe4, 0, 2, 3},
    {0x463, 1, 3, 2},
    {0x863, 1, 3, 2},
    {0x67, 1, 2, 3},
    {0xe3, 1, 2, 3},
    {0xc7, 1, 2, 3},
    {0xe6, 1, 2, 3},
    {0xc61, 1, 3, 2},
    {0xc62, 1, 3, 2},
    {0x8423, 2, 4, 2},
    {0x18421, 2, 4, 2},
    {0x10843, 2, 4, 2},
    {0x18842, 2, 4, 2},
    {0x2f, 2, 2, 4},
    {0x10f, 2, 2, 4},
    {0x1e1, 2, 2, 4},
    {0x1e8, 2, 2, 4},
    {0x8461, 3, 4, 2},
    {0x8c21, 3, 4, 2},
    {0x10862, 3, 4, 2},
    {0x10c42, 3, 4, 2},
    {0x4f, 3, 2, 4},
    {0x8f, 3, 2, 4},
    {0x1e2, 3, 2, 4},
    {0x1e4, 3, 2, 4},
    {0x10c21, 4, 4, 2},
    {0x10861, 4, 4, 2},
    {0x8462, 4, 4, 2},
    {0x8c42, 4, 4, 2},
    {0x1c3, 4, 2, 4},
    {0x187, 4, 2, 4},
    {0x6e, 4, 2, 4},
    {0xec, 4, 2, 4},
    {0x23, 5, 2, 2},
    {0x61, 5, 2, 2},
    {0x43, 5, 2, 2},
    {0x62, 5, 2, 2},
    {0x1c21, 6, 3, 3},
    {0x427, 6, 3, 3},
    {0x1087, 6, 3, 3},
    {0x1c84, 6, 3, 3},
    {0x10c3, 7, 3, 3},
    {0x1861, 7, 3, 3},
    {0x466, 7, 3, 3},
    {0xcc4, 7, 3, 3},
    {0xa7, 8, 2, 3},
    {0xe5, 8, 2, 3},
    {0xc23, 8, 3, 2},
    {0xc43, 8, 3, 2},
    {0x8421, 9, 4, 1},
    {0xf, 9, 1, 4},
    {0x63, 10, 2, 2},
    {0x8e2, 11, 3, 3},
};

void piece_show(const struct piece_t *piece) {
    char c = 'A' + piece->type;
    printf("+-----------------------+\n");
    for (int y = 0; y < HEIGHT; y++) {
        printf("| ");
        for (int x = 0; x < WIDTH; x++) {
            uint64_t cell_bit = 1ull << ((HEIGHT * x) + y);
            if (piece->mask & cell_bit) {
                printf("%c ", c);
            } else {
                printf("  ");
            }
        }
        printf("|\n");
    }
    printf("+-----------------------+\n");
    printf("Height: %d\n", piece->height);
    printf(" Width: %d\n", piece->width);
}

int main() {
    for (int i = 0; i < NUM_PIECES; i++) {
        piece_show(&PIECES[i]);
        printf("\n");
    }

    return 0;
}
