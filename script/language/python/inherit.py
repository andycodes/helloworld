#! /usr/bin/python
#encoding:utf-8
class Namable:
    name = ''
    def __init__ (self, name):#构造函数
        self.name = name
    def output (self):
        print 'name is:', self.name

class Agable:
    age = 0
    def __init__ (self, age):
        self.age = age
    def output (self):
        print 'age is:', self.age

class Person (Namable, Agable):
    sex = 'male'
    def __init__ (self, name, age, sex = 'male'):
        Namable.__init__(self, name)  # 显式调用基类的 __init__，带 self 参数
        Agable.__init__(self, age)
        self.sex = sex

    def output (self):
        Namable.output(self) # 调用基类的函数，亦需要带上 self 参数
        Agable.output(self)
        print 'sex is:', self.sex

    def do_output (self):
        self.output() # 非基类函数，则无需手工加上 self 参数

p = Person('doudehou', 32)
p.do_output()
