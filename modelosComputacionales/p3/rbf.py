#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@author: Carlos de la Barrera Perez
"""

# TODO Incluir todos los import necesarios
import pickle
import os
import click
import pandas as pd
import numpy as np
import math
import time
import random
from click._compat import raw_input
from scipy.spatial import distance
from sklearn.cluster import KMeans
from sklearn.metrics import accuracy_score, pairwise_distances
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import mean_squared_error
from sklearn.metrics import confusion_matrix
from sklearn.model_selection import StratifiedShuffleSplit
from sklearn.preprocessing import label_binarize, OneHotEncoder


@click.command()
@click.option('--train_file', '-t', default=None, required=True,help=u'Fichero con los datos de entrenamiento.')
@click.option('--test_file', '-T', default=None, required=False, help=u'Fichero con los datos de test.')
@click.option('--classification', '-c', is_flag=True,help=u'ue indica si el problema es de clasiﬁcacion. Si no se especiﬁca, supondremos que el problema es de regresion.')
@click.option('--ratio_rbf', '-rb', default=0.1, required=False,help=u'Indica la razon.')
@click.option('--l2', '-l', is_flag=True, help=u'Boleano que se usa para la reguluzación L2.')
@click.option('--outputs', '-o', default=1, required=False,help=u'Numero de salidas.')
@click.option('--eta', '-e', default=(1 * math.exp(-5)), required=False, help=u'Ajuste del factor eta.')
@click.option('--matrix_m', '-m', is_flag=True,help=u'Boleano que se usa para mostrar la matriz de confusion')
# TODO incluir el resto de parámetros...

def entrenar_rbf_total(train_file, test_file, classification, ratio_rbf, l2, eta, outputs, matrix_m):
    """ Modelo de aprendizaje supervisado mediante red neuronal de tipo RBF.
        Ejecución de 5 semillas.
    """
    if train_file is None:
        print("No se ha especificado el conjunto de entrenamiento (-t)")
        return
    if test_file is None:
        test_file = train_file

    train_mses = np.empty(5)
    train_ccrs = np.empty(5)
    test_mses = np.empty(5)
    test_ccrs = np.empty(5)
    tiempos = np.empty(5)
    for s in range(1, 6, 1):
        print("-----------")
        print("Semilla: %d" % s)
        print("-----------")
        np.random.seed(s)
        inicio = time.time()
        train_mses[s - 1], test_mses[s - 1], train_ccrs[s - 1], test_ccrs[s - 1] = entrenar_rbf(train_file, test_file,
                                                                                                classification,
                                                                                                ratio_rbf, l2, eta,
                                                                                                outputs, matrix_m)
        fin = time.time()
        tiempos[s - 1] = fin - inicio
        print("Tiempo de ejecución: %f" % tiempos[s - 1])
        print("MSE de entrenamiento: %f" % train_mses[s - 1])
        print("MSE de test: %f" % test_mses[s - 1])
        print("CCR de entrenamiento: %.2f%%" % train_ccrs[s - 1])
        print("CCR de test: %.2f%%" % test_ccrs[s - 1])

    print("*********************")
    print("Resumen de resultados")
    print("*********************")
    print("Tiempo medio: %f" % np.mean(tiempos))
    print("MSE de entrenamiento: %f +- %f" % (np.mean(train_mses), np.std(train_mses)))
    print("MSE de test: %f +- %f" % (np.mean(test_mses), np.std(test_mses)))
    print("CCR de entrenamiento: %.2f%% +- %.2f%%" % (np.mean(train_ccrs), np.std(train_ccrs)))
    print("CCR de test: %.2f%% +- %.2f%%" % (np.mean(test_ccrs), np.std(test_ccrs)))


def entrenar_rbf(train_file, test_file, classification, ratio_rbf, l2, eta, outputs, matrix_m):
    """ Modelo de aprendizaje supervisado mediante red neuronal de tipo RBF.
        Una única ejecución.
        Recibe los siguientes parámetros:
            - train_file: nombre del fichero de entrenamiento.
            - test_file: nombre del fichero de test.
            - classification: True si el problema es de clasificacion.
            - ratio_rbf: Ratio (en tanto por uno) de neuronas RBF con
              respecto al total de patrones.
            - l2: True si queremos utilizar L2 para la Regresión Logística.
              False si queremos usar L1 (para regresión logística).
            - eta: valor del parámetro de regularización para la Regresión
              Logística.
            - outputs: número de variables que se tomarán como salidas
              (todas al final de la matriz).
        Devuelve:
            - train_mse: Error de tipo Mean Squared Error en entrenamiento.
              En el caso de clasificación, calcularemos el MSE de las
              probabilidades predichas frente a las objetivo.
            - test_mse: Error de tipo Mean Squared Error en test.
              En el caso de clasificación, calcularemos el MSE de las
              probabilidades predichas frente a las objetivo.
            - train_ccr: Error de clasificación en entrenamiento.
              En el caso de regresión, devolvemos un cero.
            - test_ccr: Error de clasificación en test.
              En el caso de regresión, devolvemos un cero.
    """
    train_inputs, train_outputs, test_inputs, test_outputs = lectura_datos(train_file, test_file, outputs)

    num_rbf = int(np.size(train_inputs, 0) * ratio_rbf)
    # TODO: Obtener num_rbf a partir de ratio_rbf
    print("Número de RBFs utilizadas: %d" % (num_rbf))
    kmedias, distancias, centros = clustering(classification, train_inputs,
                                              train_outputs, num_rbf)

    radios = calcular_radios(centros, num_rbf)

    '''
        Los pesos de la capa de salida los ajustaremos de dos formas, dependiendo de si estamos ante un problema de 
        clasiﬁcacion o de regresion. Si el problema es de clasiﬁcacion, los pesos se ajustaran utilizando regresion logıstica. 
        Si el problema es de regresion, los pesos se ajustaran utilizando la pseudo-inversa.
        En ambos casos, necesitaremos la matriz de salidas de las RBF, que llamaremos R:
    '''
    matriz_r = calcular_matriz_r(distancias, radios)
    if not classification:
        coeficientes = invertir_matriz_regresion(matriz_r, train_outputs)
    else:
        logreg = logreg_clasificacion(matriz_r, train_outputs, eta, l2)

    """
    TODO: Calcular las distancias de los centroides a los patrones de test
          y la matriz R de test
    """
    distancias_test = distance.cdist(test_inputs, centros, metric='euclidean')
    matriz_r_test = calcular_matriz_r(distancias_test, radios)

    if not classification:
        # MSE en train y test
        matriz_y_estimada_train = np.dot(matriz_r, coeficientes)
        matriz_y_estimada_test = np.dot(matriz_r_test, coeficientes)
        train_mse = mean_squared_error(train_outputs, matriz_y_estimada_train)
        test_mse = mean_squared_error(test_outputs, matriz_y_estimada_test)

        train_ccr = accuracy_score(matriz_y_estimada_train.round(), train_outputs.round()) * 100
        test_ccr = accuracy_score(matriz_y_estimada_test.round(), test_outputs.round()) * 100

    else:
        """
        TODO: Obtener las predicciones de entrenamiento y de test y calcular
              el CCR. Calcular también el MSE, comparando las probabilidades 
              obtenidas y las probabilidades objetivo
        """
        # CCR en train y test
        train_ccr = logreg.score(matriz_r, train_outputs) * 100
        test_ccr = logreg.score(matriz_r_test, test_outputs) * 100

        # MSE en train y test
        # Notacion 1 de Q binarizando los label de test outputs con las clases de logreg
        # Notacion 1 de Q binarizando los label de train outputs con las clases de logreg
        # Example: label_binarize(['yes', 'no', 'no', 'yes'], classes=['no', 'yes'])
        # Result array([[1],[0],[0], [1]])

        encoder = OneHotEncoder(categories='auto')#Transformar a arrays de 1 dimension
        train_outputs_binarized = encoder.fit_transform(train_outputs).toarray()
        test_outputs_binarized = encoder.fit_transform(test_outputs).toarray()

        train_mse = mean_squared_error(y_true=train_outputs_binarized, y_pred=logreg.predict_proba(matriz_r))
        test_mse = mean_squared_error(y_true=test_outputs_binarized, y_pred=logreg.predict_proba(matriz_r_test))
        # Matriz de confusión

        matrix_confusion = confusion_matrix(test_outputs, logreg.predict(matriz_r_test))
        print(matrix_confusion)

    return train_mse, test_mse, train_ccr, test_ccr


def lectura_datos(fichero_train, fichero_test, outputs):
    """ Realiza la lectura de datos.
        Recibe los siguientes parámetros:
            - fichero_train: nombre del fichero de entrenamiento.
            - fichero_test: nombre del fichero de test.
            - outputs: número de variables que se tomarán como salidas
              (todas al final de la matriz).
        Devuelve:
            - train_inputs: matriz con las variables de entrada de
              entrenamiento.
            - train_outputs: matriz con las variables de salida de
              entrenamiento.
            - test_inputs: matriz con las variables de entrada de
              test.
            - test_outputs: matriz con las variables de salida de
              test.
    """
    train = pd.read_csv(fichero_train, header=None).to_numpy()
    test = pd.read_csv(fichero_test, header=None).to_numpy()

    return train[:, :-outputs], train[:, -outputs:], test[:, :-outputs], test[:, -outputs:]


def inicializar_centroides_clas(train_inputs, train_outputs, num_rbf):
    """ Inicializa los centroides para el caso de clasificación.
        Debe elegir los patrones de forma estratificada, manteniendo
        la proporción de patrones por clase.
        Recibe los siguientes parámetros:
            - train_inputs: matriz con las variables de entrada de
              entrenamiento.
            - train_outputs: matriz con las variables de salida de
              entrenamiento.
            - num_rbf: número de neuronas de tipo RBF.
        Devuelve:
            - centroides: matriz con todos los centroides iniciales
                          (num_rbf x num_entradas).
    """

    # Particiones estratificadas de num_rbf/clases elementos
    stratified_split = StratifiedShuffleSplit(n_splits=1, train_size=num_rbf, test_size=None)
    splits = list(stratified_split.split(train_inputs, train_outputs))[0][0]
    return train_inputs[splits]


def clustering(clasificacion, train_inputs, train_outputs, num_rbf):
    """ Realiza el proceso de clustering. En el caso de la clasificación, se
        deben escoger los centroides usando inicializar_centroides_clas()
        En el caso de la regresión, se escogen aleatoriamente.
        Recibe los siguientes parámetros:
            - clasificacion: True si el problema es de clasificacion.
            - train_inputs: matriz con las variables de entrada de
              entrenamiento.
            - train_outputs: matriz con las variables de salida de
              entrenamiento.
            - num_rbf: número de neuronas de tipo RBF.
        Devuelve:
            - kmedias: objeto de tipo sklearn.cluster.KMeans ya entrenado.
            - distancias: matriz (num_patrones x num_rbf) con la distancia
              desde cada patrón hasta cada rbf.
            - centros: matriz (num_rbf x num_entradas) con los centroides
              obtenidos tras el proceso de clustering.
    """

    # TODO: Completar el código de la función
    if clasificacion == True:
        centros = inicializar_centroides_clas(train_inputs, train_outputs, num_rbf)
        kmedias = KMeans(n_clusters=num_rbf, init=centros, n_init=1, max_iter=300, n_jobs=-1)
    else:
        # Obtenemos num_brf numeros aleatorios
        kmedias = KMeans(n_clusters=num_rbf, init='random', max_iter=300, n_jobs=-1)

    # Aqui tenemos la matriz de distancias
    distancias = kmedias.fit_transform(train_inputs)

    # Aqui tenemos los centros
    centros = kmedias.cluster_centers_
    return kmedias, distancias, centros


def calcular_radios(centros, num_rbf):
    """ Calcula el valor de los radios tras el clustering.
        Recibe los siguientes parámetros:
            - centros: conjunto de centroides.
            - num_rbf: número de neuronas de tipo RBF.
        Devuelve:
            - radios: vector (num_rbf) con el radio de cada RBF.
    """
    # Matriz de distancias, Este método toma una matriz de vectores o una
    # matriz de distancias, y devuelve una matriz de distancias.
    # Este método proporciona una forma segura de tomar una matriz de distancia
    # Si se proporciona Y (el valor predeterminado es Ninguno),
    # la matriz devuelta es la distancia por pares entre las matrices de X e Y.

    matriz_distancias = pairwise_distances(centros, Y=None, metric="euclidean")

    # Radios = suma de de todas las filas dividido entre dos por el numero de rbf -1:
    # sum(filas)/ 2 * num_rbf-1
    # axis=1 son las filas
    radios = matriz_distancias.sum(axis=1) / (2 * (num_rbf - 1))
    return radios


def calcular_matriz_r(distancias, radios):
    """ Devuelve el valor de activación de cada neurona para cada patrón
        (matriz R en la presentación)
        Recibe los siguientes parámetros:
            - distancias: matriz (num_patrones x num_rbf) con la distancia
              desde cada patrón hasta cada rbf.
            - radios: array (num_rbf) con el radio de cada RBF.
        Devuelve:
            - matriz_r: matriz (num_patrones x (num_rbf+1)) con el valor de
              activación (out) de cada RBF para cada patrón. Además, añadimos
              al final, en la última columna, un vector con todos los
              valores a 1, que actuará como sesgo.
    """
    # Vamos mirando cada distancia con el radio y asi vamos viendo
    # Si la distancia es mayor que el radio entonces la salida de la neurona es 0
    # Mientras que si la distancia es menor que el radio, la salida será 1

    sesgo = np.ones(distancias.shape[0])
    matriz_r = np.exp(-np.square(distancias) / (np.square(radios) * 2))
    # Añadimos el sesgo apilando en columna con column_stack
    matriz_r = np.column_stack((matriz_r, sesgo))

    return matriz_r


def invertir_matriz_regresion(matriz_r, train_outputs):
    """ Devuelve el vector de coeficientes obtenidos para el caso de la
        regresión (matriz beta en las diapositivas)
        Recibe los siguientes parámetros:
            - matriz_r: matriz (num_patrones x (num_rbf+1)) con el valor de
              activación (out) de cada RBF para cada patrón. Además, añadimos
              al final, en la última columna, un vector con todos los
              valores a 1, que actuará como sesgo.
            - train_outputs: matriz con las variables de salida de
              entrenamiento.
        Devuelve:
            - coeficientes: vector (num_rbf+1) con el valor del sesgo y del
              coeficiente de salida para cada rbf.
    """
    # Step 3:
    # Apply pseudo-inverse

    # TODO:
    # Compute the (Moore-Penrose) pseudo-inverse of a matrix.
    # Calculate the generalized inverse of a matrix using its singular-value decomposition (SVD) and including all large singular values.

    # TODO:
    # Dot product of two arrays. Specifically
    # This operation gives the transpose
    coeficientes = np.dot(np.dot(np.linalg.pinv(np.dot(matriz_r.T, matriz_r)), matriz_r.T), train_outputs)

    return coeficientes


def logreg_clasificacion(matriz_r, train_outputs, eta, l2):
    """ Devuelve el objeto de tipo regresión logística obtenido a partir de la
        matriz R.
        Recibe los siguientes parámetros:
            - matriz_r: matriz (num_patrones x (num_rbf+1)) con el valor de
              activación (out) de cada RBF para cada patrón. Además, añadimos
              al final, en la última columna, un vector con todos los
              valores a 1, que actuará como sesgo.
            - train_outputs: matriz con las variables de salida de
              entrenamiento.
            - eta: valor del parámetro de regularización para la Regresión
              Logística.
            - l2: True si queremos utilizar L2 para la Regresión Logística.
              False si queremos usar L1.
        Devuelve:
            - logreg: objeto de tipo sklearn.linear_model.LogisticRegression ya
              entrenado.
    """

    # TODO: Completar el código de la función
    # Penalty sed to specify the norm used in the penalization
    if l2:
        logreg = LogisticRegression(penalty='l2', C=1 / eta, fit_intercept=False, multi_class='auto',
                                    solver='liblinear', max_iter=500)
    else:
        logreg = LogisticRegression(penalty='l1', C=1 / eta, fit_intercept=False, multi_class='auto',
                                    solver='liblinear', max_iter=500)

    # Entrenated model
    if train_outputs.shape[1] == 1:
        train_outputs = np.ravel(train_outputs)
    logreg.fit(matriz_r, train_outputs)

    return logreg


if __name__ == "__main__":
    entrenar_rbf_total()