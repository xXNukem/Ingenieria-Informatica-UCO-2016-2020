function cifradoafin = afin(clave, d, texto)
numero = letranumero(texto);
cifradoafin = [];
clave = floor(clave);
d = floor(d); %La funcion floor rendondea al entero mas cercano
alfabeto = 'abcdefghijklmnnopqrstuvwxyz';
alfabeto(15) = char(241);

if gcd(clave, length(alfabeto)) == 1
    
    numero = numero * clave + d;
    numero = mod(numero, length(alfabeto));

    cifradoafin = numeroletra(numero);
else
    error('ErrrorTest:convertTest', 'El MCD de la clave y el tamaño del alfabeto debe ser 1')
    
    
end