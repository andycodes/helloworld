#! /usr/bin/python3

from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QLineEdit,QInputDialog
from PyQt5.QtWidgets import QApplication, QAction, QFileDialog,  QTextEdit
from PyQt5 import QtWidgets
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QIcon

import sys
import make_new_register_info_dict
import put_list_to_gui
import file_show_map

if __name__ == '__main__':
	#gui show file
	app=QtWidgets.QApplication(sys.argv)
	myshow=put_list_to_gui.MyWindow()
	myshow.show()

	#input 
	qb = file_show_map.OpenFile()
	qb.show()
	sys.exit(app.exec_())