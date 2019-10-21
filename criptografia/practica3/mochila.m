function valida=mochila(s)

    n=length(s);
    
  for i=1:n-1 %Recorrer todos los elementos de la mochila y realizar pruebas para cada uno de ellos
      
   if mod(s(i), 1) == 0 &&  s(i)>0 %Los elementos deben ser naturales y positivos
       
       sumatorio = 0;
       
       for j=1:i
            sumatorio = sumatorio + s(j);%Introducimos al sumatorio todos los elementos has la posicion que estamos probando
       end
       if s(i+1) < s(i) %Si el elemento posterior es menor que el actual ya podemos descartar
           disp('La mochila no esta ordenada crecientemente');
           valida = 0;
           return
       end
       
       if sumatorio > s(i+1)%La suma de los elementos precedentes no puede ser mayor
            valida = 0;
            disp('La mochila no es supercreciente');
            valida=0
            return
       end
   else
       valida = 0;
       disp('Los elementos de la mochila no son naturales o positivos');
       valida=0;
       return
   end
  end
%Si se pasan todas las pruebas es que la mochila es supercreciente.
disp('La mochila es supercreciente')
valida = 1;
end