# The MIT License (MIT)
#
# Copyright (c) 2019 Jonah Yolles-Murphy
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

from tg_gui import gui

class refreshable_value_bar(gui.refreshable_widget):

    def __init__(self, x, y, width, height, superior, refresher, min_val, max_val, color = None, border = None):
        if color == None:
            color = gui.white
        if border == None:
            border = gui.good_gap_size
        self.min_val = min_val
        self.max_val = max_val
        self.border = border
        self.color = color
        super().__init__(x, y, width, height, superior, refresher)

    def place(self):
        super().place()
        gui.round_rect(self.physical_x, self.physical_y, self.width, self.height, 0, self.color)
        gui.round_rect(self.physical_x + self.border, self.physical_y + self.border,
                         self.width - self.border*2, self.height - self.border*2, 0, gui.default_background_color)
        self.refresh()

    def refresh(self):
        data = min(max(self.refresher(self), self.min_val), self.max_val)
        val_len = int(((data-self.min_val)/(self.max_val -self.min_val)) * (self.width - gui.good_gap_size*4))
        gui.round_rect(self.physical_x + self.border*2, self.physical_y + self.border*2,
                         val_len, self.height - self.border*4, 0, self.color)
        gui.round_rect(self.physical_x + self.border*2 + val_len, self.physical_y + self.border*2,
                         self.width - self.border*4 - val_len, self.height - self.border*4, 0, gui.default_background_color)
