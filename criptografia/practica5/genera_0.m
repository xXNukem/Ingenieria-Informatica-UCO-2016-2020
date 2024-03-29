% Función que indica si el número natural g es generador del grupo
% multiplicativo determinado por el primo p. Para ello utilizaremos la definición
% de generador.
% Entradas:
% g: número natural de Z p , a decidir si es generador.
% p: número primo que determina el grupo multiplicativo.
% Salida:
% generador=0: en caso de que no sea generador o las entradas no
% sean correctas.
function generador=genera_0(g,p)

    if g<1 || mod(g,1)~=0
        error('ErrorTest:convertTest', 'El numero g debe ser natural entero positivo')
    end

    if isprime(p)==0
        error('ErrorTest:convertTest', 'El numero p tiene que ser primo')
    end
   
    disp('Los datos introducidos parecen estar ok')
    
    generador = g;
    tic
    if (g>= 1 && g<= p-1) || length(factor(p)) ~= 1
        B =[];
        for i=1:p-1
            b = u
            int64(potencia(g, i, p));
            if find(B == b)
                %Se sale porque esta repetido
                generador = 0;
                toc
                return;
            else
                B = [B, b];
            end
        end
        toc
    else
       generador = 0;
       toc
       return; 

end