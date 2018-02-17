#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Feb 18 02:42:55 2018

@author: uhong
"""

import sys
from UI import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *


class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)
        #self.listWidget = QTableWidget(10, 6)
        self.pushButton.clicked.connect(self.set_name)

    def set_name(self):
        name = self.textEdit.toPlainText()
        salary = self.textEdit_2.toPlainText()
        self.newName = QTableWidgetItem(name)
        self.newSalary = QTableWidgetItem(salary)
        self.tableWidget.setItem(0, 0, self.newName)
        self.tableWidget.setItem(0, 1, self.newSalary)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())

