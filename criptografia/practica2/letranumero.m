function v=letranumero(texto)
alfabeto='abcdefghijklmnnopqrstuvwxyz';
texto=lower(texto);
alfabeto(15)=char(241); %pasando la ñ
tam=size(texto);
v=[];

for i=1:tam(2)
   for j=1:27
   
       if texto(i)==alfabeto(j)
           v=[v,j-1];
       end
       
   end
end