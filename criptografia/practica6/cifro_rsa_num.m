function cifrado=cifro_rsa_num(e, n, bloque)
%Recibimos directamente un bloque de numeros asi que nos ahorramos lo de
%antes casi todo
aux = num2str(n);
cifrado = [];
    for i=1:length(bloque)
        cifrado = [cifrado, potencia(bloque(i), e, n)];
    end
end