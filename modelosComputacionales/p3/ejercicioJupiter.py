from sklearn.datasets import load_digits
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.preprocessing import MinMaxScaler
digits=load_digits()

#Dividiendo en conjunto de test y de entrenamiento y normalizando
X_train,X_test,Y_train,Y_test=train_test_split(digits['data'],digits['target'])
scaler=MinMaxScaler()
scaler.fit(X_train)
scaler.fit(X_test)

#Algoritmo KNN para vecinos
print('------------Ejecutando KNN para i vecinos---------')
for i in range(1,5):
    print('Vecinos: ',i)
    knn = KNeighborsClassifier(n_neighbors=i)
    knn.fit(X_train,Y_train)
    print('CCR Train')
    print(knn.score(X_train,Y_train))
    print('CCR Test')
    print(knn.score(X_test,Y_test))
    print('-------------------')

#Regresion logistica
print("---------Ejecutando regresión logística-----------")
print('Iteraciones maximas: 200')
#Para problemas multiclase utilizamos newton-cg y multiclass ovr para que se entrene un poblema binario para cada clase
logreg = LogisticRegression(random_state=0, solver='newton-cg',multi_class='ovr', max_iter=100)
logreg.fit(X_train, Y_train)
print('CCR Train')
print(logreg.score(X_train, Y_train))
print('CCR Test')
print(logreg.score(X_test, Y_test))
print('-------------------')