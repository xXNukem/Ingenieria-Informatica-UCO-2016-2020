% 
% Funci�n que debe calcular el m�nimo valor del exponente de la potencia de A que m�dulo m es
% igual a la matriz identidad.
% Entradas:
% A: matriz (cuadrada de orden 2 y con inversa m�dulo m).
% m: m�dulo de trabajo.
% Salida: El valor del exponente que hace que la correspondiente potencia de A sea la
% identidad.

function n = pote(A,m)

[filasA, columA] = size(A);
if filasA == 2 && columA == 2 %Si la matriz no es de 2 por 2 fuera
    I = [1 0;0 1];
    n = 1;
    auxA = A;
    while ~isequal(auxA, I)
        auxA = mod(auxA*A, m);
        n = n+1;

    end
else
   disp('Matriz de entrada incorrecta'); 
end