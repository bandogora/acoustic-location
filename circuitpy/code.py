import busio, board, time, gc

import boardutil as bt
#import board2
#import team5

import board
import neopixel


def correct(t1, t2, t3, t4):

    if t3 < 10 and t4 >= 10 and t2 >=10:
        #33.75 tick delay to account for 135 uSec delay
        t4 += 34
        t2 += 34
        t1 += 34
    elif t4 < 10 and t3 >= 10 and t1 >=10:
        t3 += 34
        t2 += 34
        t1 += 34
    elif t1 < 10 and t3 >= 10 and t2 >=10:
        t3 += 34
        t2 += 34
        t4 += 34
    elif t3 < 10 and t4 < 10 and t1 > 100 and t2 > 100:
        t2 += 70
        t1 += 70
    elif t1 < 10 and t3 < 10 and t4 > 100 and t2 > 100:
        t4 += 70
        t2 += 70
    elif t1 < 10 and t2 < 10 and t3 > 100 and t4 > 100:
        t3 += 70
        t4 += 70
    return t1, t2, t3, t4


# Configure the setup
PIXEL_PIN = board.D13   # pin that the NeoPixel is connected to
pixels = neopixel.NeoPixel(PIXEL_PIN, 25, pixel_order=neopixel.RGB)


usart = busio.UART(board.TX, board.RX, baudrate=9600, timeout=.1,  parity=busio.UART.Parity.ODD)

brd = bt.newboard(240, 6, 6)

cnt = 0
buf = ''
while True:
    try:
            gc.collect()

            data = usart.readline()

            if data is None:
                continue

            else:
                buf += (str(data)[2:-5])


            if buf.endswith('+'):

                try:
                    tup = [int(d) for d in buf[0:-1].split('-')]#correct(*)
                except:
                    buf = ''
                    print(buf[0:-1].split('-'))

                buf = ''

                pt = bt.point_compare(brd, *tup)
                if pt is not None:
                    pt = list(pt)

                    if pt[0] < 1:
                        pt[0] = 1
                    if pt[0] > 4:
                        pt[0] = 4
                    if pt[-1] < 1:
                        pt[-1] = 1
                    if pt[-1] > 4:
                        pt[-1] = 4

                    print('coord', cnt, pt)
                    cnt += 1

                    #neo stuff
                    x, y = pt
                    x, y = x-1, y-1
                    pixels.fill((0,0,0))

                    if y % 2:

                        pixels[(y+1)*5 - x -1 ] = (100, 50, 150)

                    else:

                        pixels[5*y + x - 1] = (100, 50, 150)



    except Exception as e:
        buf = ''
        print(e)