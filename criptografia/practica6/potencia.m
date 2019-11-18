% Función que usa el algoritmo de potenciación rápida para calcular las
% potencias modulares.
% Entradas:
% c: base de la potencia. Un número natural.
% d: exponente de la potencia. Un número natural.
% n: módulo. Un número natural.
% Salida: pote es la potencia c d módulo n.
function pote = potencia(c,d,n)

    if c<1 || mod(c,1)~=0
        error('ErrorTest:convertTest', 'La base de la potencia debe ser un numero natural y positivo')
    end
    
    if d<1 || mod(d,1)~=0
        error('ErrorTest:convertTest', 'El exponente de la potencia debe ser un numero natural y positivo')
    end
    
     if n<1 || mod(n,1)~=0
        error('ErrorTest:convertTest', 'El modulo debe ser un numero natural y positivo')
     end
    
   % disp('Los datos introducidos parecen estar ok')
    
    
    %Pasamos el exponente a binario
    exponente = dec2bin(d);

    baseModulo = mod(c, n);
    aux = baseModulo;
    pote = 1;
    for i=length(exponente):-1:1
       if exponente(i) == '1' %Recorriendo el exponente en binario vamos operando conforme encontramos 1
          pote = uint64(mod(pote*aux, n));
       end
       aux = uint64(mod(aux*aux, n));
    end
    
end