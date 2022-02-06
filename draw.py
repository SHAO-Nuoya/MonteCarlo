'''
Description: 
Version: 1.0
Author: SHAO Nuoya
Date: 2021-12-28 02:05:04
LastEditors: SHAO Nuoya
LastEditTime: 2022-02-06 11:08:28
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


def plot_greek(FD_eur_data, FD_asia_data, M_eur_data, M_asia_data, greek_name):
    plt.figure(figsize=(10, 10))

    # euro option
    plt.subplot(2, 1, 1)

    # Finite difference method
    plt.plot(range(100, len(FD_eur_data)),
             FD_eur_data[100:],
             label='Finite Diff')

    # Malliavin method
    plt.plot(range(100,
                   len(M_eur_data) - 1),
             M_eur_data[100:-1],
             label='Malliavin',
             color='green')

    # Theoretical value
    plt.axhline(y=M_eur_data[-1], color='red', label='Theo')

    plt.title(f"european call {greek_name}")
    plt.xlabel('n')
    plt.ylabel(greek_name)
    plt.grid()
    plt.legend()

    # asian option
    plt.subplot(2, 1, 2)

    # Finite difference method
    plt.plot(range(10, len(FD_asia_data)),
             FD_asia_data[10:],
             label='Finite Diff')

    # Malliavin method
    plt.plot(range(10,
                   len(M_asia_data) - 1),
             M_asia_data[10:-1],
             label='Malliavin',
             color='green')
    plt.title(f"asian call {greek_name}")
    plt.xlabel('n')
    plt.ylabel(greek_name)
    plt.grid()
    plt.legend()

    plt.savefig(f'Result/{greek_name}.png')
    plt.show()


# # Malliavin
m_eur_delta = get_data('Result/M_Delta_EUR_CALL.txt')
m_asia_delta = get_data('Result/M_Delta_ASIA_CALL.txt')
m_eur_gamma = get_data('Result/M_Gamma_EUR_CALL.txt')
m_asia_gamma = get_data('Result/M_Gamma_ASIA_CALL.txt')
m_eur_vega = get_data('Result/M_Vega_EUR_CALL.txt')
m_asia_vega = get_data('Result/M_Vega_ASIA_CALL.txt')
m_eur_rho = get_data('Result/M_Rho_EUR_CALL.txt')
m_asia_rho = get_data('Result/M_Rho_ASIA_CALL.txt')

# Finite difference
fd_eur_delta = get_data('Result/FD_Delta_EUR_CALL.txt')
fd_asia_delta = get_data('Result/FD_Delta_ASIA_CALL.txt')
fd_eur_gamma = get_data('Result/FD_Gamma_EUR_CALL.txt')
fd_asia_gamma = get_data('Result/FD_Gamma_ASIA_CALL.txt')
fd_eur_vega = get_data('Result/FD_Vega_EUR_CALL.txt')
fd_asia_vega = get_data('Result/FD_Vega_ASIA_CALL.txt')
fd_eur_rho = get_data('Result/FD_Rho_EUR_CALL.txt')
fd_asia_rho = get_data('Result/FD_Rho_ASIA_CALL.txt')

plot_greek(fd_eur_delta, fd_asia_delta, m_eur_delta, m_asia_delta, 'delta')
plot_greek(fd_eur_gamma, fd_asia_gamma, m_eur_gamma, m_asia_gamma, 'gamma')
plot_greek(fd_eur_vega, fd_asia_vega, m_eur_vega, m_asia_vega, 'vega')
plot_greek(fd_eur_rho, fd_asia_rho, m_eur_rho, m_asia_rho, 'rho')
