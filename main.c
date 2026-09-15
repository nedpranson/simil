#include <stdio.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define SUB_SAT(a, b) ((a) > (b) ? (a) - (b) : 0)

// [ ][L][a][b][a][s][,][ ][P][a][s][a][u][l][i][?]
// [P] 0  0  0  0  0  0  0  1  0  0  0  0  0  0  0
// [a] 0  1  0  1  0  0  0  0  1  0  1  0  0  0  0
// [s] 0  0  0  0  1  0  0  0  0  1  0  0  0  0  0
// [a] 0  1  0  1  0  0  0  0  1  0  1  0  0  0  0
// [u] 0  0  0  0  0  0  0  0  0  0  0  1  0  0  0
// [l] 0  0  0  0  0  0  0  0  0  0  0  0  1  0  0
// [i] 0  0  0  0  0  0  0  0  0  0  0  0  0  1  0
// [,] 0  0  0  0  0  1  0  0  0  0  0  0  0  0  0
// [ ] 0  0  0  0  0  0  1  0  0  0  0  0  0  0  0
// [L] 1  0  0  0  0  0  0  0  0  0  0  0  0  0  0
// [a] 0  1  0  1  0  0  0  0  1  0  1  0  0  0  0
// [b] 0  0  1  0  0  0  0  0  0  0  0  0  0  0  0
// [a] 0  1  0  1  0  0  0  0  1  0  1  0  0  0  0
// [s] 0  0  0  0  1  0  0  0  0  1  0  0  0  0  0
// [?] 0  0  0  0  0  0  0  0  0  0  0  0  0  0  1

// 1 1 1
// 0 0 0
// 0 1 0
// 0 1 0

// [3x4], len = 3+4-1=6

//     1       0      1
//   1 0       1      2
// 1 0 0       2      3
// 0 1 0       3      3
// 0 1         4      2
// 0           5      1
//

// [3x5], len = 3+5-1=7

//     1       0      1
//   0 1       1      2 
// 0 1 0       2      3
// 1 0 0       3      3
// 0 1 0       4      3
// 0 1         5      2
// 0           6      1

//             [0,2]
//       [0,1] [1,2]
// [0,0] [1,1] [2,2]
// [1,0] [2,1] [3,2]
// [2,0] [3,1] [4,2]
// [3,0] [4,1]
// [4,0]

int main() {
    const char* str1 = "Labas, Pasauli?";
    const char* str2 = "Pasauli, Labas?";

    size_t substr = 0;

    size_t rows = strlen(str1);
    size_t cols = strlen(str2);

    size_t height = rows + cols - 1;

    // O(n^2) time, O(1) space
    for (size_t h = 0; h < height; h++) {
        size_t j = SUB_SAT(cols - 1, h);
        size_t i = SUB_SAT(h, cols - 1);

        size_t w = MIN(rows, MIN(h + 1, height - h));
        size_t c = 0;

        // todo: skip diags with len smaller then current substr
        for (; w > 0; w--) {
            c += (str2[j++] == str1[i++]);
        }

        substr = MAX(substr, c);
    }

    printf("%ld\n", substr);
    return 0;
}
