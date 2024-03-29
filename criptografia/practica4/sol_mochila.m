function [v,valida]=sol_mochila(s,obj)

%Comprobar si es supercreciente o no
%El objetivo puede alcanzarse aun no siendo supercreciente
    if mochila(s)==1
        valida=1;
    else
        valida=0;
    end

n=length(s);
v=zeros(1,n); %Vector para rellenar con 0 y 1
%m es el obj

for i=n:-1:1 %El algoritmo comienza hacia atras
    
    if s(i)<=obj%Si el objeto se coje la posicion en el vector vale 1
        v(i) = 1;
        obj = obj - s(i);
    end
    
end

%Se considerara objetivo no valido si no se puede recudicr a 0
if obj~=0 && valida ==0
    disp('Ni se alcanza el objetivo ni la mochila es supercreciente')
end
if obj~=0 && valida==1
    v = 0;
    disp('Con el algoritmo usado no encuentro objetivo. Pero la mochila es supercreciente')
end
if obj==0 && valida==1
     disp('El objetivo se alcanza, La mochila es supercreciente')
end
if obj==0 && valida ==0
    disp('El objetivo se alcanza, La mochila no es supercreciente')

end