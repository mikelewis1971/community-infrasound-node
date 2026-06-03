import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.signal import spectrogram

data = pd.read_csv("../firmware/data.csv")

acc = np.sqrt(data["ax"]**2 + data["ay"]**2 + data["az"]**2)
acc = acc - np.mean(acc)

fs = 200

f, t, Sxx = spectrogram(acc, fs)

plt.figure()
plt.pcolormesh(t, f, 10 * np.log10(Sxx))
plt.ylabel("Frequency (Hz)")
plt.xlabel("Time (s)")
plt.title("Vibration Spectrogram")
plt.colorbar(label="dB")
plt.ylim(0, 80)
plt.show()
