'''
Description: 
Version: 1.0
Author: SHAO Nuoya
Date: 2021-12-28 02:05:04
LastEditors: SHAO Nuoya
LastEditTime: 2022-01-06 19:02:23
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


def plot_greek(eur_data, asia_data, greek_name):
    plt.figure(figsize=(10, 10))

    plt.subplot(2, 1, 1)
    plt.plot(range(100, len(eur_data)), eur_data[100:])
    plt.title(f"european call {greek_name}")
    plt.xlabel('n')
    plt.ylabel(greek_name)
    plt.grid()

    plt.subplot(2, 1, 2)
    plt.plot(range(100, len(asia_data)), asia_data[100:])
    plt.title(f"asian call {greek_name}")
    plt.xlabel('n')
    plt.ylabel(greek_name)
    plt.grid()
    plt.savefig(f'Result/{greek_name}.png')
    plt.show()


eur_delta = get_data('Result/Delta_EUR_CALL.txt')
asia_delta = get_data('Result/Delta_ASIA_CALL.txt')
eur_gamma = get_data('Result/Gamma_EUR_CALL.txt')
asia_gamma = get_data('Result/Gamma_ASIA_CALL.txt')
eur_vega = get_data('Result/Vega_EUR_CALL.txt')
asia_vega = get_data('Result/Vega_ASIA_CALL.txt')
eur_rho = get_data('Result/Rho_EUR_CALL.txt')
asia_rho = get_data('Result/Rho_ASIA_CALL.txt')

plot_greek(eur_delta, asia_delta, 'delta')
plot_greek(eur_gamma, asia_gamma, 'gamma')
plot_greek(eur_vega, asia_vega, 'vega')
plot_greek(eur_rho, asia_rho, 'rho')