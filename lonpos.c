#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>

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

#define PIECE_TYPES (12)

double get_current_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return ((double)tv.tv_sec) + (((double)tv.tv_usec) / 1000000);
}

struct move_t {
    int piece_id;
    int offset;
};

struct solver_t {
    uint64_t attempts;
    uint64_t used_piece_types;
    struct move_t moves[PIECE_TYPES];
    int move_count;
    uint64_t occupied;
    int solutions_found;
    double start_time;
};

void solver_init(struct solver_t *solver) {
    solver->attempts = 0;
    solver->used_piece_types = 0;
    solver->occupied = 0;
    solver->solutions_found = 0;
    solver->move_count = 0;
    solver->start_time = get_current_time();
}

void solver_print_solution(const struct solver_t * solver) {
    int piece_types[WIDTH * HEIGHT];
    for (int i=0; i<WIDTH * HEIGHT; i++) {
        piece_types[i] = -1;
    }

    for (int i=0; i<solver->move_count;i++) {
        const struct move_t *move = solver->moves + i;
        const struct piece_t *piece = PIECES + move->piece_id;
        int piece_type = piece->type;
        int first_piece_used_cell = __builtin_ctzll(piece->mask);

        for (int j=0; j<WIDTH*HEIGHT; j++) {
            if (piece->mask & (1ull << j)) {
                piece_types[move->offset + j - first_piece_used_cell] = piece_type;
            }
        }
    }

    printf("+-----------------------+\n");
    for (int y = 0; y < HEIGHT; y++) {
        printf("| ");
        for (int x = 0; x < WIDTH; x++) {
            int piece_type = piece_types[(HEIGHT * x) + y];
            if (piece_type == -1) {
                printf("  ");
            } else {
                printf("%c ", 'A' + piece_type);
            }
        }
        printf("|\n");
    }
    printf("+-----------------------+\n\n");
}


void solver_print_stats(const struct solver_t *solver) {
    double seconds = get_current_time() - solver->start_time;
    double speed = ((double)solver->attempts) / seconds;

    fprintf(
        stderr,
        "%12ld attempts"
        " | %7.4f sec"
        " | %8.0f attempts / sec"
        " | %3d solutions found\n",
        solver->attempts,
        seconds,
        speed,
        solver->solutions_found
    );
}

void solver_solve(struct solver_t *solver) {
    solver->attempts++;

    if (solver->move_count == PIECE_TYPES) {
        solver_print_solution(solver);
        solver->solutions_found++;
        return;
    }

    if (solver->attempts % 5000000 == 0) {
        solver_print_stats(solver);
    }

    int first_empty_cell = __builtin_ctzll(~solver->occupied);
    int first_empty_x = first_empty_cell / HEIGHT;
    int first_empty_y = first_empty_cell % HEIGHT;

    for (int piece_id = 0; piece_id < NUM_PIECES; piece_id++) {
        const struct piece_t* piece = PIECES + piece_id;

        // consider adding this to table
        uint64_t piece_type_mask = 1ull << piece->type;

        if (solver->used_piece_types & piece_type_mask) {
            // piece type is already used
            continue;
        }

        int first_piece_used_cell = __builtin_ctzll(piece->mask);

        if (
            (first_empty_y - first_piece_used_cell + piece->height > HEIGHT)
            || (first_empty_y - first_piece_used_cell < 0)
            || (piece->width + first_empty_x > WIDTH)
        ) {
            // piece falls outside board
            continue;
        }

        uint64_t occupy_mask = (piece->mask >> first_piece_used_cell) << first_empty_cell;

        if (occupy_mask & solver->occupied) {
            // piece would overlap with other piece
            continue;
        }

        solver->moves[solver->move_count] = (struct move_t){
            .piece_id = piece_id,
            .offset = first_empty_cell
        };

        solver->occupied |= occupy_mask;
        solver->used_piece_types |= piece_type_mask;
        solver->move_count++;

        solver_solve(solver);

        solver->move_count--;
        solver->used_piece_types &= (~piece_type_mask);
        solver->occupied &= (~occupy_mask);
    }
}

int main() {
    struct solver_t solver;
    solver_init(&solver);
    solver_solve(&solver);
    solver_print_stats(&solver);
    return 0;
}
