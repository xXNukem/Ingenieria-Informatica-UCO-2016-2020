function [cp, mu, invw] = mochila_mh(s1)

%Validez de la mochila
if mochila(s1)
   %Valor de mu
   prompt = 'MU: '; %Acordarse de mirar la documentacion

   salir = false;

   while (salir==false)

        mu = input(prompt);

        if mu<(2*s1(length(s1))+2)%MU ha de cumplir una condicion
            disp('Valor no aceptado');
        else
            salir = true;
        end
   end

   salir = false;
   i = 2;

   while salir==false
       if gcd(mu, i) == 1
          if factorescomunes(i, s1) == 0 %No tendra factores comunes con la mochila
            w = i;
            salir = true;
          end
       end
       i = i+1;
   end

    %con la inversa se calcula la mochila despues
    [G, U, invw] = gcd(mu, w);

    cp = [];

    for i=1:length(s1)
        cp = [cp, mod(s1(i)*w, mu)];
    end

end