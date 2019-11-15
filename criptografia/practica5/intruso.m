% Se deben proporcionar los datos comunes a A y a B: el valor del primo y 
% el valor del generador, el programa debe comprobar que se cumplen estas condiciones.
% El programa generará tanto para A como para B sus respectivos números aleatorios, 
% nos indicará cuáles son las potencias que envían e intercepta C. Generará para el supuesto 
% espía C otro número aleatorio, y nos mostrará cómo A y C obtienen una clave común (aquí A piensa que C es B) y , 
% y como B y C obtienen la otra clave común (aquí B pensará que C es A).

function intruso(g, p)

if genera(g,p) ~= 0
    
    randA = randi([1 p-1]);
    fprintf('A genera el numero aleatorio randA: %d\n', randA);
    
    pote_a = potencia(g, randA, p);
    fprintf('A envia a B el producto: %d\n\n', pote_a);
    
    %Hasta aqui es como antes
    
    %Este cacho de codigo mete la historia del intruso
    
    fprintf('EL INTRUSO CAPTURA pote_a: %d, y lo guarda\n', pote_a);
    randC = randi([1 p-1]);
    fprintf('EL INTRUSO GENERA cc: %d\n', randC);
    pote_c = potencia(g, randC, p);
    fprintf('EL INTRUSO ENVIA a B: %d\n', pote_c);
    fprintf('B piensa que le llega A\n\n');
    
    %Ahora generamos los de B
    randB = randi([1 p-1]);
    fprintf('B genera un número aleatorio %d', randB);
    pote_b = potencia(g, randB, p);
    fprintf('B envia a A : %d', pote_b);
    
    %El intruso captura lo que envia B y le envia a A pote_c
    fprintf('EL INTRUSO CAPTURA pote_b: %d y lo guarda\n', pote_b);
    fprintf('EL INTRUSO ENVIA a A el mismo dato que le ha enviado a B: %d\n', pote_c);
    fprintf('A piensa que le llega de B\n\n');
    
    %A y B calculan las claves con los datos que le ha enviado el intruso
    claveA = potencia(pote_c, randA, p);
    claveB = potencia(pote_c, randB, p);
    
    fprintf('A y B reciben datos y calculan las claves\n');
    fprintf('A cifra el mensaje con: %d\n', claveA);
    fprintf('B cifra el mensaje con: %d\n\n', claveB);
    
    fprintf('En este caso el intruso sabria la clave\n\n');
    
else
   %No se puede hacer cosas
   fprint('El g introducido y p no son validos puesto que no son generadores');
end