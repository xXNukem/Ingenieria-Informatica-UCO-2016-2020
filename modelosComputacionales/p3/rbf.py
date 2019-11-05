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

@click.command()

#Parametros obligatorios
@click.option('--train_file', '-t', default=None, required=True,
              help=u'Fichero con los datos de entrenamiento.')

@click.option('--test_file', '-T', default=None, required=True,
              help=u'Fichero con los datos de test.')

@click.option('--classification', '-c', default=0, required=False,
              help=u'Booleano que indica si es clasificacion o regresion(Por defecto regresion).')

@click.option('--ratio_rbf', '-rb', default=None, required=False,
              help=u'Fichero con los datos de entrenamiento.')

@click.option('--eta', '-e', default=1*math.exp(-2), required=False,
              help=u'Valor del parametro eta (n). por defecto 1e^-2')

@click.option('--outputs', '-o', default=1, required=False,
              help=u'Numero de columnas de salida (por defecto 1).')



def entrenar_rbf_total(train_file, test_file, classification, ratio_rbf, l2, eta, outputs, model_file, pred):
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
            entrenar_rbf(train_file, test_file, classification, ratio_rbf, l2, eta, outputs, \
                         model_file and "{}/{}.pickle".format(model_file, s // 100) or "")
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

    # # # # KAGGLE # # # #
    if model_file != "":
        save_obj = {
            'classification': classification,
            'radios': radios,
            'kmedias': kmedias
        }
        if not classification:
            save_obj['coeficientes'] = coeficientes
        else:
            save_obj['logreg'] = logreg

        dir = os.path.dirname(model_file)
        if not os.path.isdir(dir):
            os.makedirs(dir)

        with open(model_file, 'wb') as f:
            pickle.dump(save_obj, f)

    # # # # # # # # # # #

    if not classification:
        """
        TODO: Obtener las predicciones de entrenamiento y de test y calcular
              el MSE
        """
    else:
        """
        TODO: Obtener las predicciones de entrenamiento y de test y calcular
              el CCR. Calcular también el MSE, comparando las probabilidades 
              obtenidas y las probabilidades objetivo
        """

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

    print('Train inputs')
    print(train_inputs)
    print('Train_outputs')
    print(train_outputs)


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
    return kmedias, distancias, centros

def calcular_radios(centros, num_rbf):
    """ Calcula el valor de los radios tras el clustering.
        Recibe los siguientes parámetros:
            - centros: conjunto de centroides.
            - num_rbf: número de neuronas de tipo RBF.
        Devuelve:
            - radios: vector (num_rbf) con el radio de cada RBF.
    """

    #TODO: Completar el código de la función
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
