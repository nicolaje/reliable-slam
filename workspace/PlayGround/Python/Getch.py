import time
import curses

ENTER_KEY = (curses.KEY_ENTER, ord('\n'), ord('\r'))

def run(win, timeout=3): # timeout in seconds
    win.addstr(0, 0, "Enter something: ")
    while True:
        c = win.getch()
        if c == curses.KEY_UP:
            

curses.wrapper(run)
