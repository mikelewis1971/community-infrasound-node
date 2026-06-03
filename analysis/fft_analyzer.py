import numpy as np
import pandas as pd
from scipy.signal import welch
import matplotlib.pyplot as plt

# -------------------------------------------------------
# Load data
# -------------------------------------------------------

data = pd.read_csv("../firmware/data.csv")

# Extract acceleration magnitude
acc = np.sqrt(data["ax"]**2 + data["ay"]**2 + data["az"]**2)

# Remove DC offset
acc = acc - np.mean(acc)

# -------------------------------------------------------
# FFT using Welch method (stable for noisy signals)
# -------------------------------------------------------

fs = 200  # sampling rate (200 Hz)

freqs, psd = welch(acc, fs=fs, nperseg=1024)

# -------------------------------------------------------
# Plot frequency spectrum
# -------------------------------------------------------

plt.figure()
plt.semilogy(freqs, psd)
plt.title("Vibration Frequency Spectrum")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Power")
plt.grid()
plt.show()
