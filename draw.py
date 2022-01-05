'''
Description: 
Version: 1.0
Author: SHAO Nuoya
Date: 2021-12-28 02:05:04
LastEditors: SHAO Nuoya
LastEditTime: 2022-01-05 00:34:36
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


eur_data = get_data('Result/DeltaEUR_CALL.txt')
asia_data = get_data('Result/DeltaASIA_CALL.txt')

plt.figure(figsize=(10, 10))

plt.subplot(2, 1, 1)
plot_trajectoire(eur_data)
plt.title("european call delta")
plt.xlabel('n')
plt.ylabel('delta')
plt.grid()

plt.subplot(2, 1, 2)
plot_trajectoire(asia_data)
plt.title("asian call delta")
plt.xlabel('n')
plt.ylabel('delta')
plt.grid()
plt.savefig('Result/delta.png')
plt.show()
