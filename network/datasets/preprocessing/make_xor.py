import numpy as np
from writeinput import *

# inputs
input_arr = np.array([0.01,0.03,0.028,
                      0.02,0.032,0.99,
                      0.03,0.98,0.023,
                      0.03,0.99,0.993,
                      0.989,0.023,0.003,
                      0.99,0.01,0.993,
                      0.991,0.989,0.012,
                      0.999,0.993,0.989], dtype="float32")

# outputs
output_arr = np.array([0.01, 0.99,
                       0.99, 0.02,
                       0.989, 0.043,
                       0.012, 0.975,
                       0.982, 0.008,
                       0.009, 0.988,
                       0.011, 0.995,
                       0.998, 0.072], dtype="float32")

train = Dataset()
train.n_inputs = 8
train.n_input_channels = 3
train.n_output_channels = 2
train.input_data = input_arr
train.label_data = output_arr

# filename can be 'xor' or 'xor.data' –– both will work
train.write("xor")
