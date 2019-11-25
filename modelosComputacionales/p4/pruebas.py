import pandas as pd
from sklearn.model_selection import StratifiedShuffleSplit
from sklearn import svm
from sklearn.model_selection import GridSearchCV
import numpy as np

data = pd.read_csv('./BasesDatos/csv/train_nomnist.csv', header=None)
X_train = data.iloc[:, :-1].values
y_train = data.iloc[:, -1].values

data = pd.read_csv('./BasesDatos/csv/test_nomnist.csv', header=None)
X_test = data.iloc[:, :-1].values
y_test = data.iloc[:, -1].values

sss = StratifiedShuffleSplit(test_size=0.25, train_size=0.75, n_splits=10)

for train_index, test_index in sss.split(X, y):
    X_train, X_test = X[train_index], X[test_index]
    y_train, y_test = y[train_index], y[test_index]

    Cs = np.logspace(-5, 15, num=11, base=2)
    Gs = np.logspace(-15, 3, num=9, base=2)
    svm_model = svm.SVC(kernel='rbf')
    optimo = GridSearchCV(estimator=svm_model, param_grid=dict(C=Cs, gamma=Gs), n_jobs=-1, cv=5)
    optimo.fit(X_train, y_train)
    print('Mejores parametros: ')
    print(optimo.best_params_)
    print('Puntuacion: ')
    print(optimo.score(X_test, y_test))