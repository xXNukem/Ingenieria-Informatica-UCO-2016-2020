function des_mmh(s1, cifrado, mu, invw)

%Aplicando lo visto en clase
cifrado = mod(cifrado*invw, mu);
%Descifrar
mensaje = des_mochila(s1, cifrado);