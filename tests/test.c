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
#include <assert.h>

int
main(void) {
    ion_t ion[32];

    ion_init(ion, sizeof(ion));
    assert(ion_step(ion, '_') == ION_ERROR);

    ion_init(ion, sizeof(ion));
    assert(ion_step(ion,  ' ') == ION_NONE);
    assert(ion_step(ion, '\t') == ION_NONE);
    assert(ion_step(ion, '\r') == ION_NONE);
    assert(ion_step(ion, '\n') == ION_NONE);

    ion_init(ion, sizeof(ion));
    assert(ion_step(ion, '1') == ION_NONE);
    assert(ion_step(ion, '2') == ION_NONE);
    assert(ion_step(ion, ' ') == ION_NUMBER);

    ion_init(ion, sizeof(ion));
    assert(ion_step(ion, '1') == ION_NONE);
    assert(ion_step(ion, '2') == ION_NONE);
    assert(ion_step(ion, '_') == ION_ERROR);

    return 0;
}

