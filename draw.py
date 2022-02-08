'''
Description: 
Version: 1.0
Author: SHAO Nuoya
Date: 2021-12-28 02:05:04
LastEditors: SHAO Nuoya
LastEditTime: 2022-02-08 22:38:52
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


def plot_greek(FD_data, M_data, ML_data, option_name, greek_name):
    plt.figure(figsize=(10, 10))

    # Finite difference method
    if len(FD_data):
        plt.plot(range(1000, len(FD_data)),
                 FD_data[1000:],
                 label='Finite Diff',
                 linestyle="--")

    # Malliavin method
    if len(M_data):
        plt.plot(range(1000, len(M_data)),
                 M_data[1000:],
                 label='Malliavin',
                 color='purple',
                 linestyle="--")

    # Malliavin method
    if len(ML_data):
        plt.plot(range(1000, len(ML_data)),
                 ML_data[1000:],
                 label='Loc_Malliavin',
                 color='green',
                 linestyle="--")

    if option_name == 'European call':
        # Theoretical value
        plt.axhline(y=EU_theo_values[greek_name], color='red', label='Theo')

        # PDE value
        plt.axhline(y=PDE_values[greek_name],
                    color='orange',
                    label='PDE',
                    linestyle=":")

    plt.title(option_name + "-" + greek_name)
    plt.xlabel('n')
    plt.ylabel(greek_name)
    plt.grid()
    plt.legend()

    plt.savefig("Result/" + option_name + '_' + greek_name + ".png")
    plt.show()


keys = ['delta', 'gamma', 'vega']
EU_theo_values = get_data('Result/theo_eur_call_greeks.txt')
EU_theo_values = {
    keys[i]: EU_theo_values[i]
    for i in range(len(EU_theo_values))
}

PDE_values = get_data('Result/PDE_eur_call_greeks.txt')
PDE_values = {keys[i]: PDE_values[i] for i in range(len(PDE_values))}

# Malliavin
m_eur_delta = get_data('Result/M_Delta_EUR_CALL.txt')
m_asia_delta = get_data('Result/M_Delta_ASIA_CALL.txt')
m_eur_gamma = get_data('Result/M_Gamma_EUR_CALL.txt')
m_asia_gamma = get_data('Result/M_Gamma_ASIA_CALL.txt')
m_eur_vega = get_data('Result/M_Vega_EUR_CALL.txt')
m_asia_vega = get_data('Result/M_Vega_ASIA_CALL.txt')

# Locallized Malliavin
ml_eur_delta = get_data('Result/ML_Delta_EUR_CALL.txt')
ml_asia_delta = get_data('Result/ML_Delta_ASIA_CALL.txt')
ml_eur_gamma = get_data('Result/ML_Gamma_EUR_CALL.txt')
ml_asia_gamma = get_data('Result/ML_Gamma_ASIA_CALL.txt')
ml_eur_vega = get_data('Result/ML_Vega_EUR_CALL.txt')
ml_asia_vega = get_data('Result/ML_Vega_ASIA_CALL.txt')

# Finite difference
fd_eur_delta = get_data('Result/FD_Delta_EUR_CALL.txt')
fd_asia_delta = get_data('Result/FD_Delta_ASIA_CALL.txt')
fd_eur_gamma = get_data('Result/FD_Gamma_EUR_CALL.txt')
fd_asia_gamma = get_data('Result/FD_Gamma_ASIA_CALL.txt')
fd_eur_vega = get_data('Result/FD_Vega_EUR_CALL.txt')
fd_asia_vega = get_data('Result/FD_Vega_ASIA_CALL.txt')

plot_greek(fd_eur_delta, m_eur_delta, ml_eur_delta, 'European call', 'delta')

plot_greek(fd_eur_gamma, m_eur_gamma, ml_eur_gamma, 'European call', 'gamma')

plot_greek(fd_eur_vega, m_eur_vega, ml_eur_vega, 'European call', 'vega')

plot_greek(fd_asia_delta, m_asia_delta, ml_asia_delta, 'Asian call', 'delta')

plot_greek(fd_asia_gamma, m_asia_gamma, ml_asia_gamma, 'Asian call', 'gamma')
