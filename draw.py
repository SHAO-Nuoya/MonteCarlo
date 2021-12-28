'''
Description: 
Version: 1.0
Author: SHAO Nuoya
Date: 2021-12-28 02:05:04
LastEditors: SHAO Nuoya
LastEditTime: 2021-12-28 03:11:00
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


def plot_trajectoire(ns, data):
    plt.plot(ns, data)


eur_data = get_data('Result/DeltaEUR_CALL.txt')
asia_data = get_data('Result/DeltaASIA_CALL.txt')
ns = get_data('Result/ns.txt')

plt.figure(figsize=(20, 15))
plt.subplot(2, 1, 1)
plot_trajectoire(ns, eur_data)
plt.title("european call delta")
plt.xlabel('n')
plt.ylabel('delta')
plt.subplot(2, 1, 2)
plot_trajectoire(ns, asia_data)
plt.title("asian call delta")
plt.xlabel('n')
plt.ylabel('delta')
plt.show()
