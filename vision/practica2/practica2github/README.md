Unsharp-mask
============

Objetivos de la práctica:
=========================

    Aprender a mejorar una imagen aplicando un realce por máscara de desenfoque (unsharp mask).
    Aprender a procesar una imagen en el domino de la frecuencia.
    Aprender a utilizar la GUI de openCV usando controles con barra de deslizamiento.

Requisitos:
===========

Recuerda que la operación a aplicar es: O = (g+1)·I -g·IL, siendo I la imagen original, IL la versión paso baja de la misma (obtenida mediante 
filtrado en el dominio de la frecuencia con un fitlro butterworth) y g la ganancia del realce.

    La imagen de entrada puede ser monocroma o en color.
    En una imagen en color se debe pasar a un espacio de color HSV y aplicar el realce al plano de iluminación (V) para deshacer el cambio.
    Mediante un parámetro 'r', con valores en intervalo [0, 1] (por defecto 0.5), es proporcionada la frecuencia de corte del filtro como la 
    fracción de la máxima frecuencia.

    Mediante el parámetro 'n', con valores [1,10] (por defecto 2), se proporcionado el orden del filtro butterworth paso baja.
    Mediante el parámetro 'g', con valores [0.0, 5.0] (por defecto 1.0), es proporcionada la ganancia del realce.
    Si se proporciona una máscara, sólo se procesan los puntos activos en la máscara.

    unsharp [-r <float>] [-n <int>] [-g <float>] <input img> <output img> [<mask img>]

Opcional:
=========

    Especificar el espacio de color: HSV, HLS, YCrCb, La*b*. Parámetro -s <int> con valor por defecto 0 (HSV).
    Si es indicado el parámetro '-i' (de interactivo), se debe presentar una ventana con la imagen procesada, con controles por barra de 
    deslizamiento para los parámetros r, n y g. Cuando se cambie algún valor de los mismos se actualizará la imagen de la ventana.

    unsharp [-i] [-s <int>] [-r <float>] [-n <int>] [-g <float>] <input img> <output img> [<mask img>]