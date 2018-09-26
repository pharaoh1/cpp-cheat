#include "common.h"

int main(void) {
    int i, ret;
    struct stat s;
    char fname[] = __FILE__ TMPFILE_EXT;

    /* Do it twice, so that on second time, we are sure it exists,
     * to exercise every possible state. */
    for (i = 0; i < 2; ++i) {
        /* Remove the directory if it exists. */
        ret = stat(fname, &s);
        if (ret == 0) {
            /* ENOENT happens when it exists, other errors are unexpected. */
            assert(errno == ENOENT);
            assert(rmdir(fname) == 0);
        }

        /* Make the dir and check for error. */
        if(mkdir(fname, 0777) == -1)
            assert(false);
    }

    return EXIT_SUCCESS;
}
