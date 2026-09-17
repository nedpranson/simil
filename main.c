#include <stdio.h>

#include "base.h"

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

// [5x3]
//
// 0 0 1
// 1 1 1
// 0 0 0
// 0 1 0
// 0 1 0

// h = 5+3-1=7

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

// O(n^2) time, O(1) space
// using binary search it should be possible to acheive O(nlogn)
size_t lcsubstr(string_view a, string_view b, size_t* ai, size_t* bi) {
    size_t count = 0;

    *ai = 0;
    *bi = 0;

    if (a.len > 0 && b.len > 0) {
        size_t rows = a.len;
        size_t cols = b.len;

        size_t height = rows + cols - 1;
        for (size_t h = 0; h < height; h++) {
            size_t j = SUB_SAT(cols - 1, h);
            size_t i = SUB_SAT(h, cols - 1);

            size_t w = MIN(rows, MIN(h + 1, height - h));
            size_t n = 0;

            if (count >= w) {
                continue;
            }

            for (; w > 0; w--) {
                if (b.ptr[j++] != a.ptr[i++]) {
                    n = 0;
                    if (count >= w - 1)
                        break;
                } else if (++n > count ) {
                    count = n;
                    *ai = i - count;
                    *bi = j - count;
                }
            }
        }
    }

    return count;
}

size_t gcsubstr(string_view a, string_view b) {
    size_t ai;
    size_t bi;

    size_t len = lcsubstr(a, b, &ai, &bi);
    if (len == 0) {
        return 0;
    }

    size_t n = len;

    n += gcsubstr(sv_slice(a, 0, ai), sv_slice(b, 0, bi));
    n += gcsubstr(sv_slice(a, ai + len, a.len), sv_slice(b, bi + len, b.len));

    return n;
}

int main(/** int argc, char** argv **/) {
    string_view str1 = sv("GESTALT PATTERN MATCHING\n");
    string_view str2 = sv("GESTALT PRACTICE\n");

    size_t n = gcsubstr(str1, str2);
    float dice = (float)(2 * n) / (float)(str1.len + str2.len);

    printf("%.2f\n", dice * 100);
    return 0;
}
