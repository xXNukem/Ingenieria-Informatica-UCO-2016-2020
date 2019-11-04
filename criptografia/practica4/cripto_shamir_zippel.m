function cripto_shamir_zippel(cp, mu)

%Se calcula q, que es S1/S2 mod mu
%Para ello tendremos que calcular 

%Buscamos el inverso de b2
[G, U, V] = gcd(cp(2), mu);
q = mod(cp(1) * V, mu);
m = length(cp)+1;
CM = [];
salirRango = false;

%Busqueda del rango
j=0; % j controla el rango
while salirRango==false
    rango = 2^(m+j);
    fprintf('Rango: [1 %d]\n', rango);

    %Metiendo multiplos modulares

    for i=1:rango
       CM = [CM, mod(i * q, mu)];
    end
    CM = sort(CM);
    %El candidato para S1 es el menor valor (conviene ordenar la mochila)
    for i=1:length(CM)
    S1 = CM(i);
            % el mcd de s1 y my es 1 (condicion fuerte pero no imprescindible)
        
            [G, U, V] = gcd(mu, S1);
            w = mod(cp(1) * V, mu);
            
            %inverso de w saca la mochila
            [G, U, winv] = gcd(mu, w);
            %Aplicamos winv a toda la mochila
            s1 = mod(cp * winv,mu);
         
            %Comprobar si es supercreciente para terminar
            if mochila2(s1) == 1
                disp('Mochila encontrada');
                disp(s1);

                return;
            end
    end
    %Aqui le pedimos al usuario si desea ampliar el rango
    prompt = 'Mochila no encontrada, pulsar 1 para continuar y 0 para salir: ';
    aux = input(prompt);
    if aux==1
        j = j+1;
    else
        salirRango = true;
    end
end
