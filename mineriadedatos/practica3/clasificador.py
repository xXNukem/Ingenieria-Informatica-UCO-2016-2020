# -*- coding: utf-8 -*-
from scipy.io import arff
import numpy as np
import sklearn
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import KFold
from sklearn.svm import SVC
from sklearn.tree import DecisionTreeClassifier
from sklearn import metrics
import graphviz
from sklearn.tree import export_graphviz
import matplotlib.pyplot as plt
from sklearn.externals.six import StringIO
from IPython.display import Image
import pydotplus
import pandas as pd

iris=load_iris()

dataset=arff.loadarff('iris.arff')
df=pd.DataFrame(dataset[0])
print(df.keys())
data=df.iloc[:,0:4]
target=df.iloc[:,4:]
#print(target)
#hold out 60 train 40 test
X_train,X_test,Y_train,Y_test=train_test_split(data,target, test_size=0.4)

#Llamada y entrenamiento del algoritmo KNN
knn=KNeighborsClassifier(n_neighbors=25)
knn.fit(X_train,Y_train)
print('Porcentaje de bien clasificados KNN:')
print(knn.score(X_test,Y_test))
array=knn.predict([[5.2,3.4,1.6,1.1]])
print('Clase predicha KNN')
print(array)

print('----------------')

#llamada y entrenamiento algoritmo SVM
svm=SVC(gamma='auto')
svm.fit(X_train,Y_train)
print('Porcentaje de bien clasificados SVM')
print(svm.score(X_test,Y_test))
array=knn.predict([[5.2,3.4,1.6,1.1]])
print('Clase predicha SVM')
print(array)

print('-----------------')

#llamada y entrenamiento del arbol de decision
arbol=DecisionTreeClassifier()
arbol=arbol.fit(X_train,Y_train)
print('Porcentaje de bien clasificados arbol')
print(arbol.score(X_test,Y_test))
array=arbol.predict([[5.2,3.4,1.6,1.1]])
print('Clase predicha arbol')
print(array)

print('Visualizacion del arbol')
export_graphviz(arbol,out_file='arbol.dot',class_names=iris.target_names,
                feature_names=iris.feature_names,impurity=False,filled=True)
with open('arbol.dot') as f:
    dot_graph=f.read()
graph.write()
graphviz.Source(dot_graph)