% Función que debe hacer los siguientes pasos: pasar texto a una cadena numérica usando 2 dígitos por letra, calcular el tamaño de los bloques a partir de n, aplicar la función anterior para obtener los bloques de números, y cifrarlos según el sistema RSA usando la clave pública (n,e). 
% Entradas:   
% e y n: clave pública para el cifrado RSA. 
% texto: texto que queremos cifrar. 
% Salida: cifrado: vector formado por los bloques ya cifrados
function cifrado=cifro_rsa(e, n, texto)

bloque = letra2numeros(texto);%texto a numeros de dos digitos
aux = num2str(n);
tama = length(aux) -1;%obtenemos el tamaÃ±o
blo = prepa_num_cifrar(tama, bloque);
cifrado = [];
    for i=1:length(blo)
        cifrado = [cifrado, potencia(blo(i), e, n)];
    end
end