import numpy as np
import matplotlib.pyplot as plt

t_max = 150e-3   # second
dt = 1e-3        # second
tau = 20e-3      # second
el = -60e-3      # milivolt
vr = -70e-3      # milivolt
vth = -50e-3     # milivolt
r = 100e6        # ohm
i_mean = 25e-11  # ampere

print("Variables: ",'\n',"t_max:", t_max, "dt:", dt, "tau:", tau,"el:", el,"vr:", vr,"vth:", vth,"r:", r,"i_mean:", i_mean, '\n')

# Loop for 10 steps, variable 'step' takes values from 0 to 9
for step in range(10):

  # Compute value of t
  t = step * dt

  # Compute value of i at this time step
  i = i_mean * (1 + np.sin(2 * np.pi * t / 0.01))

  # Print value of i
  print(i)