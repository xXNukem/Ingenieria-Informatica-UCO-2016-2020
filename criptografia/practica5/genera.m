% Funci�n que indica si el n�mero natural g es generador del grupo multiplicativo determinado por el primo p. 
% Para ello utilizaremos la definici�n de generador.
% Entradas:  g: n�mero natural de Zp, a decidir si es generador. p: n�mero primo que determina el grupo multiplicativo. 
% Salida: generador=0: en caso de que no sea generador o las entradas no sean correctas. generador=g: en caso de que sea generador. Tambi�n nos debe mostrar el tiempo que tarda en decidir si el elemento es generador.

function generador = genera(g, p)
generador = g;
tic
if (g>= 1 && g<= p-1) || length(factor(p)) ~= 1
    q = p-1;
    F = factor(q);
    for i=1:length(F)
        aux = uint64(potencia(generador, q/F(i), p));
        if aux == 1
            generador = 0;
            break;
        end
    end
    toc
else
   generador = 0;
   toc
   return; 
end