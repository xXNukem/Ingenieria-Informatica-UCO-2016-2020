function doble=letra2numeros(texto)

doble=[];

    for i=1:length(texto)
        
       n = num2str(letranumero(texto(i)));
       
       if length(n)==1
        aux = strcat('0', n);
       else
        aux = n;
       end
       
       doble=[doble,aux];
       
    end
    
end