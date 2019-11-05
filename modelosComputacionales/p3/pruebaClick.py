import click
import pandas as pd
@click.command()

#Parametros obligatorios
@click.option('--train_file', '-t', default=None, required=True,
              help=u'Fichero con los datos de entrenamiento.')

@click.option('--test_file', '-T', default=None, required=True,
              help=u'Fichero con los datos de test.')
@click.option('--outputs', '-o', default=1, required=False,help=u'Numero de columnas de salida (por defecto 1).')

def lectura_datos(train_file, test_file, outputs):


    train = pd.read_csv(train_file, header=None)
    test = pd.read_csv(test_file, header=None)

    train_inputs = train.values[:, -outputs]
    train_outputs = train.values[:, 0:-outputs]
    test_inputs = test.values[:, -outputs]
    test_outputs = test.values[:, 0:-outputs]



lectura_datos()