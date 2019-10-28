% Función para asegurarnos que la entrada es un vector que de verdad representa una
% permutación de {1, 2, ..., n}.
% Entrada: El vector que queremos comprobar si es o no una permutación.
% Salida:
% permuta=0: si el vector no es una permutación de {1, 2, ..., n}.permuta=1: si el vector es una permutación de {1, 2, ..., n}.
function permutacion = permutacioncion_v(p)
    X = [1:size(p,2)];
    Y = sort(p);
    if X == Y %si al ordenar el vector resulta igual a X es que es una permutacion
        disp('permutacioncion detectada')
        permutacion = 1;
    else
        disp('No es permutacioncion')
        permutacion = 0;
    end
end