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

#ifndef ION_H_
#define ION_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum ion_result {
    ION_NONE,
    ION_ERROR,
    ION_NUMBER,
    ION_QUOTE
};

typedef char ion_char_t;
typedef unsigned char ion_size_t;
typedef unsigned char ion_result_t;
typedef ion_char_t ion_t;

extern void
ion_init(ion_t *ion, ion_size_t size);

extern ion_result_t
ion_step(ion_t *ion, ion_char_t value);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ION_H_ */
