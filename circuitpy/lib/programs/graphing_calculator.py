'''style:{color:red, text_color:black}'''
from tg_gui import gui, system_handler
from tg_gui_extens.artsy import canvas

def scale_position(value,maximum):
    return int(value*20/maximum)

window = system_handler.request_window()
page0 = gui.page()
graph_canvas = canvas(0,0,page0.width,page0.height*0.8,page0)
graph_function = 'x**2'
#wait until canvas is done being made
def draw_graph(source):
    global graph_function
    for x in range(-10,11,1):
        print(x)
        graph_expression = graph_function.replace('x',str(x))
        graph_canvas.draw_pixel(int(graph_canvas.width/2),int(graph_canvas.height/2),gui.red)
        graph_canvas.draw_pixel(scale_position(x,graph_canvas.width),scale_position(eval(graph_expression),graph_canvas.height),gui.red)
graph_canvas.on_place = draw_graph