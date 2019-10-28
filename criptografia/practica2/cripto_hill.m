% Función para hallar la matriz clave en el cifrado Hill conociendo parte del texto claro, del
% criptograma y el orden de la matriz, mediante un ataque de tipo Gauss-Jordan.
% Entradas:
% claro: un fragmento de texto llano, de longitud al menos d 2 .
% cripto: el criptograma, o parte de él, de longitud al menos d 2 .
% d: el orden que estamos suponiendo para la matriz clave del cifrado Hill.Salida: la matriz clave del cifrado.

function matrizclave=cripto_hill(textoclaro,textocifrado,orden)
%Pasar a minuscula y a numero
textoclaro = lower(textoclaro);
textoclaro = letranumero(textoclaro);

aux = mod(length(textoclaro), orden);

    if(aux~= 0)
        for i=1:(orden-aux)
            textoclaro = [textoclaro,24]; %Insertar ruido en caso de no caber
        end
    end
    

Y = reshape(letranumero(textocifrado), orden, []);
X = reshape(textoclaro, orden, []);

Y = Y';
X = X';

for i=1:orden 
    aux = X(i,i);
    X;
    Y;
    [G, U, V] = gcd(27, aux);
    %Si el elemento tiene inverso, hacemos 0 tanto en las filas de arriba
    %como en las de abajo.
    %Si no tiene inverso, buscamos uno e intercambiamos filas.
    if G ~= 1
         %Si no tiene inverso, tenemos que buscar el primer numero de las
        %filas de abajo que tenga e intercambiarlo
        for k=i+1:size(X,1)
            [G, U, V] = gcd(27, X(k, i));
            if G == 1
                %ese numero tiene inverso, asi que intercambiamos filas y
                %nos salimos de este bucle
                fila = X(i, :);
                X(i, :) = X(k, :);
                X(k, :) = fila;
                %Ahora lo mismo con la matriz Y
                fila = Y(i, :);
                Y(i, :) = Y(k, :);
                Y(k, :) = fila;
                break
            end
        end
    end
        %Tiene inverso
        X(i, :) = mod(X(i,:)*V, 27);
        Y(i, :) = mod(Y(i,:)*V, 27);
        %Una vez tenemos 1 en el (i,i) Hacemos 0s en la columna i, pero en
        %todas las filas tanto por encima como por debajo
        for j=1:size(X,1)
            if j~=i
                %Hacemos ceros
                aux2 = X(j,i);
                X(j, :) = mod(X(j,:)-aux2*X(i,:),27);
                Y(j, :) = mod(Y(j,:)-aux2*Y(i,:),27);
            end
            
        end
    
end
X;
Y;
%Despues de estas operaciones ya tenemos las dos matrices.
%Ahora cogeremos la matriz clave de la matriz Y
matrizclave = Y(1:orden,1:orden);
matrizclave = matrizclave';

end