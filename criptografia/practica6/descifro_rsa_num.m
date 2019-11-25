% Funci�n que aplica la funci�n de descifrado del m�todo RSA a un vector num�rico (que supuestamente se habr� cifrado previamente con la clave p�blica), utilizando la clave privada proporcionada. 
% Entradas:   
% (d, n): clave privada. 
% cifrado_numero: vector num�rico, se supone que cifrados seg�n la clave p�blica con RSA. 
% Salida: descifro_num: vector num�rico obtenidos tras aplicar la funci�n de descifrado con RSA
function descifro_num = descifro_rsa_num(d, n, cifrado_numeros)
descifro_num = [];
for i=1:length(cifrado_numeros)
   descifro_num = [descifro_num, potencia(cifrado_numeros(i), d, n)]; %Potencia con clave privada
end