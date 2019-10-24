function [cifrado, llano] = descifro_permutacion(p, cifrado)

%Hay que pasarle la inversa al cifrado hill

if permutacion_v(p) == 1
    A = matper(p);
    A = inv_modulo(A, 27);
    
    d = size(A, 1);
        %Pasamos el texto a numeros y lo dividimos en grupos
        numeros = letranumero(cifrado);
        X = reshape(numeros, d, []);
        Y = mod(A*X, 27);
        %Ahora tenemos que concatenar las columnas y pasarlo a letra

        llano = reshape(Y, 1, []);

        %Con esto ya deberiamos de tener el texto cifrado
        llano = numeroletra(claro);
else
    error('ErrorTests:convertTest','Permutacion no valida')
end