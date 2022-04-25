import numpy as np
import os

os.path.join

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
output_arr = np.array([0.01,
                       0.99,
                       0.989,
                       0.012,
                       0.982,
                       0.009,
                       0.011,
                       0.998], dtype="float32")

# # set up file
with open("../xor.data", "wb") as file:
    file.write("8 INPUTS, 3 INPUT CHANNELS, 2 OUTPUT CHANNELS".encode('ascii'))
    file.write(input_arr.tobytes())
    file.write(output_arr.tobytes())
