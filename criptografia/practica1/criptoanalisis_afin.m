function criptoanalisis_afin(v, m)
format shortg %Dar formato a la salida
[frecuencia, freordenada] = cripto_ana_orden(v);
alfabeto = 'abcdefghijklmnnopqrstuvwxyz';
alfabeto(15) = char(241);
disp(alfabeto);

frecuenciaCastellano = [0.1311 4; 0.106 0; 0.0847 19; 0.0823 15; 0.0716 8; 0.0714 13; 0.0695 18; 0.0587 3; 0.054 20; 0.0485 2; 0.0442 11; 0.0434 21; 0.0311 12; 0.0271 16; 0.014 6; 0.0116 1; 0.0113 5; 0.0082 22; 0.0079 25; 0.0074 17; 0.006 7; 0.0026 26; 0.0025 9; 0.0015 24; 0.0012 23; 0.0011 10; 0.001 14];

a = 0;

    for i=1:length(freordenada)
        for j=1:length(frecuenciaCastellano)
            
            %Entramos cuando la frecuencia ordenada se parezca a la de castellano
            if i~= j
                %Cogemos las 2 letras mas utilizadas tanto del alfabeto castellano como del introducido y formamos el sistema de ecuaciones
                x1 = round(frecuenciaCastellano(i,2));
                x2 = round(frecuenciaCastellano(j, 2));
                y1 = round(freordenada(i,2));
                y2 = round(freordenada(j,2));
                B = [x1 1;x2 1];
                C = [y1; y2];
                %Es necesario comprobar si hay inverso
                B = mod(B, length(alfabeto));
                deter=round(mod(det(B),length(alfabeto)));%porque gcd admite entradas enteras
                [G ,U ,V]=gcd(length(alfabeto),deter);
                if(G==1)
                    %El mcd es 1 y entramos
                    B = inv_modulo(B, length(alfabeto));
                    A = B*C;
                    %Ahora resolvemos el sistema de ecuaciones para obtener k y d y
                    %desciframos con afin
                    clave = mod(A(1,1), length(alfabeto));
                    d = mod(A(2,1), length(alfabeto));
                    %Una vez tenemos la clave llamamos al cifrado afin
                    if gcd(clave, length(alfabeto)) == 1
                        fprintf('Clave: %d:\n', clave);
                        fprintf('D: %d:\n', d);
                        descifradoafin = desafin(clave, d, v)
                    else
                        disp('Clave invalida')
                    end
                    prompt = '1 para reintentar, 0 para salir';
                    a = input(prompt);
                end

                if a == 0
                    return
                end   
            end
        end
end