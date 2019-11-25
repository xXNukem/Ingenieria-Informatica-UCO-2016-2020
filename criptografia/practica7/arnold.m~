% Función que va a ordenar o a desordenar una foto. Para elegir una de estas dos opciones se debe usar 
% un switch con dos casos: caso 1 para desordenary caso 2 para ordenar.
% Entradas:  foto: fotografía (que debe ser cuadrada), a la que queremos aplicarle una transformación de Arnold. 
% Debe ser la fotografía original en el caso 1, y la fotografía desordenada según la matriz A en el caso 2.
% A: matriz que se va a usar para desordenar en el caso 1, o que ya se ha usado para desordenar en el caso 2. 
% Debe ser una matriz 2x2 con inversa módulo el número de filas de foto.
% Salida: En el caso 1 la imagen desordenada según la transformación indicadapor la matriz A.
% En el caso 2 la matriz ordenada teniendo en cuenta que se desordenóusando la matriz A

function arnold(foto,A)

    MatrizCopia=foto;
    [filas, columnas, capas]=size(foto); %La variable capas al final no la uso pero la dejo porsi hago algo luego
    [f,c]=size(A)
    
    [G,U,V]=gcd(det(A),filas)
    
        if f~=c || f~=2 || c~=2 || G~=1 %Comprobaciones de validez de la matriz
            disp('Matriz A invalida')
            return
        end

    
    
        
end