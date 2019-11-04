function cifrado = cifr_mochila(s, texto)

%La mochila supercreciente puede cifrar

ascii = double(texto) 
textoBinario = dec2textoBinario(ascii, 8) %Se pasan el texto a ascii 8 bits

%Ahora tenemos que dividir los bits en grupos
textoBinario = reshape(textoBinario', 1, [])


d = length(s);
a = mod(size(textoBinario,2), d);
if(a ~= 0)
    %Si no es divisible metemos 1 al final
    for i=1:d-a
       textoBinario = [textoBinario, '1']; %Añadir ruido y reshape
    end
end

textoBinario = reshape(textoBinario,length(s), [])'
%Y ahora lo ciframos
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