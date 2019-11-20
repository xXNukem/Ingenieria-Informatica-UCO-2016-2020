# -*- coding: utf-8 -*-
from scipy.io import arff
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.tree import DecisionTreeClassifier
import pandas as pd
from sklearn.metrics import mean_squared_error
from scipy.stats import wilcoxon
from os import listdir
import numpy as np
from scipy.stats import friedmanchisquare
from scipy.stats import rankdata
from scipy.stats import f
from sklearn.svm import LinearSVC
from sklearn.gaussian_process import GaussianProcessClassifier
from sklearn.gaussian_process.kernels import RBF
from sklearn.multiclass import OutputCodeClassifier
#ejecutar con python2.7

datasets=listdir('./datasets')

scoreWilKNN=[]
scoreWilSVM=[]
scoreWilTREE=[]
"""
print('CLASIFICADOR BASE LINEARSVC')
for i in datasets:

    print('Base de datos: ' + str(i))
    dataset = arff.loadarff('./datasets/' + str(i))
    df = pd.DataFrame(dataset[0])
    data = df.iloc[:, df.columns != 'class']
    target = pd.factorize(df['class'])[0]
    X_train, X_test, Y_train, Y_test = train_test_split(data, target, test_size=0.4)

    # llamada y entrenamiento algoritmo SVM
    svc= LinearSVC(random_state=0, tol=1e-5,max_iter=9999)
    svc.fit(X_train, Y_train)
    print('Porcentaje de bien clasificados LINEARSVC')
    print(svc.score(X_test, Y_test))

print('--------------------------')
print('Aplicando metodo multiclase ONE VS ONE GAUSSIAN PROCESS CLASSIFIER')

for i in datasets:

    print('Base de datos: ' + str(i))
    dataset = arff.loadarff('./datasets/' + str(i))
    df = pd.DataFrame(dataset[0])
    data = df.iloc[:, df.columns != 'class']
    target = pd.factorize(df['class'])[0]
    X_train, X_test, Y_train, Y_test = train_test_split(data, target, test_size=0.4)


    kernel = 1.0 * RBF(1.0)
    gpc = GaussianProcessClassifier(kernel=kernel, random_state=0, multi_class = 'one_vs_one')
    gpc.fit(X_train,Y_train)
    print('Porcentaje de bien clasificados GAUSSIAN PROCESS CLASSIFIER ONE VS ONE')
    print(gpc.score(X_test,Y_test))


print('--------------------------')
print('Aplicando metodo multiclase ONE VS ALL GAUSSIAN PROCESS CLASSIFIER')

for i in datasets:

    print('Base de datos: ' + str(i))
    dataset = arff.loadarff('./datasets/' + str(i))
    df = pd.DataFrame(dataset[0])
    data = df.iloc[:, df.columns != 'class']
    target = pd.factorize(df['class'])[0]
    X_train, X_test, Y_train, Y_test = train_test_split(data, target, test_size=0.4)

    kernel = 1.0 * RBF(1.0)
    gpc = GaussianProcessClassifier(kernel=kernel, random_state=0, multi_class='one_vs_rest')
    gpc.fit(X_train, Y_train)
    print('Porcentaje de bien clasificados GAUSSIAN PROCESS CLASSIFIER ONE VS ALL')
    print(gpc.score(X_test, Y_test))

print('--------------------------')
print('Aplicando metodo multiclase ERROR CORRECTING OUTPUT CODES')
"""
for i in datasets:

    print('Base de datos: ' + str(i))
    dataset = arff.loadarff('./datasets/' + str(i))
    df = pd.DataFrame(dataset[0])
    data = df.iloc[:, df.columns != 'class']
    target = pd.factorize(df['class'])[0]
    X_train, X_test, Y_train, Y_test = train_test_split(data, target, test_size=0.4)

    clf = OutputCodeClassifier(KNeighborsClassifier(n_neighbors=5), code_size = 2, random_state = 0)
    clf.fit(X_train, Y_train)
    print('Porcentaje de bien clasificados ERROR CORRECTING OUTPUT CODES')
    print(clf.score(X_test,Y_test))