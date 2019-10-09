# -*- coding: utf-8 -*-
"""Usando Pandas cargue los ficheros y evalúe qué información puede obtener del histograma de atributos."""

import numpy as np
import matplotlib.pyplot as mp
import pandas as pd
from scipy.io import arff
from sklearn.preprocessing import MinMaxScaler

dataD=arff.loadarff('diabetes.arff')
dataI=arff.loadarff('iris.arff')
dataW=arff.loadarff('weather.arff')


print('Histograma de la base de datos Diabetes:\n')

dfD = pd.DataFrame(dataD[0])
dfD.plot.hist(bins=12, alpha=0.5, by=4)
mp.suptitle('DIABETES')


print('Histograma de la base de datos Iris:\n')

dfI = pd.DataFrame(dataI[0])
dfI.plot.hist(bins=12, alpha=0.5, by=4)
mp.suptitle('IRIS')


print('Histograma de la base de datos Weather:\n')

dfW = pd.DataFrame(dataW[0])
dfW.plot.hist(bins=12, alpha=0.5, by=4)
mp.suptitle('WEATHER')

mp.show()
"""Estudie el efecto de la normalización (reescalar en el intervalo [0, 1]) y la estandarización (μ = 0, σ = 1) sobre el histograma."""

