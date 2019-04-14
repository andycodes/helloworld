#! /usr/bin/python
#encoding:utf-8
class Person:#创建类class
    "store information of a person"  #类的文档字串，用来简单说明这个类
    name = 'fansaihua'
    age = 30
    sex = 'male'
    def textOut(self):  # 这个 self 不可少
        print 'name is: ', self.name, ' age is ', self.age, ' and sex is ', self.sex  # 对成员变量的引用，亦必须通过 self
    @staticmethod
    def sayHello ():
        print 'hello,world!'

p = Person()
p.textOut()
p.sayHello()
Person.sayHello()
