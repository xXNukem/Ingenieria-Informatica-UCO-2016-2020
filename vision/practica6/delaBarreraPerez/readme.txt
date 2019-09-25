Ejecutar test

./test_bovw --config_file ../data/02_ObjectCategories_conf.txt --dict ../models/() --classifier ../models/() --img ../data/test/() --video ../data/test/()

Los parámetros img y video no se ponen a la vez

Los parametros de los modelos estan especificados en la talba, por ejemplo 1_SIFTD_classifier y 1_SIFTD_dictionary corresponden a la prueba 1 en la tabla con los parametros alli especificados para el SIFT DENSO.

Ejecutar train

./train_bovw --config_file 02_ObjectCategories_conf.txt
Los demas parametros estan por defecto
