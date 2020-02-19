# The MIT License (MIT)
#
# Copyright (c) 2019 Melissa LeBlanc-Williams for Adafruit Industries LLC
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
"""
`adafruit_st7789`
====================================================

Displayio driver for ST7789 based displays.

* Author(s): Melissa LeBlanc-Williams

Implementation Notes
--------------------

**Hardware:**

* Adafruit 1.54" 240x240 Wide Angle TFT LCD Display with MicroSD:
  https://www.adafruit.com/product/3787

**Software and Dependencies:**

* Adafruit CircuitPython firmware for the supported boards:
  https://github.com/adafruit/circuitpython/releases

"""

import displayio

__version__ = "0.0.0-auto.0"
__repo__ = "https://github.com/adafruit/Adafruit_CircuitPython_ST7789.git"

_INIT_SEQUENCE = (
    b"\x01\x80\x96" # _SWRESET and Delay 150ms
    b"\x11\x80\xFF" # _SLPOUT and Delay 500ms
    b"\x3A\x81\x55\x0A" # _COLMOD and Delay 10ms
    b"\x36\x01\x08" # _MADCTL
    b"\x21\x80\x0A" # _INVON Hack and Delay 10ms
    b"\x13\x80\x0A" # _NORON and Delay 10ms
    b"\x36\x01\xC0" # _MADCTL
    b"\x29\x80\xFF" # _DISPON and Delay 500ms
)

# pylint: disable=too-few-public-methods
class ST7789(displayio.Display):
    """ST7789 driver"""
    def __init__(self, bus, **kwargs):
        super().__init__(bus, _INIT_SEQUENCE, **kwargs)
