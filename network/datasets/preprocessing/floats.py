from writeinput import *
import numpy as np

inputs = np.array([0x12345678, 0x12345678,
                   0x12345678, 0x12345678], dtype=np.float32)

labels = np.array([0x12345678, 0x12345678,
                   0x12345678, 0x12345678], dtype=np.float32)

data = Dataset()
data.n_inputs = 2
data.n_input_channels = 2
data.n_output_channels = 2
data.input_data = inputs
data.label_data = labels

data.write("floats")
