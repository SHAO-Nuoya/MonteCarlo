'''
Description: 
Version: 1.0
Author: SHAO Nuoya
Date: 2021-12-28 02:05:04
LastEditors: SHAO Nuoya
LastEditTime: 2022-01-05 15:44:48
'''
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np


def get_data(filename):
    data_list = []
    f = open(filename, encoding="utf-8")
    for line in f.readlines():
        string_list = line.strip().split(' ')
        data_list += list(map(float, string_list))
    f.close()

    return np.array(data_list)


def plot_hist(data_list):
    plt.hist(data_list, bins=200, density=True)


def plot_corr(data1, data2):
    corr = np.corrcoef(data1, data2)
    sns.heatmap(corr)


def plot_trajectoire(data):
    plt.plot(range(100, len(data)), data[100:])


eur_delta = get_data('Result/Delta_EUR_CALL.txt')
asia_delta = get_data('Result/Delta_ASIA_CALL.txt')
eur_gamma = get_data('Result/Gamma_EUR_CALL.txt')
asia_gamma = get_data('Result/Gamma_ASIA_CALL.txt')
eur_vega = get_data('Result/Vega_EUR_CALL.txt')
asia_vega = get_data('Result/Vega_ASIA_CALL.txt')

plt.figure(figsize=(10, 10))

plt.subplot(2, 1, 1)
plot_trajectoire(eur_delta)
plt.title("european call delta")
plt.xlabel('n')
plt.ylabel('delta')
plt.grid()

plt.subplot(2, 1, 2)
plot_trajectoire(asia_delta)
plt.title("asian call delta")
plt.xlabel('n')
plt.ylabel('delta')
plt.grid()
plt.savefig('Result/delta.png')
plt.show()

plt.figure(figsize=(10, 10))

plt.subplot(2, 1, 1)
plot_trajectoire(eur_gamma)
plt.title("european call gamma")
plt.xlabel('n')
plt.ylabel('gamma')
plt.grid()

plt.subplot(2, 1, 2)
plot_trajectoire(asia_gamma)
plt.title("asian call gamma")
plt.xlabel('n')
plt.ylabel('gamma')
plt.grid()
plt.savefig('Result/gamma.png')
plt.show()

plt.figure(figsize=(10, 10))

plt.subplot(2, 1, 1)
plot_trajectoire(eur_vega)
plt.title("european call vega")
plt.xlabel('n')
plt.ylabel('vega')
plt.grid()

plt.subplot(2, 1, 2)
plot_trajectoire(asia_vega)
plt.title("asian call vega")
plt.xlabel('n')
plt.ylabel('vega')
plt.grid()
plt.savefig('Result/vega.png')
plt.show()