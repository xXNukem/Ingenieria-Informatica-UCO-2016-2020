# -*- coding: utf-8 -*-

from scipy.io import arff
from sklearn.model_selection import train_test_split
import pandas as pd
from sklearn.cluster import KMeans
from sklearn.cluster import AgglomerativeClustering
from sklearn.metrics.cluster import homogeneity_score


basededatos='./datasets/iris.arff'
num_clusters=3

print('Base de datos: ' + str(basededatos))
dataset = arff.loadarff(str(basededatos))
df = pd.DataFrame(dataset[0])
data = df.iloc[:, df.columns != 'class']
target = pd.factorize(df['class'])[0]
X_train, X_test, Y_train, Y_test = train_test_split(data, target, test_size=0.4)
#EN ESTA PRACTICA NO SE USARA LA INFORMACION DE LA CLASE
#Ajustar los clusters segun las clases conocidas


print('Clustering con K-MEANS')
kmeans=KMeans(n_clusters=num_clusters, random_state=0)
results=kmeans.fit(data)
print(results.labels_) # Imprimimos el Clustering realizado
print('Puntuacion de homogeneidad:')
print(homogeneity_score(Y_test,kmeans.predict(X_test,Y_test)))



print('Clustering con SINGLE LINK')
single=AgglomerativeClustering(n_clusters=num_clusters, linkage='single')
results=single.fit(data)
print(results.labels_)



print('Clustering con COMPLETE LINK')
complete=AgglomerativeClustering(n_clusters=num_clusters,linkage='complete')
results=complete.fit(data)
print(results.labels_)



print('Custering con AVERAGE LINK')
average=AgglomerativeClustering(n_clusters=num_clusters, linkage='average')
results=average.fit(data)
print(results.labels_)