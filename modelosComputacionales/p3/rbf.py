#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Wed Oct 28 12:37:04 2016

@author: pagutierrez
"""

# TODO Incluir todos los import necesarios
import pickle
import os
import pandas as pd
import click as click
import math
import numpy as np
import pandas as pd
import random
from scipy.spatial import distance
from sklearn.cluster import KMeans
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import mean_squared_error
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score

@click.command()

#Parametros obligatorios
@click.option('--train_file', '-t', default=None, required=True, help=u'Fichero con los datos de entrenamiento.')
@click.option('--test_file', '-T', default=None, required=True, help=u'Fichero con los datos de test.')
@click.option('--classification', '-c', default=0, is_Flag=True, help=u'Booleano clasificacion o regresion')
@click.option('--ratio_rbf', '-rb', default=0.1, required=False, help=u'Fichero con los datos de entrenamiento.')
@click.option('--eta', '-e', default=1*math.exp(-2), required=False, help=u'parametro eta (n). por defecto 1e^-2')
@click.option('--outputs', '-o', default=1, required=False, help=u'Numero de columnas de salida (por defecto 1).')

def entrenar_rbf_total(train_file, test_file, classification, ratio_rbf, l2, eta, outputs):
    """ Modelo de aprendizaje supervisado mediante red neuronal de tipo RBF.
        Ejecución de 5 semillas.
    """

    if train_file is None:
        print("No se ha especificado el conjunto de entrenamiento (-t)")
        return

    train_mses = np.empty(5)
    train_ccrs = np.empty(5)
    test_mses = np.empty(5)
    test_ccrs = np.empty(5)

    for s in range(1, 6, 1):
        print("-----------")
        print("Semilla: %d" % s)
        print("-----------")
        np.random.seed(s)
        train_mses[s - 1], test_mses[s - 1], train_ccrs[s - 1], test_ccrs[s - 1] = \
            entrenar_rbf(train_file, test_file, classification, ratio_rbf, l2, eta, outputs)
        print("MSE de entrenamiento: %f" % train_mses[s - 1])
        print("MSE de test: %f" % test_mses[s - 1])
        print("CCR de entrenamiento: %.2f%%" % train_ccrs[s - 1])
        print("CCR de test: %.2f%%" % test_ccrs[s - 1])

    print("*********************")
    print("Resumen de resultados")
    print("*********************")
    print("MSE de entrenamiento: %f +- %f" % (np.mean(train_mses), np.std(train_mses)))
    print("MSE de test: %f +- %f" % (np.mean(test_mses), np.std(test_mses)))
    print("CCR de entrenamiento: %.2f%% +- %.2f%%" % (np.mean(train_ccrs), np.std(train_ccrs)))
    print("CCR de test: %.2f%% +- %.2f%%" % (np.mean(test_ccrs), np.std(test_ccrs)))


def entrenar_rbf(train_file, test_file, classification, ratio_rbf, l2, eta, outputs, model_file=""):
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
    train_inputs, train_outputs, test_inputs, test_outputs = lectura_datos(train_file,
                                                                           test_file,
                                                                           outputs)

    #TODO: Obtener num_rbf a partir de ratio_rbf
    # Solo hay una capa de entrada con tantas neuronas como entradas tiene la base de datos
    num_rbf = int(np.size(train_inputs, 0) * ratio_rbf)

    print("Número de RBFs utilizadas: %d" %(num_rbf))
    kmedias, distancias, centros = clustering(classification, train_inputs,
                                              train_outputs, num_rbf)
    
    radios = calcular_radios(centros, num_rbf)
    
    matriz_r = calcular_matriz_r(distancias, radios)

    if not classification:
        coeficientes = invertir_matriz_regresion(matriz_r, train_outputs)
    else:
        logreg = logreg_clasificacion(matriz_r, train_outputs, eta, l2)

    """
    TODO: Calcular las distancias de los centroides a los patrones de test
          y la matriz R de test
    """
    distancias_test = calcular_distancias(test_inputs, centros, num_rbf)
    matriz_r_test = calcular_matriz_r(distancias_test, radios)

    if not classification:
        """
        TODO: Obtener las predicciones de entrenamiento y de test y calcular
              el MSE
        """
        matriz_y_estimada_train = np.dot(matriz_r, coeficientes)
        matriz_y_estimada_test = np.dot(matriz_r_test, coeficientes)
        train_mse = mean_squared_error(train_outputs, matriz_y_estimada_train)
        test_mse = mean_squared_error(test_outputs, matriz_y_estimada_test)
        train_ccr = 0
        test_ccr = 0
    else:
        """
        TODO: Obtener las predicciones de entrenamiento y de test y calcular
              el CCR. Calcular también el MSE, comparando las probabilidades 
              obtenidas y las probabilidades objetivo
        """
        train_ccr = logreg.score(matriz_r, train_outputs) * 100
        test_ccr = logreg.score(matriz_r_test, test_outputs) * 100

        train_predict = logreg.predict(matriz_r)
        test_predict = logreg.predict(matriz_r_test)
        train_mse = mean_squared_error(train_predict, train_outputs)
        test_mse = mean_squared_error(test_predict, test_outputs)

        matriz_confusion = confusion_matrix(test_outputs, test_predict)

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
    train = pd.read_csv(fichero_train, header=None)
    test = pd.read_csv(fichero_test, header=None)

    train_inputs = train.values[:, -outputs]
    train_outputs = train.values[:, 0:-outputs]
    test_inputs = test.values[:, -outputs]
    test_outputs = test.values[:, 0:-outputs]

    return train_inputs, train_outputs, test_inputs, test_outputs

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
    
    #TODO: Completar el código de la función

    num_clases = np.unique(train_outputs).shape[0]
    num_entradas = train_inputs.shape[1]
    centroides = np.empty([num_rbf, num_entradas])
    clases = np.empty([num_rbf])

    for i in range(num_rbf):
        j = i % num_clases
        clases[i] = np.unique(train_outputs)[j]

    for i in range(num_rbf):
        # Metemos 'num_rbf' patrones en la matriz centroides
        while 1:
            rand = random.randint(0, train_outputs.shape[0] - 1)
            if train_outputs[rand] == clases[i]:
                centroides[i] = train_inputs[rand]
                np.delete(train_inputs, [rand])
                np.delete(train_outputs, [rand])
                break

    return centroides


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

    #TODO: Completar el código de la función

    if clasificacion == True:
        centros = inicializar_centroides_clas(train_inputs, train_outputs, num_rbf)
        kmedias = KMeans(n_clusters=num_rbf, init=centros, n_init=1, max_iter=500)
    else:
        # Obtenemos num_brf numeros aleatorios
        kmedias = KMeans(n_clusters=num_rbf, init='random', max_iter=500)

    kmedias.fit(train_inputs, train_outputs)

    centros = kmedias.cluster_centers_

    # Ahora vamos a calcular las distancias de cada patron a su cluster mas cercano
    distancias = calcular_distancias(train_inputs, centros, num_rbf)

    return kmedias, distancias, centros


def calcular_distancias(inputs, centros, num_rbf):
    distancias = np.empty([inputs.shape[0], num_rbf])
    for i in range(0, inputs.shape[0]):
        for j in range(0, centros.shape[0]):
            # Calculamos la matriz distancia euclidea de cada patron para cada rbf
            distancias[i, j] = distance.euclidean(inputs[i, :], centros[j, :])
    return distancias


def calcular_radios(centros, num_rbf):
    """ Calcula el valor de los radios tras el clustering.
        Recibe los siguientes parámetros:
            - centros: conjunto de centroides.
            - num_rbf: número de neuronas de tipo RBF.
        Devuelve:
            - radios: vector (num_rbf) con el radio de cada RBF.
    """

    #TODO: Completar el código de la función

    radios = np.empty(num_rbf)
    aux = 0.0
    # Para cada elemento de los radios calculamos el radio que será el sumatorio
    for i in range(0, num_rbf):
        for j in range(0, num_rbf):
            if i != j:
                aux += distance.euclidean(centros[i], centros[j])
        radios[i] = aux / (2 * num_rbf - 1)
        aux = 0.0

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

    #TODO: Completar el código de la función
    #+1 es el sesgo, todo el sesogo se pone a 1
    matriz_r = np.empty([distancias.shape[0], distancias.shape[1] + 1])
    matriz_r[:, 0] = 1

    #Distancia>radio ->Salida 0
    #Distancia<radio ->Salida 1
    for i in range(0, matriz_r.shape[0]):
        for j in range(0, matriz_r.shape[1] - 1):
            matriz_r[i][j + 1] = math.exp(-(distancias[i][j] ** 2) / (2 * radios[j] ** 2))

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

    #TODO: Completar el código de la función

    # Matriz de Moore-Penrose
    moore = np.linalg.pinv(matriz_r)

    coeficientes = np.dot(moore, train_outputs)  # Esta operacion lo que nos da es la transpuesta
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

    #TODO: Completar el código de la función
    pen = ''
    if l2 == True:
        pen = 'l2'
    else:
        pen = 'l1'

    logreg = LogisticRegression(penalty=pen, C=1 / eta, fit_intercept=False)
    # En esta habria que pasarle R o los train_inputs, pero claro eso no lo tenemos
    logreg.fit(matriz_r, train_outputs)

    return logreg


def predict(test_file, model_file):
    """ Calcula las predicciones para un conjunto de test que recibe como parámetro. Para ello, utiliza un fichero que
    contiene un modelo guardado.
    :param test_file: fichero csv (separado por comas) que contiene los datos de test.
    :param model_file: fichero de pickle que contiene el modelo guardado.
    :return: las predicciones para la variable de salida del conjunto de datos proporcionado.
    """
    test_df = pd.read_csv(test_file, header=None)
    test_inputs = test_df.values[:, :]

    with open(model_file, 'rb') as f:
        saved_data = pickle.load(f)

    radios = saved_data['radios']
    classification = saved_data['classification']
    kmedias = saved_data['kmedias']

    test_distancias = kmedias.transform(test_inputs)
    test_r = calcular_matriz_r(test_distancias, radios)

    if classification:
        logreg = saved_data['logreg']
        test_predictions = logreg.predict(test_r)
    else:
        coeficientes = saved_data['coeficientes']
        test_predictions = np.dot(test_r, coeficientes)

    return test_predictions


if __name__ == "__main__":
    entrenar_rbf_total()
