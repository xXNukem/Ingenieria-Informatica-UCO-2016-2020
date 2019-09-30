function descifradoafin = desafin(clave, d, texto)
numero = letranumero(texto);
descifradoafin = [];
    alfabeto = 'abcdefghijklmnnopqrstuvwxyz';
    alfabeto(15) = char(241);

if gcd(clave, length(alfabeto)) == 1
   [G, U, V]= gcd(length(alfabeto), clave);%Obtenemos V que hara falta en la desencriptacion
    numero =  V * (numero - d);
    numero = mod(numero, length(alfabeto));
    
else
    error('ErrrorTest:convertTest', 'El MCD de la clave y el alfabeto debe ser 1')
    
end

descifradoafin = numeroletra(numero);