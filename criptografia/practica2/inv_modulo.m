function inver=inv_modulo(A,m)
%La matriz tiene que ser cuadrada si o si, y ya luego tendra inversa o no

[filas,columnas]=size(A);
if filas~=columnas  
    inver=0;
    error('ErrorTests:convertTest','la matriz no es cuadrada, no puede tener inversa')
    return
else
    if ~isequal(A,round(A))
        inver =0;
        error('ErrorTests:convertTest','la matriz no tiene todos los elementos enteros')
        return
    else
        A=mod(A,m);
        deter=round(mod(det(A),m));%porque gcd admite entradas enteras
        [g ,u ,v]=gcd(m,deter);
        if(g==1)   % El determinante tiene que ser primo relativo con mcd 1 en el modulo en el que trabajamos
            adjA=mod(det(A)*inv(A),m);
            inverso_deter=mod(v,m);
            inver=mod(inverso_deter*adjA,m);
            inver=round(inver);
        else
            error('ErrorTests:convertTest','La matriz no tiene inversa en modulo %d \n',m)
            inver=0;
        end
    end
end
