% Funci�n que debe hacer los siguientes pasos: pasar texto a una cadena num�rica usando 2 d�gitos por letra, calcular el tama�o de los bloques a partir de n, aplicar la funci�n anterior para obtener los bloques de n�meros, y cifrarlos seg�n el sistema RSA usando la clave p�blica (n,e). 
% Entradas:   
% e y n: clave p�blica para el cifrado RSA. 
% texto: texto que queremos cifrar. 
% Salida: cifrado: vector formado por los bloques ya cifrados
function cifrado=cifro_rsa(e, n, texto)

bloque = letra2numeros(texto);%texto a numeros de dos digitos
aux = num2str(n);
tama = length(aux) -1;%obtenemos el tamaño
blo = prepa_num_cifrar(tama, bloque);
cifrado = [];
    for i=1:length(blo)
        cifrado = [cifrado, potencia(blo(i), e, n)];
    end
end