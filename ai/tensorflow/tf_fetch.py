#! /usr/bin/python
import tensorflow as tf
sess = tf.InteractiveSession()
print ("Hello World")

input1 = tf.constant(3.0)
input2 = tf.constant(2.0)
input3 = tf.constant(5.0)
intermed = tf.add(input2, input3)
mul = tf.multiply(input1, intermed)

with tf.Session():
  result = sess.run([mul, intermed])
  print result
