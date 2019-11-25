function autentificarFirmas(na, ea, da, nb, eb, db, mens_f, f)
    %Se llaman a las funciones aplicando los pasos vistos
    
    %A cifra con la clave de B y cifra su firma con su clave
    cif_mens_f=cifro_rsa(eb, nb, mens_f)
    cif_f_da = cifro_rsa(da, na, f)
    
    %Utilizamos la funcion de preparar para cifrar
    aux = aux_funcion(na, cif_f_da);
    tama = length(num2str(nb))-1;
    blo=prepa_num_cifrar(tama, aux);
    
    %A tiene que volver a cifrar
    cif_f_da_eb = cifro_rsa_num(eb, nb, blo)
    
    %B descifra el mensaje con la clave privada de B
    descif_mens_f = descifro_rsa( db, nb, cif_mens_f)
    %B descifra la firma cifrada con la clave privada de B
    descif_f_da_eb = descifro_rsa_num( db, nb, cif_f_da_eb)
    
    %Se prepara la firma cifrada
    aux = prepabloque(nb,na, descif_f_da_eb);

    %B obtiene la firma con la clave publica de A
    descif_f_da = descifro_rsa(ea, na, aux)
    
end