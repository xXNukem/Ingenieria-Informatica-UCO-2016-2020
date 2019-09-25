import funciones as fun

if __name__ == "__main__":
    print("Se esta ejecutando el programa principal");
    
    A= int(input("Escribe la variable A \n"));
    B= int(input("Escribe la variable B \n"));
    
    print(fun.suma(A,B));
    print(fun.resta(A,B));
    print(fun.division(A,B));
    print(fun.multiplicacion(A,B));