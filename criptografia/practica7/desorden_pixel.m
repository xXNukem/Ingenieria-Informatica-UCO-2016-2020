% Función que desordena los píxeles de las matrices asociadas a una imagen, foto, 
% de acuerdo a la transformación asociada a la matriz A. No queremos que nos muestre nada, 
% ni imágenes ni matrices, sólo que guarde las matrices obtenidas para usarlas en otras funciones.
% Para ello se puede usar setappdata (gcf, 'matriz', matriz), y cuando más adelante necesitemos usar esa matriz, 
% matriz = getappdata (gcf, 'matriz').
% Entradas:  foto: la foto de la que queremos desordenar sus píxeles. Debe ser cuadrada.
% A: matriz que nos determina la transformación. Debe ser 2x2 y tener inversa módulo el número 
% de filas de foto.Salidas: Ninguna. Debe guardar las nuevas matrices obtenidas para un posible uso posterior.

function desorden_pixel(foto,A)

    matrizCopia=imread(foto);
    [filas, columnas, capas]=size(matrizCopia); %La variable capas al final no la uso pero la dejo porsi hago algo luego
    [f,c]=size(A);
    
    [G,U,V]=gcd(round(det(A)),filas);
    
        if f~=c || f~=2 || c~=2 || G~=1 %Comprobaciones de validez de la matriz
            disp('Matriz A invalida')
            return
        end
    
    for i=1:filas
        for j=1:columnas %Recorrer la matriz DE LA FOTO e intercambiar los pixels
            
            coord = mod(A*[i;j], filas); %Hay que usar el modulo para llevar los pixeles a sitios que no se salgan del tamaño
            x=coord(1);
            y=coord(2);
            
            if(x==0)
                x=filas;
            end
            if(y==0)
                y=columnas;
            end
            
            %se intercambia los pixeles
            matrizCopia2(x,y,:)=matrizCopia(i,j,:);
            
        end
        
    end
    matrizCopia2=uint8(matrizCopia2);
    subplot(1,2,1);imshow(foto);
    imwrite(matrizCopia2,'pruebafoto.bmp');
    subplot(1,2,2);imshow('pruebafoto.bmp');
    %setappdata(gcf, 'imagenDesordenada', matrizCopia);
end