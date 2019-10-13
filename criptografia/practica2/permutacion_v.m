function permutacion = permutacioncion_v(p)
    X = [1:size(p,2)];
    Y = sort(p);
    if X == Y
        disp('permutacioncion detectada')
        permutacion = 1;
    else
        disp('No es permutacioncion')
        permutacion = 0;
    end
end