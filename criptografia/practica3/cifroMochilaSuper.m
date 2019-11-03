function cifrado = cifroMochilaSuper(s, texto)

%Comprobamos si la mochila es supercreciente
if mochila(s) == 1

    ascii = double(texto) ;
    textoBinario = dec2textoBinario(ascii, 8); % Pasar el texto a ASCII 8 bits

    %Division del texto 
    textoBinario = reshape(textoBinario', 1, []);
    
    d = length(s);
    a = mod(size(textoBinario,2), d);
    if(a ~= 0)
        %Si no es divisible metemos 1 al final
        for i=1:d-a
           textoBinario = [textoBinario, '1']; %Ruido
        end
    end


    textoBinario = reshape(textoBinario,length(s), [])'

    cifrado = [];
    aux = 0;
    for i=1:size(textoBinario,1)
        for j=1:size(textoBinario,2)
           if(textoBinario(i,j) == '1')
                aux = aux + s(j);
           end
        end
        cifrado = [cifrado, aux];
        aux = 0;
    end
    
else
    cifrado = [];
end