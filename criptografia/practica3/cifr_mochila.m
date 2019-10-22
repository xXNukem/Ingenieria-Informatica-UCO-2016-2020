function cifrado=cifr_mochila(s,texto)
%La funcion comprobara si s es una mochila
%No importa si no es supercrecientepero debe ser correcta
if mochila(s)==0
    return
end
disp('que te jodan');
%Pasar el texto a ascii de 8 bits
texto=double(texto);
textoBinario=dec2bin(texto,8);

%Dividir en grupos de longitud n y añadir 1 si el grupo no llega a 835

textoBinario=reshape(textoBinario',1,[]);%Transformacion a vector
n=length(s);
%proceso de insertar 1
aux=mod(size(textoBinario,2),n);
if(aux ~= 0)
   %si no es divisible metemos 1
   for i=1:n-aux
      textoBinario=[textoBinario, '1']; 
   end
end
textoBinario=reshape(textoBinario,length(s),[])'

%hora del ciframiento
cifrado=[];
aux=0;

for i=1:size(textoBinario,1)
   for j=1: size(textoBinario,2)
       if(textoBinario(i,j)=='1')
           aux=aux+s(j);
       end

   end
       cifrado=[cifrado,aux];
       aux=0;
end

end