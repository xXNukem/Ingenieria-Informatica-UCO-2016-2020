function salida_hill = cifro_hill(A,m,texto)
    texto=lower(texto);
    texto = letranumero(texto);
    if ~isequal(inv_modulo(A,m),0)

        if mod(size(texto,2),size(A,1))~=0
            RESTO = mod(size(texto,2), size(A,1))
               for i=1:size(A,1)-RESTO
               texto=[texto,23];
            end
        end  
        
        forma_matriz = (size(texto)/size(A,1));
        forma_matriz = forma_matriz(2);
   
        texto = reshape(texto,size(A,1),forma_matriz);

        for i=1:forma_matriz
            array(:,i)=mod(A*texto(:,i),m);     
        end
        salida = reshape(array,1,[]);
        
        salida = numeroletra(salida);
    else
        salida = 0;
    end
        
end