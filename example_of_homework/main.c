#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "words.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s number_of_words_to_generate\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n_words_to_generate = atoi(argv[1]);
    if (n_words_to_generate <= 0) {
        printf("Usage: %s number_of_words_to_generate\nnumber_of_words_to_generate must be > 0\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source_data = generate_data_with_words(n_words_to_generate);
    if (!source_data) {
        printf("Can't generate data\n");
        return EXIT_FAILURE;
    }

    const char *the_longest_word = get_the_longest_word(source_data);
    if (!the_longest_word) {
        free((void *)source_data); // XXX: don't forget it to prevent leak
        printf("Can't get the longest word\n");
        return EXIT_FAILURE;
    }

    printf("Generated data: '%s'\n", source_data);
    printf("The longest word in generated data is '%s'\n", the_longest_word);

    free((void *)source_data);
    free((void *)the_longest_word);
    return EXIT_SUCCESS;
}
