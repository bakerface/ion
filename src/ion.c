/*
 * Copyright (c) 2014 Christopher M. Baker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#include <ion.h>

#define ion_private(ion) ((ion_private_t *) ion)

#define WHITESPACE  \
          ' ':      \
    case '\t':      \
    case '\r':      \
    case '\n'

#define DIGIT   \
         '0':   \
    case '1':   \
    case '2':   \
    case '3':   \
    case '4':   \
    case '5':   \
    case '6':   \
    case '7':   \
    case '8':   \
    case '9'

enum ion_state {
    ION_STATE_START,
    ION_STATE_NUMBER,
    ION_STATE_QUOTE
};

typedef unsigned char ion_state_t;

typedef struct ion_header {
    ion_state_t state;
    ion_size_t size;
} ion_header_t;

typedef struct ion_private {
    ion_header_t header;
    ion_char_t stack[1];
} ion_private_t;

typedef ion_result_t (*ion_function_t)(ion_private_t *ion, ion_char_t value);

static ion_result_t
state_start(ion_private_t *ion, ion_char_t value) {
    ion_result_t result = ION_ERROR;

    switch (value) {
        case WHITESPACE:
            result = ION_NONE;
            break;

        case DIGIT:
            ion->header.state = ION_STATE_NUMBER;
            result = ION_NONE;
            break;

        case '[':
            *ion->stack = 1;
            ion->header.state = ION_STATE_QUOTE;
            result = ION_NONE;
            break;

        default:
            break;
    }

    return result;
}

static ion_result_t
state_number(ion_private_t *ion, ion_char_t value) {
    ion_result_t result = ION_ERROR;

    switch (value) {
        case WHITESPACE:
            ion->header.state = ION_STATE_START;
            result = ION_NUMBER;
            break;

        case DIGIT:
            result = ION_NONE;
            break;

        default:
            break;
    }

    return result;
}

static ion_result_t
state_quote(ion_private_t *ion, ion_char_t value) {
    ion_result_t result = ION_ERROR;

    if (value == ']' && --(*ion->stack) == 0) {
        ion->header.state = ION_STATE_START;
        result = ION_QUOTE;
    }
    else if (value == '[') {
        (*ion->stack)++;
        result = ION_NONE;
    }
    else {
        result = ION_NONE;
    }

    return result;
}

void
ion_init(ion_t *ion, ion_size_t size) {
    ion_private_t *private = ion_private(ion);
    private->header.state = ION_STATE_START;
    private->header.size = (ion_size_t) (size - sizeof(ion_header_t));
}

static const ion_function_t state_machine[] = {
    state_start,
    state_number,
    state_quote
};

ion_result_t
ion_step(ion_t *ion, ion_char_t value) {
    ion_private_t *private = ion_private(ion);
    return state_machine[private->header.state](private, value);
}

