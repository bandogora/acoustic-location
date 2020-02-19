from math import *
precalced_points = None
board_len = None



def newboard(side_length = 41, num_tiles_per_side = 5, resolution = 10):
    if not isinstance(resolution, int) and (resolution < 1):
        raise ValueError('resolution bust a whole number and not 0')
    if not isinstance(num_tiles_per_side, int) and (num_tiles_per_side < 1):
        raise ValueError('num_tiles_per_side bust a whole number and not 0')

    #global precalced_points, board_len
    board_len = side_length
    precalced_points = {}

    tile_width = side_length/num_tiles_per_side
    subtile_width = tile_width/resolution

    for tile_x in range(num_tiles_per_side):
        for tile_y in range(num_tiles_per_side):
            precalced_points[(tile_x, tile_y)] = []
            for x_subtile_offset in range(resolution):
                for y_subtile_offset in range(resolution):

                    #
                    phys_x = tile_x*tile_width + (x_subtile_offset+.5)*subtile_width
                    phys_y = tile_y*tile_width + (y_subtile_offset+.5)*subtile_width

                    #list of strut legths in abcd order (counter clockwise)
                    #   see picture of drawing
                    strut_lengths = [
                    sqrt( (phys_x)**2 + (phys_y)**2), #a_strut_len
                    sqrt( (side_length - phys_x)**2 + (phys_y)**2), #b_strut_len
                    sqrt( (side_length - phys_x)**2 + (side_length - phys_y)**2), #c_strut_len
                    sqrt( (phys_x)**2 + (side_length - phys_y)**2) #d_strut_len
                    ]

                    shortest = min(*strut_lengths)
                    # this is list comprehension, edit into forloop for final code
                    #    because it is an advanced user feasture, subtracting
                    #    the shortest length from all the items in the list
                    strut_lengths = [length - shortest for length in strut_lengths]

                    precalced_points[(tile_x, tile_y)].append(strut_lengths)


    return precalced_points, board_len

def point_compare(board, a_strut, b_strut, c_strut, d_strut):
    struts = (a_strut, b_strut, c_strut, d_strut)

    #global precalced_points, board_len
    precalced_points, board_len = board


    best_point = None
    best_diff =  board_len**2

    for point, phys_struts_list in precalced_points.items():
        #print(point)
        for phys_struts in phys_struts_list:
            diff = 0

            for calced_strut_len, strut_len in zip(phys_struts, struts):
                diff += sqrt(abs(strut_len**2 - calced_strut_len**2 ))#
                diff += abs(calced_strut_len - strut_len)
                #print('      ',(calced_strut_len - strut_len), '=', calced_strut_len , '-', strut_len)
            #print('   ', diff, 'vs', best_diff)

            if abs(diff) < abs(best_diff):
                best_diff = diff
                best_point = point

    return best_point