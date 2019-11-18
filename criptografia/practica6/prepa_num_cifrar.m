function blo = prepa_num_cifrar (tama, bloque)

if mod(length(bloque), tama) ~= 0
    %habra que añadir 30 y 0 
    if mod(tama-mod(length(bloque), tama), 2) == 0
        %Es par
        while(mod(length(bloque), tama)~=0)
            bloque = strcat(bloque, '30');
        end
    else
        %Es impar
        while(tama-mod(length(bloque),tama) ~= 1)
            bloque = strcat(bloque, '30');
        end
        bloque = strcat(bloque, '0');
    end
end
%Si no los bloques cabran y todo bien
bloque = reshape(bloque, tama, []);
bloque = bloque';

blo = [];

%Como viene en cadena se acaba pasandolos a entero
    for i=1:size(bloque,1)
        blo = [blo, str2num(bloque(i, :))];
    end

end