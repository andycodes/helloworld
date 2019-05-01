#!/usr/bin/env python3
# coding: utf-8
import os, tarfile,shutil
import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QAction,QLabel,QLineEdit,QPushButton
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QTextEdit, QTextBrowser, QHBoxLayout, QVBoxLayout
import time
 
def make_targz(output_filename, source_dir):
    """
    一次性打包目录为tar.gz
    :param output_filename: 压缩文件名
    :param source_dir: 需要打包的目录
    :return: bool
    """
    try:
        with tarfile.open(output_filename, "w:gz") as tar:
            tar.add(source_dir, arcname=os.path.basename(source_dir))

        return True
    except Exception as e:
        print(e)
        return False


def untar(fname, dirs):
    """
    解压tar.gz文件
    :param fname: 压缩文件名
    :param dirs: 解压后的存放路径
    :return: bool
    """
    try:
        t = tarfile.open(fname)
        t.extractall(path = dirs)
        return True
    except Exception as e:
        print(e)
        return False

def make_newdir(path):
	isExists=os.path.exists(path)
	if not isExists:
		os.mkdir(path)
	else:
		shutil.rmtree(path)
		os.mkdir(path)
 
 
class GUI(QMainWindow):
    def __init__(self):
        super().__init__()
        self.iniUI()
        self.buttonClicked()
 
    def iniUI(self):
        self.setWindowTitle("LOG自动解压归档")
        #self.statusBar().showMessage("文本状态栏")
        self.resize(400, 300)
        self.qle = QLineEdit(self)
        self.qle.move(20, 80)
        btn1 = QPushButton("解压", self)
        btn1.move(20, 120)
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
        dddd=self.qle.text()
        print(dddd)
        path = 'G:/tmp/dirname'
        kernel_dirpath='unrardir_kernel'
        hal_dirpath='unrardir_hal'
        make_newdir(kernel_dirpath)
        make_newdir(hal_dirpath)
        files = os.listdir(path)
        for f in files:
            if f.endswith('.tar.gz') and 'kernel' in f:
                untar(f,kernel_dirpath)
            if f.endswith('.tar.gz') and 'hal' in f:
                untar(f,hal_dirpath)
 
if __name__ == '__main__':
    app = QApplication(sys.argv)
    gui = GUI()
    gui.show()
    sys.exit(app.exec_())