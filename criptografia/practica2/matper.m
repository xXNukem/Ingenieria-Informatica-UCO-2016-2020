% Función para comprobar que p es una permutación, y en este caso construir la matriz asociada
% a ella.
% Entrada: El vector que supuestamente debe ser una permutación. El programa debe
% comprobar que lo es.
% Salida: La matriz asociada en caso de que realmente sea una permutación, o un
% mensaje de error en caso contrario.

function mat_per=matper(p)
    if permutacion_v(p) == 1 %Si el vector es una permutacion aceptamos y creamos la matriz asociada
    mat_per = zeros(size(p,2),size(p,2));   
    for i=1:size(p,2)
        mat_per(i,p(i))= 1; %Introducimos 1 segun corresponda evaluando la permutacion
    end
    else
        disp('Error')
    end
end
