% Función para cifrar un texto a partir de una permutación con el cifrado Hill en caso de ser posible,
% y un mensaje de error por lo contrario.
% Entradas:
% p: vector que debe ser una permutación. El programa debe comprobarlo.
% texto: el texto llano a cifrar.
% Salida: El texto cifrado usando Hill y la permutación si es posible, o un mensaje de error
% en caso contrario.
function [texto, cifrado] = cifro_permutacion(p, texto)

%Comprobar si la matriz de la permutacion es valida
if permutacion_v(p) == 1

    A = mapter(p);%Matriz de la permutacion
    
    %Se coge la matriz de la permutacion y se hace un hill
    d = size(A, 1);

    
    numeros = letranumero(texto);%Se comprueba si el texto es divisible entre el numero de filas y columas de a y sino se le mete ruido
    a = mod(length(numeros), d);
    if(a ~= 0)
        for i=1:(d-a)
           numeros = [numeros, 23]; %Se mete w como ruido
        end
    end
    
    %Concatenar y pasar a letra
    X = reshape(numeros, d, []);
    Y = mod(A*X, 27);

    cifrado = reshape(Y, 1, []);

    %Con esto ya deberiamos de tener el texto cifrado
    cifrado = numeroletra(cifrado);
        
else
    error('ErrorTests:convertTest','Permutacion no valida')
end