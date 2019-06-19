import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QAction,QLabel,QLineEdit,QPushButton
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QTextEdit, QTextBrowser, QHBoxLayout, QVBoxLayout
import time
 
class GUI(QMainWindow):
    def __init__(self):
        super().__init__()
        self.iniUI()
        self.buttonClicked()
 
    def iniUI(self):
        self.setWindowTitle("PythonGUI教程")
        self.statusBar().showMessage("文本状态栏")
        self.resize(400, 300)
        #self.browser_label = QLabel('QTextBrowser', self)
        #self.text_edit = QTextEdit(self)
        self.text_browser = QTextBrowser(self)
        self.text_browser.move(160,30)
        self.text_browser.resize(200,200)
        self.qle = QLineEdit(self)
        self.qle.move(20, 80)
        btn1 = QPushButton("确定", self)
        btn1.move(20, 120)
        #print(qle.text())
        btn1.clicked.connect(self.buttonClicked)
 
        # 创建一个菜单栏
        menu = self.menuBar()
        # 创建两个个菜单
        file_menu = menu.addMenu("文件")
        file_menu.addSeparator()
        edit_menu = menu.addMenu('修改')
 
        # 创建一个行为
        new_action = QAction('新的文件', self)
        # 更新状态栏文本
        new_action.setStatusTip('打开新的文件')
        # 添加一个行为到菜单
        file_menu.addAction(new_action)
 
        # 创建退出行为
        exit_action = QAction('退出', self)
        # 退出操作
        exit_action.setStatusTip("点击退出应用程序")
        # 点击关闭程序
        exit_action.triggered.connect(self.close)
        # 设置退出快捷键
        exit_action.setShortcut('Ctrl+z')
        # 添加退出行为到菜单上
        file_menu.addAction(exit_action)
 
    def buttonClicked(self):
        self.text_browser.setText(self.qle.text())
 
if __name__ == '__main__':
    app = QApplication(sys.argv)
    gui = GUI()
    gui.show()
    sys.exit(app.exec_())