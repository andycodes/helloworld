
import tensorflow as tf;
import numpy as np;
import matplotlib.pyplot as plt;
 
c = tf.truncated_normal(shape=[10,10], mean=0, stddev=1)
 
with tf.Session() as sess:
	print sess.run(c)