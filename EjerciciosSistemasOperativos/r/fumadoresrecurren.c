//Declaración de estructuras

typedef struct{
	int valor;
}SEMAFORO;

typedef struct{
	int papel=0;
	int tabaco=0;
	int cerillas=0;
}fumador;

#define N 3

//Declaracion de semaforos

SEMAFORO proveedor; //Semáforo para bloquear al proveedor
SEMAFORO fum[N]; //Semáforo para bloquear a los fumadores
SEMAFORO material; //Semáforo para controlar los materiales que da el proveedor

//Declaración de fumadores
fumador fumador[N];

int tabaco=0,papel=0,cerillas=0; //Estas son las unidades que irá creando el proveedor

main()
{
	init(proveedor,0); //Inicializamos el proveedor como cerrado, ya el fumador lo abrirá cuando lo necesite
	init(material,1); //Ya que en el proveedor tenemos un wait y en los fumadores también, debe ir a 1
	for(i=0;i<N;i++)
	{
		init(fum[i],1);
	}

	fumador[1].papel=25;
	fumador[1].tabaco=25;

	fumador[2].cerillas=25;
	fumador[2].tabaco=25;

	fumador[3].cerillas=25;
	fumador[3].papel=25;

	for(i=0;i<3;i++)
	{
		crear_hilo_fumador(i);
	}//for end

	crear_hilo_proveedor();

	for(i=0;i<3;i++)
	{
		cerrar_hilo_fumador(i);
	}//for end

	cerrar_hilo_proveedor();
}//main end

proveedor()
{
	extern int tabaco, papel, cerillas; 
	extern SEMAFORO proveedor;
	extern SEMAFORO fum;
	extern SEMAFORO material;
	int cantidad; //Este valor almacenará el aleatorio que vamos generando

	while(TRUE)
	{
	wait(proveedor); //Dormimos al proveedor
		switch(rand()%3)//Generamos un numero aleatorio que nos sirve para entrar en el switch
		{
			case 0:
				//Generar Tabaco
				wait(mutex);
				tabaco += cantidad;
				signal(material);
			case 1:
				//Generar papel
				wait(mutex);
				papel += cantidad;
				signal(material);

			case 2:
				//Generar cerillas
				wait(mutex);
				cerillas += cantidad;
				signal(material);
		}//switch end
		for(i=0;i<3;i++)
		{
			signal(fum[i]); //Avisamos a los fumadores
		}//for end
	}//while end
}//proveedor end

fumador(int i)
{
	extern SEMAFORO proveedor;
	extern SEMAFORO fum;
	extern int tabaco, papel, cerillas;

	while(TRUE)
	{
		if(fumador[i].papel*fumador[i].tabaco*fumador[i].cerillas>0) //Entonces quiere decir que tengo al menos 1 de cada
		{
			fumar();
			papel_f--;
			tabaco_f--;
			cerillas_f--;
		}//if end
		else{ //El fumador necesita al menos 1
			signal(proveedor);
			wait(fum[i]);
			wait(material);
			if(tabaco!=0 && fumador[i].tabaco==0)
			{
				fumador[i].tabaco=tabaco;
				tabaco=0;
			}//if end

			if(cerillas!=0 && fumador[i].cerillas==0)
			{
				fumador[i].cerillas=cerillas;
				cerillas=0;
			}//if end

			if(papel!=0 && fumador[i].papel==0)
			{
				fumador[i].papel=papel;
				papel=0;
			}//if end

			signal(material);
			signal(fum[i])
		}//else end
	}//while end
	
}//fumador end
