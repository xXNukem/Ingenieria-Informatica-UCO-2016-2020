% A cada letra del texto, la función le debe asociar su correspondiente valor de Z27, con dos dígitos: a:00, b:01, …, z:26. 
% Entradas:  texto: el texto llano 
% Salida: doble: cadena numérica formada por los números asociados a cada letra del texto. 
 
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