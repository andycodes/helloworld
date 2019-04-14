
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QLineEdit,QInputDialog

import make_new_register_info_dict

class MyWindow(QtWidgets.QWidget):
	def __init__(self):
		super(MyWindow,self).__init__()
		self.myButton = QtWidgets.QPushButton(self)
		self.myButton.setObjectName("myButton")
		self.myButton.setText("Test")
		self.myButton.clicked.connect(self.msg)

	def msg(self):
		items = ["Spring", "Summer", "Fall", "Winter"]
		new_reg_dict = make_new_register_info_dict.build_new_register_info_dict('./test_image.map')
		item, ok4 = QInputDialog.getItem(self, "标题","Season:", new_reg_dict.keys(), 1, True)