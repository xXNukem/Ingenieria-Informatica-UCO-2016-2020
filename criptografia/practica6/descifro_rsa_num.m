% Función que aplica la función de descifrado del método RSA a un vector numérico (que supuestamente se habrá cifrado previamente con la clave pública), utilizando la clave privada proporcionada. 
% Entradas:   
% (d, n): clave privada. 
% cifrado_numero: vector numérico, se supone que cifrados según la clave pública con RSA. 
% Salida: descifro_num: vector numérico obtenidos tras aplicar la función de descifrado con RSA
function descifro_num = descifro_rsa_num(d, n, cifrado_numeros)
descifro_num = [];
for i=1:length(cifrado_numeros)
   descifro_num = [descifro_num, potencia(cifrado_numeros(i), d, n)]; %Potencia con clave privada
end