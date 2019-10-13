function mat_per=matper(p)
    if permutacion_v(p) == 1
    mat_per = zeros(size(p,2),size(p,2));   
    for i=1:size(p,2)
        mat_per(i,p(i))= 1;
    end
    else
        disp('Error')
    end
end
