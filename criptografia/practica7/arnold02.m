
% Funci�n que debe desordenar los p�xeles de la imagen foto seg�n la matriz A, de manera
% sucesiva. Vamos a usar un switch con dos casos: caso 1 para desordenar hasta recuperar la
% imagen original y caso 2 para desordenar el n�mero de veces que se indique.
% Entradas:
% foto: foto que queremos desordenar.
% A: matriz que determina la transformaci�n.
% Salida: potencia: el n�mero de veces que hemos realizado la transformaci�n de forma
% sucesiva. Adem�s, en ambos casos debe mostrar la imagen original y todas las im�genes
% transformadas que se hayan ido realizando.
function potencia = arnol_02(foto, A)
[filasA, columA] = size(A);
if filasA == 2 && columA == 2
    matrizFoto = imread(foto);
    [filasFoto, columFoto, capas] = size(matrizFoto);
    if filasFoto ~= columFoto %Las filas tienen que ser del mismo tama�o que las cols de la foto
        %Recortamos la foto
        if columFoto <filasFoto
            nuevaFoto = matrizFoto(1:columFoto, 1:columFoto, 1:3);
        else
            nuevaFoto = matrizFoto(1:filasFoto, 1:filasFoto, 1:3);
        end
    else
        nuevaFoto = matrizFoto;
    end

opcion = input('1-Desordenar hasta recuperar 2-Desordenar lo que se diga: ');
switch opcion
    case 1
       potencia = pote(A, filasFoto); %Potencia A= Numero de veces de desordenar
       %Le pedimos al usuario el numero de veces que quiere desordenar
       potencia %La voy a dejar mostrandose de mientras
       usuario = input('Numer de veces que quieres desordenar(tiene que ser menor que la potencia)')
       auxFoto = nuevaFoto;
       for i=1:potencia-usuario
           desorden_pixel(auxFoto, A)
           auxFoto = getappdata(gcf, 'imagenDesordenada'); %agarrar la imagen de fuera
       end
       imshow(auxFoto);
       imwrite(auxFoto, 'FotoOrdenadaArnol2.bmp')
    case 2
        salir = 1;
        auxFoto = nuevaFoto;
        potencia = 1;
        while salir~=0
            %Desordenar y mostrar, 1 seguir desordenando 0 parar
            desorden_pixel(auxFoto, A);
            potencia = potencia +1;
            auxFoto = getappdata(gcf, 'imagenDesordenada');
            imshow(auxFoto);
            salir = input('1 seguir, 0 parar: ');
        end
        imwrite(auxFoto, 'FotoOrdenadaArnol2.bmp')
        
end
end