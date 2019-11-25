% Funci�n que transforma un vector num�rico en letras (dos d�gitos por letra). Debe completar los bloques para que tengan longitud d�gitos(n)-1, concatenarlos y agrupar de dos en dos, eliminar los posibles 30�s y/o 0 que pueda haber al final, y pasar a letras. 
% Entradas:   
% n: n�mero que va a determinar el tama�o de los bloques, d�gitos(n)-1. 
% bloque_numero: vector num�rico. 
% Salida: desci: cadena alfab�tica con el texto asociado a los bloques de n�meros.
function desci = num_descifra(n, bloque_numero)
%Pasamos ese bloque de numeros a letras

tama = length(num2str(n))-1;
nuevoBloque = [];
for i=1:length(bloque_numero)
    aux = num2str(bloque_numero(i));
    if length(aux) < tama
        while 1
           if mod(length(aux), tama) == 0
               break;
           else
              aux = strcat('0', aux);
           end
        end
    end
    nuevoBloque = [nuevoBloque, aux];
end
%Con esto ya hemos metido los 0s al principio de cada n�mero
%Quitamos el 0 que a�adimos al final, si se a�adi�
if mod(length(nuevoBloque),2) ~= 0
    nuevoBloque = nuevoBloque(1:length(nuevoBloque)-1)';
end
nuevoBloque = reshape(nuevoBloque, 2, [])';%Agrupar de dos en dos
numeros =[];
for i=1:length(nuevoBloque)
   numeros = [numeros, str2num(nuevoBloque(i,:))]; 
end

nuevosNumeros = [];
for i=1:length(numeros)%Quitar 30 al final
   if numeros(i) ~= 30
       nuevosNumeros = [nuevosNumeros, numeros(i)];
   end
end
desci = numeroletra(nuevosNumeros);