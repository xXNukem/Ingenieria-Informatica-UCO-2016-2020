% Se deben proporcionar los datos comunes a A y a B: el valor del primo y el valor del generador, 
% el programa debe comprobar que se cumplen estas condiciones. El programa generará tanto 
% para A como para B sus respectivos números aleatorios, nos indicará cuáles son las potencias que se envían, 
% y como tanto A como B obtienen la clave 
% común a partir de los valores obtenidos por el contrario.
function diffieHellman(g, p)

if genera(g,p) ~= 0 %Verificar generador
    
    %A y B aleatorios
    randA = randi([1 p-1]);
    fprintf('A genera el numero aleatorio A: %d\n', randA);
    randB = randi([1 p-1]);
    fprintf('B genera el numero aletorio B: %d\n\n', randB);
    
    %CLAVES
    pote_a = potencia(g, randA, p);
    fprintf('A envia a B el producto: %d\n', pote_a);
    pote_b = potencia(g, randB, p);
    fprintf('B envia a A el producto: %d\n\n', pote_b);
    
    %CALCULO DE LAS CLAVES PARA CIFRAR
    
    claveA = potencia(pote_b, randA, p);
    fprintf('A calcula la clave: %d\n', claveA);
    claveB = potencia(pote_a, randB, p);
    fprintf('B calcula la clave %d\n\n', claveB);
    
else
   fprint('Los parametros pasados no son generadores');
end