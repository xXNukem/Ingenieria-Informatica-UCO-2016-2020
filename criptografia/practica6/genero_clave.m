% El programa debe pedir al usuario los valores de los primos p y q. 
% Una sugerencia, para facilitar la introducciÛn de estos valores, es pedirle 
% al programa que muestre en primer lugar un listado de n˙meros primos hasta un cierto valor. 
% Si los n˙meros anteriores son lo suficientemente grandes puede considerar ? = 1 + 224 = 65537, y
% si no o bien solicitarlo al usuario o 
% generar cualquier valor para e v·lido de la manera que considerÈis m·s oportuna.
function clave=genero_clave()

    disp('Mostrando primeros numeros primos ');
    
    primes(1000)
       
    
    disp('Introduce los numeros:')
    p = input('Introduce el primo p');
    q = input ('Introduce el primo q');
    
    fi_n=(p-1)*(q-1); %fi de n tiene que ser mayor que el numero por defecto
    
    n=p*q;%obtenemos la n
    
    e=0;
    
    if fi_n>65537
        e=65537;
    else
        for i=2:fi_n-2
           if gcd(e,i)==1
              e=i; %obtenemos la e
           end
        end
    end
    
    %obtenemos la d
    [g,c,d]=gcd(e,fi_n);
    d=mod(c,fi_n);
    
    fprintf('La clave privada es (%d, %d)\n', n,d);
    fprintf('La clave p√∫blica es (%d, %d)\n\n', n, e);

end