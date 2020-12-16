from tkinter import *
import os

root = Tk()
root.title('ExprEval Calculator')
root.resizable(0, 0)

icon = PhotoImage(file='icons8-pi-96.png')
root.iconphoto(False, icon)

frame_main = Frame(root)
frame_main.pack()

entry_input = None
operation_history = []


def button_clicked(token):
    global entry_input
    entry_input.insert(END, token)

def clear():
    global entry_input
    entry_input.delete(0, END)

def delete():
    global entry_input
    entry_input.delete(len(entry_input.get())-1)

def evaluate():
    global entry_input
    global operation_history

    expression = entry_input.get()
    if len(expression) > 0:
        entry_input.delete(0, END)
        os.system(f'(echo "{expression}" | ./main) > tmp.txt')
        with open('tmp.txt', 'r') as f:
            line = f.readline()
            result = ''
            if len(line):
                result = line[3:-1]
            entry_input.insert(0, result)
            operation_history.append(expression + ' = ' + result)
        f.close()

def _add_operator(symbol, arguments, expression):
    args = arguments.split(' ')
    print(symbol)
    print(args)
    print(expression)

def _remove_operator(symbol):
    print(symbol)

def add_operator():
    global root
    win = Toplevel(root)
    win.title('Add a new function')

    Label(win, text='Symbol').grid(row=0, column=0)
    Label(win, text='Arguments').grid(row=1, column=0)
    Label(win, text='Expression').grid(row=2, column=0)

    entry_symbol = Entry(win)
    entry_arguments = Entry(win)
    entry_expression = Entry(win)

    Button(win, text='Add', command=lambda: _add_operator(entry_symbol.get(), entry_arguments.get(), entry_expression.get())).grid(row=3, column=0, columnspan=2)

    entry_symbol.grid(row=0, column=1)
    entry_arguments.grid(row=1, column=1)
    entry_expression.grid(row=2, column=1)

def remove_operator():
    global root
    win = Toplevel(root)
    win.title('Delete a function')

    Label(win, text='Symbol').grid(row=0, column=0)
    
    entry_symbol = Entry(win)

    Button(win, text='Remove', command=lambda: _remove_operator(entry_symbol.get()))

def list_operators():
    global root
    win = Toplevel(root)
    win.title('Use a function')

    scrollbar = Scrollbar(win)
    scrollbar.pack(side=RIGHT, fill=Y)

    operator_list = Listbox(win, yscrollcommand=scrollbar.set)
    for i in range(100):
        operator_list.insert(END, 'Hey' + str(i))

    operator_list.pack(side=LEFT, fill=BOTH)
    scrollbar.config(command=operator_list.yview)

def history():
    global root
    global operation_history
    win = Toplevel(root)
    win.title('History')

    scrollbar = Scrollbar(win)
    scrollbar.pack(side=RIGHT, fill=Y)

    unit_list = Listbox(win, yscrollcommand=scrollbar.set)
    for unit in operation_history:
        unit_list.insert(END, unit)

    unit_list.pack(side=LEFT, fill=BOTH)
    scrollbar.config(command=unit_list.yview)


# = = = = = = = = = = = = =
button_dot = Button(frame_main, text='.', command=lambda: button_clicked('.'))
button_0 = Button(frame_main, text='0', command=lambda: button_clicked('0'))
button_1 = Button(frame_main, text='1', command=lambda: button_clicked('1'))
button_2 = Button(frame_main, text='2', command=lambda: button_clicked('2'))
button_3 = Button(frame_main, text='3', command=lambda: button_clicked('3'))
button_4 = Button(frame_main, text='4', command=lambda: button_clicked('4'))
button_5 = Button(frame_main, text='5', command=lambda: button_clicked('5'))
button_6 = Button(frame_main, text='6', command=lambda: button_clicked('6'))
button_7 = Button(frame_main, text='7', command=lambda: button_clicked('7'))
button_8 = Button(frame_main, text='8', command=lambda: button_clicked('8'))
button_9 = Button(frame_main, text='9', command=lambda: button_clicked('9'))

# button_2nd = Button(frame_main, text='2nd', width=3)
button_clear = Button(frame_main, text='Clear', command=lambda: clear(), width=3)
button_delete = Button(frame_main, text='\u2190', command=lambda: delete(), width=3)
button_equal = Button(frame_main, text='=', command=lambda: evaluate())

button_add = Button(frame_main, text='+', command=lambda: button_clicked('+'))
button_subtract = Button(frame_main, text='-', command=lambda: button_clicked('-'))
button_multiply= Button(frame_main, text='*', command=lambda: button_clicked('*'))
button_divide = Button(frame_main, text='/', command=lambda: button_clicked('/'), width=3)
button_pow = Button(frame_main, text='^', command=lambda: button_clicked('^'), width=3)
button_mod = Button(frame_main, text='mod', command=lambda: button_clicked('mod'), width=3)

button_ln = Button(frame_main, text='ln', command=lambda: button_clicked('ln'), width=3)
button_log2 = Button(frame_main, text='log2', command=lambda: button_clicked('log2'), width=3)
button_log10 = Button(frame_main, text='log10', command=lambda: button_clicked('log10'), width=3)

button_sin = Button(frame_main, text='sin', command=lambda: button_clicked('sin'), width=3)
button_cos = Button(frame_main, text='cos', command=lambda: button_clicked('cos'), width=3)
button_tan = Button(frame_main, text='tan', command=lambda: button_clicked('tan'), width=3)
button_sinh = Button(frame_main, text='sinh', command=lambda: button_clicked('sinh'), width=3)
button_cosh = Button(frame_main, text='cosh', command=lambda: button_clicked('cosh'), width=3)
button_tanh = Button(frame_main, text='tanh', command=lambda: button_clicked('tanh'), width=3)
button_asin = Button(frame_main, text='asin', command=lambda: button_clicked('asin'), width=3)
button_acos = Button(frame_main, text='acos', command=lambda: button_clicked('acos'), width=3)
button_atan = Button(frame_main, text='atan', command=lambda: button_clicked('atan'), width=3)
button_asinh = Button(frame_main, text='asinh', command=lambda: button_clicked('asinh'), width=3)
button_acosh = Button(frame_main, text='acosh', command=lambda: button_clicked('acosh'), width=3)
button_atanh = Button(frame_main, text='atanh', command=lambda: button_clicked('atanh'), width=3)

button_round = Button(frame_main, text='round', command=lambda: button_clicked('round'), width=3)
button_ceil = Button(frame_main, text='ceil', command=lambda: button_clicked('ceil'), width=3)
button_floor = Button(frame_main, text='floor', command=lambda: button_clicked('floor'), width=3)
button_gamma = Button(frame_main, text='gamma', command=lambda: button_clicked('gamma'), width=3)
button_rand = Button(frame_main, text='rand', command=lambda: button_clicked('rand'), width=3)

button_pi = Button(frame_main, text='pi', command=lambda: button_clicked('pi'), width=3)
button_e = Button(frame_main, text='e', command=lambda: button_clicked('e'), width=3)

button_paranthesis_open = Button(frame_main, text='(', command=lambda: button_clicked('('), width=3)
button_paranthesis_close = Button(frame_main, text=')', command=lambda: button_clicked(')'), width=3)

is_switched = False

def switch():
    global is_switched

    global button_sin
    global button_cos
    global button_tan
    global button_sinh
    global button_cosh
    global button_tanh

    global button_round
    global button_ceil
    global button_floor
    global button_rand
    global button_mod

    if is_switched:
        button_sin.config(text='sin', command=lambda: button_clicked('sin'))
        button_cos.config(text='cos', command=lambda: button_clicked('cos'))
        button_tan.config(text='tan', command=lambda: button_clicked('tan'))
        button_sinh.config(text='sinh', command=lambda: button_clicked('sinh'))
        button_cosh.config(text='cosh', command=lambda: button_clicked('cosh'))
        button_tanh.config(text='tanh', command=lambda: button_clicked('tanh'))

        button_round.config(text='round', command=lambda: button_clicked('round'))
        button_ceil.config(text='ceil', command=lambda: button_clicked('ceil'))
        button_floor.config(text='floor', command=lambda: button_clicked('floor'))
        button_rand.config(text='rand', command=lambda: button_clicked('rand'))
        button_mod.config(text='mod', command=lambda: button_clicked('mod'))
    else:
        button_sin.config(text='arcsin', command=lambda: button_clicked('arcsin'))
        button_cos.config(text='arccos', command=lambda: button_clicked('arccos'))
        button_tan.config(text='arctan', command=lambda: button_clicked('arctan'))
        button_sinh.config(text='arcsinh', command=lambda: button_clicked('arcsinh'))
        button_cosh.config(text='arccosh', command=lambda: button_clicked('arccosh'))
        button_tanh.config(text='arctanh', command=lambda: button_clicked('arctanh'))

        button_round.config(text='Add', command=lambda: add_operator())
        button_ceil.config(text='Remove', command=lambda: remove_operator())
        button_floor.config(text='Use', command=lambda: list_operators())
        button_rand.config(text='abs', command=lambda: button_clicked('abs'))
        button_mod.config(text='History', command=lambda: history())
    
    is_switched = not is_switched

button_2nd = Button(frame_main, text='2nd', command=lambda: switch(), width=3)

entry_input = Entry(frame_main, width=40)

# = = = = = = = = = = = = =
entry_input.grid(row=0, column=0, columnspan=7)

button_dot.grid(row=4, column=0)
button_0.grid(row=4, column=1)
button_equal.grid(row=4, column=2)

button_1.grid(row=1, column=0)
button_2.grid(row=1, column=1)
button_3.grid(row=1, column=2)
button_4.grid(row=2, column=0)
button_5.grid(row=2, column=1)
button_6.grid(row=2, column=2)
button_7.grid(row=3, column=0)
button_8.grid(row=3, column=1)
button_9.grid(row=3, column=2)

button_clear.grid(row=1, column=3)
button_delete.grid(row=2, column=3)
button_2nd.grid(row=3, column=3)

button_add.grid(row=5, column=0)
button_subtract.grid(row=5, column=1)
button_multiply.grid(row=5, column=2)
button_divide.grid(row=5, column=3)
button_pow.grid(row=4, column=3)

button_paranthesis_open.grid(row=1, column=4)
button_paranthesis_close.grid(row=1, column=5)

button_round.grid(row=2, column=4)
button_ceil.grid(row=2, column=5)
button_floor.grid(row=2, column=6)
button_rand.grid(row=1, column=6)

button_sin.grid(row=3, column=4)
button_cos.grid(row=3, column=5)
button_tan.grid(row=3, column=6)
button_sinh.grid(row=4, column=4)
button_cosh.grid(row=4, column=5)
button_tanh.grid(row=4, column=6)

button_pi.grid(row=5, column=4)
button_e.grid(row=5, column=5)
button_mod.grid(row=5, column=6)

root.mainloop()