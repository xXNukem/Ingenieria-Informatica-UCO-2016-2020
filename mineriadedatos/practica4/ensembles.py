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
from sklearn.model_selection import cross_val_score
from sklearn.ensemble import bagging
from sklearn import model_selection
from sklearn.ensemble import GradientBoostingClassifier
from sklearn.ensemble import GradientBoostingRegressor

datasets=listdir('./datasets')

scoreWilKNN=[]
scoreWilSVM=[]
scoreWilTREE=[]
"""
print('Aplicando método base: ')

for i in datasets:

    print('Base de datos: ' + str(i))
    dataset = arff.loadarff('./datasets/' + str(i))
    df = pd.DataFrame(dataset[0])
    data = df.iloc[:, df.columns != 'class']
    target = pd.factorize(df['class'])[0]


    # Llamada y entrenamiento del algoritmo KNN
    print('Puntuacion KNN')
    knn = KNeighborsClassifier(n_neighbors=5)
    cv_scores=cross_val_score(knn,data,target,cv=3)
    print(cv_scores)
    print('----------------')


    # llamada y entrenamiento algoritmo SVM
    print('Puntuacion SVM')
    svm = SVC(gamma='auto')
    cv_scores = cross_val_score(svm, data, target, cv=3)
    print(cv_scores)

    print('-----------------')

    # llamada y entrenamiento del arbol de decision
    print('Puntuacion TREE')
    arbol = DecisionTreeClassifier()
    cv_scores = cross_val_score(arbol, data, target, cv=3)
    print(cv_scores)

    print('-----------------------------------------------')
"""

"""
print('Aplicando metodo de combinacion BAGGING')

for i in datasets:

    print('Base de datos: ' + str(i))
    dataset = arff.loadarff('./datasets/' + str(i))
    df = pd.DataFrame(dataset[0])
    data = df.iloc[:, df.columns != 'class']
    target = pd.factorize(df['class'])[0]

    for base_estimator in [KNeighborsClassifier(n_neighbors=5),SVC(gamma='auto'),DecisionTreeClassifier()]:

        kfold = model_selection.KFold(n_splits=3)
        model = bagging.BaggingClassifier(base_estimator=base_estimator)
        results = model_selection.cross_val_score(model, data, target, cv=kfold)
        print(results)





print('Algoritmo de BOOSTING: Classifier')

for i in datasets:

    print('Base de datos: ' + str(i))
    dataset = arff.loadarff('./datasets/' + str(i))
    df = pd.DataFrame(dataset[0])
    data = df.iloc[:, df.columns != 'class']
    target = pd.factorize(df['class'])[0]

    kfold = model_selection.KFold(n_splits=3)
    model = GradientBoostingClassifier(n_estimators=100, learning_rate=1.0,max_depth=1, random_state=0)
    results = model_selection.cross_val_score(model,data,target,cv=kfold)
    print(results)
"""
print('Algoritmo de BOOSTING: Regressor')

for i in datasets:

    print('Base de datos: ' + str(i))
    dataset = arff.loadarff('./datasets/' + str(i))
    df = pd.DataFrame(dataset[0])
    data = df.iloc[:, df.columns != 'class']
    target = pd.factorize(df['class'])[0]

    kfold = model_selection.KFold(n_splits=10)
    model=GradientBoostingRegressor(n_estimators=100, learning_rate=0.1,max_depth=1, random_state=0, loss='ls')
    results=model_selection.cross_val_score(model,data,target,cv=kfold)
    print(results)

