

from PyQt5.QtWidgets import QApplication, QAction, QFileDialog,  QTextEdit
from PyQt5 import QtWidgets
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QIcon

class OpenFile(QtWidgets.QMainWindow):
	def __init__(self, parent= None):
		QtWidgets.QWidget.__init__(self)

		self.setGeometry(300, 300, 150, 110)
		self.setWindowTitle('OpenFile')
		self.textEdit = QTextEdit()
		self.setCentralWidget(self.textEdit)

		self.statusBar()
		self.setFocus()

		file = open('./test_image.map')
		data = file.read() 
		self.textEdit.setText(data)


#if __name__ == "__main__":
#    import sys
#    app = QApplication(sys.argv)
#    qb = OpenFile()
#    qb.show()
#    sys.exit(app.exec_())