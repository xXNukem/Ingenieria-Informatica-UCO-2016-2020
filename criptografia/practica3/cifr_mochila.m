function cifrado=cifr_mochila(s,texto)
%La funcion comprobara si s es una mochila
%No importa si no es supercreciente

%Pasar el texto a ascii de 8 bits
texto=double(texto);
textoBinario=dec2bin(texto,8);

%Dividir en grupos de longitud n y añadir 1 si el grupo no llega a 8
n=length(s);

textoBinario=reshape(textoBinario',1,[])%Transformacion a vector

if mod(textB

end