from time import time, sleep
from Клавиатура import Клавиатура
from sys import path; path.append('../МидиРазбор')
from MidiParser import MidiParser

__author__ = 'Борис Шаховский'

клавиатура = Клавиатура()
старт = time()
миди = MidiParser('../../Visual Studio 2015/Projects/Test.mid')
клавиатура.нажать_клавишу(миди.notes[1][0])
предыдущее_время = миди.milli_seconds[1][0]
for i, нота in enumerate(миди.notes[1][1:], 1):
    продолжительность = миди.milli_seconds[1][i] - предыдущее_время
    if продолжительность > 7:  # 7 миллисекунд - считается одновременно
        подождать = старт + продолжительность / 1000 - time()
        sleep(подождать if подождать > 0 else 0)
        клавиатура.обновить()
        старт = time()
        клавиатура.отпустить_все_клавиши()
    клавиатура.нажать_клавишу(нота)
    предыдущее_время = миди.milli_seconds[1][i]
