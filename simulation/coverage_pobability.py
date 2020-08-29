import matplotlib.pyplot as plt
import numpy as np
coverage_rate = []
with open("coverage_rate.txt") as files:
    for data in files:
        coverage_rate.append(float(data.strip()))
T_range = np.linspace( -10, 20, 51 )
plt.plot(T_range, coverage_rate)
plt.xlim(-10, 20)
plt.ylim(0,1)
plt.yticks(np.arange(0,1,0.1))
plt.show()

