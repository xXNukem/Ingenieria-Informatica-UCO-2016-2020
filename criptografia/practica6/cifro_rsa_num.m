% Función igual a la anterior, salvo que en vez de recibir un texto, recibe ya los bloques de números. 
% Entradas:   
% e y n: clave pública para el cifrado RSA. 
% blo: vector de números. 
% Salida: cifrado: vector formado por los bloques introducidos ya cifrados.
function cifrado=cifro_rsa_num(e, n, bloque)
%Recibimos directamente un bloque de numeros asi que nos ahorramos lo de
%antes casi todo
aux = num2str(n);
cifrado = [];
    for i=1:length(bloque)
        cifrado = [cifrado, potencia(bloque(i), e, n)];
    end
end