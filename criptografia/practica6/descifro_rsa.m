% Funci�n de descifrado seg�n el m�todo RSA, que siga todos los pasos estudiados. 
% Entradas:   
% (d, n): clave privada. 
% cifrado_numero: vector num�rico, se supone que cifrados seg�n la clave p�blica con RSA. 
% Salida: descifrado: texto claro
function descifrado = descifro_rsa(d, n, cifrado_numeros)
%llamo a las funciones y se acabo
descifro_numeros = descifro_rsa_num(d, n, cifrado_numeros);

descifrado = num_descifra(n, descifro_numeros);

end