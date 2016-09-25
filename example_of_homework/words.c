#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *generate_word() {
    static const char *uniq_words[] = {
        "go",
        "good",
        "great",
        "had",
        "has",
        "have",
        "he",
        "help",
        "her",
        "here",
        "him",
        "his"
    };
    const size_t uniq_words_n = sizeof(uniq_words) / sizeof(uniq_words[0]);
    return uniq_words[rand() % uniq_words_n];
}

const char *generate_data_with_words(uint32_t needed_words_n) {
    assert(needed_words_n);

    char *data = NULL;
    size_t data_len = 0; // not including terminating zero
    for (uint32_t i = 0; i < needed_words_n; ++i) {
        const char *next_word = generate_word();
        assert(next_word);
        size_t cur_data_pos = data_len;

        // Increase size of allocated memory in 'data' for storing 'next_word' and space
        data_len += strlen(next_word) + 1 /* for space after it */;
        char *new_data = realloc(data, data_len + 1 /* for terminating zero */);
        if (!new_data) {
            free(data); // realloc doesn't free it in case of fail
            printf("Can't realloc %zu bytes: %s\n", data_len + 1, strerror(errno));
            return NULL;
        }
        data = new_data;

        // Print word, space and terminating zero to data
        sprintf(&data[cur_data_pos], "%s ", next_word);
    }

    return data;
}

static bool is_word_separator(char c) {
    return isspace(c) || ispunct(c);
}

const char *get_the_longest_word(const char *data) {
    size_t max_word_len = 0;
    const char *max_word_begin = NULL;

    while (data[0]) {
        const char *cur_word_begin = data;
        // find end of word
        while (data[0] && !is_word_separator(data[0]))
            ++data;

        size_t cur_word_len = data - cur_word_begin;
        if (cur_word_len > max_word_len) {
            max_word_begin = cur_word_begin;
            max_word_len = cur_word_len;
        }

        // skip all word separators after word
        while (data[0] && is_word_separator(data[0]))
            ++data;
    }

    if (!max_word_begin)
        return NULL;

    assert(max_word_len);
    return strndup(max_word_begin, max_word_len); // do a malloc-ed copy of word to make zero-terminated
}
