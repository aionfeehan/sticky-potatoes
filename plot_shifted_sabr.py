import matplotlib.pyplot as plt
import numpy as np
import os

def main():
    os.system('release/all_tests')

    with open("release/shifted_sabr_smile.csv", 'r') as f:
        strike_vol_pairs = f.read().split("\n")
    strike_vol_pairs = [p for p in strike_vol_pairs if len(p)]
    strikes = [float(p.split(',')[0]) for p in strike_vol_pairs]
    vols = [float(p.split(',')[1]) for p in strike_vol_pairs]
    plt.plot(strikes, vols)
    plt.xticks(np.arange(strikes[0], strikes[-1], 0.01))
    plt.yticks(np.linspace(min(vols), max(vols), 10))
    plt.show()

if __name__ == '__main__':
    main()