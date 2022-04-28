from writeinput import *
import numpy as np

# inputs
input_arr = np.array([0.001, 0.1023, 0.2244,
                      0.312, 0.412, 0.5123,
                      0.612, 0.711, 0.811,
                      0.893, 0.996], dtype=np.float32)

# outputs
output_arr = np.array([0.01, 0.99], dtype=np.float32)

train = Dataset()
train.n_inputs = 1
train.n_input_channels = 11
train.n_output_channels = 2
train.input_data = input_arr
train.label_data = output_arr

train.write("strain")
