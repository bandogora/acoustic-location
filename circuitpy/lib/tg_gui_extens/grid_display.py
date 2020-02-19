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

class grid(gui.refreshable_widget):
    """A refreshable widget for 2d arrays of data.
    It will auto scale to the shortest row and col.
    The 'refresher' input (function) shoudl return
    the most recent 2d list of lists. the input
    array should be in [x][y] reference.
    """
    def __init__(self, x, y, width, superior, refresher, color_mask = (1, 0, 0), background = None, filter_factor = 2):
        self._last_num_sides = 0
        self.color_mask = color_mask
        self.filter_factor = filter_factor
        if background == None:
            background = gui.default_background_color
        self.background = background
        self.max_val = None
        self.min_val = None
        print(self.max_val, self.min_val)
        super().__init__(x, y, width, width, superior, refresher)


    def place(self):
        super().place()
        self._prev_data = [[1701]*len(x) for x in self.refresher(self)]
        self.refresh(force = True)

    def refresh(self, force = False):
        if self._active:
            data = self.refresher(self)

            #find the shortest dimension
            num_sides = 50000
            shortest_col = None
            for col in data:
               if len(col) < num_sides:
                   shortest_col = col
                   num_sides = len(col)
                   num_sides = min(num_sides, len(data))

            #sizing calcs
            pixel_width = self.width // num_sides

            #find color scaling
            max_val = -6.022*10**23
            min_val =  6.022*10**23
            for x in range(num_sides):
                for y in range(num_sides):
                    max_val = max(max_val, data[x][y])
                    min_val = min(min_val, data[x][y])

            self.max_val = max_val
            self.min_val = min_val

            #clear if different to prevent artifacts
            if not num_sides == self._last_num_sides:
                gui.round_rect(self.physical_x, self.physical_y, self.width, self.height, 0, self.background)
                self._last_num_sides = num_sides

            if self._active:
                for x in range(num_sides):
                    for y in range(num_sides):
                        val = ((data[x][y]-min_val)**self.filter_factor)/((max_val-min_val)**self.filter_factor)
                        color = int(gui.color_max*(1-val)/10)*10
                        if  force or self._prev_data[x][y] != color:
                            gui.round_rect(self.physical_x + pixel_width*x, self.physical_y + pixel_width*y,
                                            pixel_width, pixel_width, 0,
                                            gui.color((color, gui.color_max)[self.color_mask[0]],
                                                        (color, gui.color_max)[self.color_mask[1]],
                                                        (color, gui.color_max)[self.color_mask[2]]))
                            self._prev_data[x][y] = color