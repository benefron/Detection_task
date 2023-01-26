# imprt all necessery packages

from PyQt5.QtWidgets import QMainWindow, QApplication, QPushButton, QComboBox, QFileDialog, QTextEdit ,QSpinBox, QGraphicsView
from PyQt5 import uic
import os
import sys
import pandas as pd
#from tkinter import Tk
#from tkinter.filedialog import askdirectory
import pyqtgraph as pg
import numpy as np


#Create the main class
class UI(QMainWindow):
    def __init__(self):
        super(UI, self).__init__()

        # load UI file
        uic.loadUi('MainGUI.ui', self)

        #define our widgets
        self.loadB = self.findChild(QPushButton,'LoadData')
        self.Animal = self.findChild(QComboBox,'Animal')
        self.Date = self.findChild(QComboBox,'Date')
        self.Session = self.findChild(QSpinBox,'Session')
        self.graphicsView_2 = self.findChild(QGraphicsView,'QSpinBox,')
        


        # load directories
        self.loadB.clicked.connect(self.DirLoad)
        self.Animal.activated.connect(self.getData)

        #show the app
        self.show()
    #define the functions for the class
    def DirLoad(self):
        self.Animal.clear()
        directory = QFileDialog.getExistingDirectory(None, "Select a folder")
        if directory:
    # Get a list of all directories in the selected directory
            dir_list = [f.path for f in os.scandir(directory) if f.is_dir()]
            self.Animal.addItems(dir_list)

    def getData(self):
        
        def month4day():
            days = self.events.values[:,2]
            months = self.events.values[:,3]
            uniqueDaysAsc, indD = np.unique(days, return_index=True, return_inverse=False)
            sorted_index = np.argsort(indD)
            uniqueDays = uniqueDaysAsc[sorted_index]
            #print(uniqueDays)
            dayU = []
            k = 0
            for day in uniqueDays:
                #print(day)
                allMonth = months[np.where(days == day)]
                #print(allMonth)
                uniqueMonthAsc ,indM = np.unique(allMonth,return_index=True, return_inverse=False)
                sorted_index_m = np.argsort(indM)
                uniqueMonth = uniqueMonthAsc[sorted_index_m]
                #print(uniqueMonth)
                for dayM in uniqueMonth:
                    string = "{}_{}".format(day,dayM)
                    dayU.append(string)
                    k += 1
            return dayU
            
            

        self.Date.clear()
        file1_path = os.path.join(self.Animal.currentText(), "events.csv")
        self.events = pd.read_csv(file1_path,on_bad_lines='skip')
        self.Date.addItems(month4day())



app = QApplication(sys.argv)
UIWindow = UI()
app.exec_()