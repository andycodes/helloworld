
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QLineEdit,QInputDialog

class MyWindow(QtWidgets.QWidget):
    def __init__(self):
        super(MyWindow,self).__init__()
        self.myButton = QtWidgets.QPushButton(self)
        self.myButton.setObjectName("myButton")
        self.myButton.setText("Test")
        self.myButton.clicked.connect(self.msg)

    def msg(self):
         #后面四个数字的作用依次是 初始值 最小值 最大值 小数点后位数
        doubleNum,ok1 = QInputDialog.getDouble(self, "标题","计数:", 37.56, -10000, 10000, 2)   
         #后面四个数字的作用依次是 初始值 最小值 最大值 步幅
        intNum,ok2 = QInputDialog.getInt(self, "标题","计数:", 37, -10000, 10000, 2)    
         #第三个参数可选 有一般显示 （QLineEdit.Normal）、密碼显示（ QLineEdit. Password）与不回应文字输入（ QLineEdit. NoEcho）
        stringNum,ok3 = QInputDialog.getText(self, "标题","姓名:",QLineEdit.Normal, "王尼玛")   
         #1为默认选中选项目，True/False  列表框是否可编辑。
        items = ["Spring", "Summer", "Fall", "Winter"]
        item, ok4 = QInputDialog.getItem(self, "标题","Season:", items, 1, True)   
        text, ok5 = QInputDialog.getMultiLineText(self, "标题", "Address:", "John Doe\nFreedom Street")

if __name__=="__main__":  
    import sys  
  
    app=QtWidgets.QApplication(sys.argv)  
    myshow=MyWindow()
    myshow.show()
    sys.exit(app.exec_())  