% Funci�n igual a la anterior, salvo que en vez de recibir un texto, recibe ya los bloques de n�meros. 
% Entradas:   
% e y n: clave p�blica para el cifrado RSA. 
% blo: vector de n�meros. 
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