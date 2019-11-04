function mensaje = des_mochila(s, cifrado)



aux = [];
for i=1:size(cifrado,2);
   aux2 = sol_mochila(s, cifrado(i)); %Vectores de bits
   aux = [aux, aux2];
end

%forzar que sea divisible en grupos de 8
b = mod(length(aux), 8);
if b ~= 0
   a = length(aux) - b;
   aux = aux(1:a);
end
%Ahora ya es multiplo de 8
aux = reshape(aux, 8,[])';


dec = bin2dec(num2str(aux)); %Conversion a decimal
mensaje = [char(dec)]';