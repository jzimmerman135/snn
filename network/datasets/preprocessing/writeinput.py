import numpy as np

class Dataset():
    def __init__(self):
        self.n_inputs = None
        self.n_input_channels = None
        self.n_output_channels = None
        self.input_data = None
        self.label_data = None

    def write(self, filename):
        if (filename[-5:] != ".data"):
            filename = filename + ".data"

        with open(f"./datasets/{filename}", "wb") as file:
            assert(self.n_inputs)
            assert(self.n_input_channels and self.n_output_channels)
            assert(self.input_data is not None)
            assert(self.label_data is not None)

            s1 = self.n_inputs
            s2 = self.n_input_channels
            s3 = self.n_output_channels

            header = "%i INPUTS, %i INPUT CHANNELS, %i OUTPUT CHANNELS\n" % (s1, s2, s3)
            file.write(header.encode('ascii'))
            file.write(self.input_data.tobytes())
            file.write(self.label_data.tobytes())
