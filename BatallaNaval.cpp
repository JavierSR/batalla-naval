#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define tam 10

using namespace std;

int barcos1=0,barcos2=0,turno=1; 
char tabJ1[tam][tam],marJ1[tam][tam],tabJ2[tam][tam],marJ2[tam][tam]; //4 Matrices, dos tableros por cada jugador
bool sp=false; //sp detecta si esta en SinglePlayer mode
string nombre1="",nombre2="",mostrar="off";

void inicializar() { //Llena las matrices con el caracter 176 que representa area vacia (o agua)
	for(int i=0;i<tam;i++) {
		for(int j=0;j<tam;j++) {
			tabJ1[i][j]=176;
			marJ1[i][j]=176;
			tabJ2[i][j]=176;
			marJ2[i][j]=176;
		}
	}
}

void imprimirTiros () {
	char letra=65;
	
	cout<<"Turno del jugador ";
	if (turno==1) {
		cout<<nombre1;
	}
	else {
		cout<<nombre2;
	}
	cout<<"\n\n\n";
	Sleep(1200);  //un breve momento para ver el nombre del jugador al que le toca, este queda arriba de todas formas pero para ahorrar pereza xdlol
	cout<<"           Tablero de tiros\n\n\n    ";
	for (int i=0;i<tam;i++) {
		cout<<letra<<"  ";
		letra+=1;
	}
	cout<<"\n\n";
	for (int i=0;i<tam;i++) {
		if(i==9) {		
			cout<<i+1<<"  ";     //Detalles para que se muestre todo de forma ordenada
		}
		else {
			cout<<i+1<<"   ";
		}
		for (int j=0;j<tam;j++) {
			if (turno==1) {
					cout<<marJ1[i][j]<<"  ";
			}
			else {
				cout<<marJ2[i][j]<<"  ";
			}
			
		}
		cout<<"\n\n";
	}	
	cout<<"\n---------------------------------\n\n";
}

void imprimirTab () {
	char letra=65;
	
	cout<<"           Tablero de barcos\n\n\n    ";
	for (int i=0;i<tam;i++) {
		cout<<letra<<"  ";
		letra+=1;
	}
	cout<<"\n\n";
	for (int i=0;i<tam;i++) {
		if(i==9) {
			cout<<i+1<<"  ";
		}
		else {
			cout<<i+1<<"   ";
		}
		for (int j=0;j<tam;j++) {
			if (turno==1) {
				cout<<tabJ1[i][j]<<"  ";
			}
			else {
				cout<<tabJ2[i][j]<<"  ";
			}
		}
		cout<<"\n\n";
	}
}

bool ubicar (int largo) {
	const char vacio=176;
	int x,y,cont=0,limite=0;
	char coord[3],orientacion;
	coord[2]=1;      //Se inicializa en 1 (Se podria cualquier valor !=0) para no correr riesgos de que genere 0 como basura en la ultima posicion y un A1 se convierta en un A10
	system("cls");
	imprimirTab();
	switch (largo) { //Switch para saber que tipo de embarcacion se esta ubicando, segun eso tiene limite diferente
		case 5:      //limite = donde se sale del tablero
			cout<<"\tPorta-aviones\n\n";
			limite=6;
		break;
			
		case 4:
			cout<<"\tBuque\n\n";
			limite=7;
		break;
		
		case 3:	
			cout<<"\tLancha\n\n";
			limite=8;
		break;
		
		case 1:
			cout<<"\tSalvavidas\n\n";
			limite=10;
		break;
	}
	cout<<"Coordenada (Letra mayuscula y numero): ";
	cin>>coord;
	x=(int)coord[0]-65; //Por medio del codigo ASCII se castean las coordenadas char en un X y Y enteros
	y=(int)coord[1]-49;
	if ((coord[1]=='1') && (coord[2]=='0')) { //Validacion para que si ingresa 10 no lo tome como 1 (A10 != A1) 
		y=9;
	}
	if ((x>=0 && x<10) && (y>=0 && y<10)) { //Validacion para que las coordenadas esten dentro del tablero
		cout<<"\nOrientacion ('h' o 'v'): ";
		cin>>orientacion;
		if ((orientacion=='h') || (orientacion=='H')) {
			if (x<limite) { //validacion para que aunque la pocision inicial este dentro del tablero luego no se salga el resto del barco
				for (int i=0;i<largo;i++) {  
					if (turno==1) {  
						if (tabJ1[y][x+i]==vacio) {     //Este for recorre el largo del barco por donde seria su posicion a ubicar
						cont++;                         //y aumenta el contador las veces que encuentra espacios vacios
						}
					}
					else {
						if (tabJ2[y][x+i]==vacio) {
							cont++;
						}
					}
				}
				if (cont==largo) {                    //Si el contador vale lo mismo que el tama�o del barco signifca que 
					if (turno==1) {                 //su ubicacion es correcta y no se superpone a otras casillas ya ocupadas
						for (int i=0;i<largo;i++) {
							tabJ1[y][x+i]=254;        //Finalmente se asigna con el caracter 254 (Cuadro negro que indica la presencia del barco)
						}
					}
					else {
						for (int i=0;i<largo;i++) {    //Lo mismo pero para el Jugador2
						tabJ2[y][x+i]=254;
						}
					}
					system("cls");
					imprimirTab();
					switch (largo) {                    //Switch solamente para imprimir
						case 5:
							cout<<"\nPorta-aviones";
						break;
			
						case 4:
							cout<<"\nBuque";
						break;
		
						case 3:	
							cout<<"\nLancha";
						break;
		
						case 1:
							cout<<"\nSalvavidas";
						break;
					}
					if (largo!=3) {               //Si es una lancha que muestre 'Lancha ubicada' en vez de 'Lancha ubicado'
						cout<<" ubicado!";
					}
					else {
						cout<<" ubicada!";
					}
					getche();
					return true;
				}
				else {
					cout<<"Error, datos incorrectos(Barco se superpone a otro). Por favor intentelo de nuevo.";
				}
			}
			else {
				cout<<"Error, datos incorrectos(Barco se sale del tablero). Por favor intentelo de nuevo.";
			}
		}
		else {
			if ((orientacion == 'v') || (orientacion == 'V')) {  //Se repite lo mismo pero en caso de que sea vertical
				if (y<limite) {
					for (int i=0;i<largo;i++) {
						if (turno==1) {
							if (tabJ1[y+i][x]==vacio) {
								cont++;
							}	
						}
						else {
							if (tabJ2[y+i][x]==vacio) {
							cont++;
							}	
						}
					}
					if (cont==largo) {
						if (turno==1) {
							for (int i=0;i<largo;i++) {
								tabJ1[y+i][x]=254;
							}
						}
						else {
							for (int i=0;i<largo;i++) {
								tabJ2[y+i][x]=254;
							}
						}
						
						system("cls");
						imprimirTab();
						switch (largo) {     
							case 5:
								cout<<"\nPorta-aviones";
							break;
			
							case 4:
								cout<<"\nBuque";
							break;
		
							case 3:	
								cout<<"\nLancha";
							break;
		
							case 1:
								cout<<"\nSalvavidas";
							break;
						}
						if (largo!=3) {          
							cout<<" ubicado!";
						}
						else {
							cout<<" ubicada!";
						}
						getche();
						return true;
					}
					else {
						cout<<"Error, datos incorrectos(Barco se superpone a otro). Por favor intentelo de nuevo.";
					}
				}
				else {
					cout<<"Error, datos incorrectos(Barco se sale del tablero). Por favor intentelo de nuevo.";
				}
			}
			else {
				cout<<"Error, datos incorrectos(Orientacion no valida). Por favor intentelo de nuevo.";
			}	
		}
	}
	else {
		cout<<"Error, datos incorrectos(Coordenadas fuera del tablero). Por favor intentelo de nuevo.";
	}
	getche();
	return false;
}

void tirar(char coord[3]) {               //No se valida que se tire varias veces en el mismo sitio ya que el jugador es libre de hacerlo
	const char cuadro=254,vacio=176;      //Asi mismo si tira donde ya hundio una parte de un barco mostrara "Al agua" pero la figura del tablero no cambiara
	int x=(int)coord[0]-65;  
	int y=(int)coord[1]-49;               
	if ((coord[1]=='1') && (coord[2]=='0')) {
		y=9;
	}
	if ((x>=0) && (x<10) && (y>=0) && (y<10)) { //Que el tiro este dentro del tablero
		if (turno==1) {
			if (tabJ2[y][x]==cuadro) { //Si en la coordenada ingresada hay un barco
				for (int i=0;i<6;i++) {
					system("cls");
					Sleep(50);
					cout<<"TIRO ASESTADO";
					Sleep(50);
					barcos1++;
				}
				marJ1[y][x]=cuadro;  //En el tablero de tiros propio se marca que detecto un barco
				tabJ2[y][x]='X';	 //En el tablero enemigo se marca una X 
			}
			else {
				cout<<"\n\nAl agua!!!";
				if (marJ1[y][x]!=cuadro) { //Valida que no cambie de cuadro a raya si se tira en el mismo sitio donde ya se hundio
					marJ1[y][x]='-';       //Finalmente en el tablero de tiros propio se marca una raya para recordar donde tir�
				}
			}
			if (sp==false) { //No cambia turno si esta en modo single player
				turno=2; 
			}
		}
		else {
			if (tabJ1[y][x]==cuadro) {      //Los mismo pero para jugador 2
				for (int i=0;i<6;i++) {
					system("cls");
					Sleep(50);
					cout<<"TIRO ASESTADO";
					Sleep(50);
					barcos2++;
				}
				marJ2[y][x]=cuadro;
				tabJ1[y][x]='X';
			}
			else {
				cout<<"\n\nAl agua!!!";
				if (marJ2[y][x]!=cuadro) {
					marJ2[y][x]='-';
				}
			}
			turno=1;
		}
	}
	else {
		cout<<"\nCoordenadas invalidas en tiro.";
	}
}

void tirarIA () {
	const char cuadro=254,vacio=176;
	int x=0,y=0;
	bool r=false;
	x=rand()%(10); //Genera dos coordenadas aleatorias entre 0 y 9
	y=rand()%(10);
	cout<<"La IA tira en "<<(char)x+65<<y+1;  //Proceso contrario: En vez de escribir la coordenada y luego castearla a int
	getche();								  //ahora la genera la IA como entero pero se muestran como char
	if (tabJ1[y][x]==cuadro) {                
		tabJ1[y][x]='X';
		marJ2[y][x]=cuadro;
	}
	else {
		if (marJ2[y][x]!=cuadro) {
			marJ2[y][x]='-';	
		}
	}
}

void jcj() {
	int largo=0;
	char tiro[3];
	const char cuadro=254;
	bool r=false,ganador=false;
	barcos1=0;
	barcos2=0;
	sp=false;
	
	inicializar();
	cout<<"Jugador 1, ingrese su nombre: ";
	cin>>nombre1;
	cout<<"\nJugador 2, ingrese su nombre: ";
	cin>>nombre2;
	
	for (int k=0;k<2;k++) {
		system("cls");
		cout<<"\tFLOTA\n\n";
		cout<<"Porta-aviones (1) "<<cuadro<<cuadro<<cuadro<<cuadro<<cuadro<<"\n\n";
		cout<<"Buques (2)        "<<cuadro<<cuadro<<cuadro<<cuadro<<" "<<cuadro<<cuadro<<cuadro<<cuadro<<"\n\n";
		cout<<"Lanchas (2)       "<<cuadro<<cuadro<<cuadro<<"  "<<cuadro<<cuadro<<cuadro<<"\n\n";
		cout<<"Salvavidas (3)    "<<cuadro<<"  "<<cuadro<<"  "<<cuadro<<"\n\n";
		if (turno==1) {
			cout<<nombre1;
		}
		else {
			cout<<nombre2;
		}
		cout<<" seleccione la ubicacion inicial de sus barcos, para ello debera digitar la coordenada inicial (Ej A1) y la orientacion deseada ('h' para horizontal o 'v' para vertical). Presione enter para empezar.";
		getche();
		for (int i=0;i<8;i++) { //Segun el ciclo en que vaya el for, la variable largo adquiere distinto valor 
			switch (i) {
				case 0:
					largo=5; //La primera vez es el porta aviones
				break;
			
				case 1:
					largo=4; //Las dos siguientes los dos buques
				break;
			
				case 2:
					largo=4;
				break;
			
				case 3:
					largo=3; //Las dos lanchas
				break;
			
				case 4:
					largo=3;
				break;
			
				case 5:
					largo=1; //Finalmente los tres salva vidas
				break;
			
				case 6:
					largo=1;
				break;
			
				case 7:
					largo=1;
				break;
			}	
			do {     //Do while para que repite el ingreso de los barcos hasta que las coordenadas sean correctas
				r=ubicar(largo);
			} while (r!=true);
		}
		turno=2; //Cambia de jugador para el sgte y ultimo ciclo del for para ubicar
	}
	turno=1; //Como finaliza en jugador 2 tras ubicar los barcos se restablece el turno al jugador 1 antes que inicie el juego
	
	for (int i=0;i<3;i++) {
		system("cls");
		cout<<"Iniciando juego";
		for (int j=0;j<3;j++) {
			cout<<".";
			Sleep(150);
		}
	}
	
	do { //Ejecucion del juego
		system("cls");
		imprimirTiros();
		imprimirTab();
		cout<<"Escriba las coordenadas de su tiro: ";
		cin>>tiro;
		tirar(tiro);
		if (barcos1==22) { //El juego seguira indefinidamente hasta que alguno de los dos jugadores complete 22 aciertos
			turno=1;     //(El numero de casillas total que ocupan los barcos)
			ganador=true;
		}
		if (barcos2==22) {
			turno=2;
			ganador=true;
		}
		getche();
	}while (ganador!=true);
	
	for (int i=0;i<3;i++) {
		system("cls");
		Sleep(300);
		cout<<"Felicidades ";
		if (turno==1) {
			cout<<nombre1;
		}
		else {
			cout<<nombre2;
		}
		cout<<", usted gano!";
		Sleep(300);
	}
	getche();
}

void ubicarIA() {
	const char vacio=176;
	int limite=0,largo=0,x=0,y=0,cont=0;
	bool r=false;
	
	srand(time(0));
	for (int i=1;i<9;i++) { 
			switch (i) {
				case 1:
					largo=5;
					limite=6; 
				break;
			
				case 2:
					largo=4;
					limite=7;
				break;
			
				case 3:
					largo=4;
					limite=7;
				break;
			
				case 4:
					largo=3;
					limite=8;
				break;
			
				case 5:
					largo=3;
					limite=8;
				break;
			
				case 6:
					largo=1;
					limite=9;
				break;
			
				case 7:
					largo=1;
					limite=9;
				break;
			
				case 8:
					largo=1;
					limite=9;
				break;
			}	
			do {    
				x=rand()%(10); //Genera coordenadas aleatorias hasta que sean correctas
				y=rand()%(10);
				if (i%2==0) {            //Intercala ubicacion horizontal-vertical en cada ciclo (no cada que ubica)
					if (x<limite) {      //Asi le da mas aleatoreidad
						for (int i=0;i<largo;i++) {   
							if (tabJ2[y][x+i]==vacio) {     
								cont++;                         
							}
						}
						if (cont==largo) {                   		                 
							for (int i=0;i<largo;i++) {
							    tabJ2[y][x+i]=254;        
							}
							r=true; 
						}
					}
				}
				else {
					if (y<limite) { 
						for (int i=0;i<largo;i++) {   
							if (tabJ2[y+i][x]==vacio) {     
								cont++;                         
							}
						}
						if (cont==largo) {                   		                 
							for (int i=0;i<largo;i++) {
							    tabJ2[y+i][x]=254;        
							}
							r=true;
						}
					}
				}			
			} while (r!=true);
		}
}

void ia() {
	int largo=0;
	char tiro[3];
	const char cuadro=254;
	bool r=false,ganador=false;
	barcos1=0;
	barcos2=0;
	sp=true;
	turno=1;
	nombre2="Robocop3000";
	
	inicializar();
	cout<<"Ingrese su nombre: ";
	cin>>nombre1;
	system("cls");
	cout<<"\tFLOTA\n\n";
	cout<<"Porta-aviones (1) "<<cuadro<<cuadro<<cuadro<<cuadro<<cuadro<<"\n\n";
	cout<<"Buques (2)        "<<cuadro<<cuadro<<cuadro<<cuadro<<" "<<cuadro<<cuadro<<cuadro<<cuadro<<"\n\n";
	cout<<"Lanchas (2)       "<<cuadro<<cuadro<<cuadro<<"  "<<cuadro<<cuadro<<cuadro<<"\n\n";
	cout<<"Salvavidas (3)    "<<cuadro<<"  "<<cuadro<<"  "<<cuadro<<"\n\n";
	cout<<nombre1<<" seleccione la ubicacion inicial de sus barcos, para ello debera digitar la coordenada inicial (Ej A1) y la orientacion deseada ('h' para horizontal o 'v' para vertical). Presione enter para empezar.";
	getche();
	for (int i=0;i<8;i++) {  
		switch (i) {
			case 0:
				largo=5; 
			break;
			
			case 1:
				largo=4; 
			break;			
			
			case 2:
				largo=4;
			break;			
			
			case 3:
				largo=3;
			break;
			
			case 4:		
				largo=3;
			break;
			
			case 5:
				largo=1; 
			break;
			
			case 6:
				largo=1;
			break;
			
			case 7:
				largo=1;
			break;
		}	
		do {     
			r=ubicar(largo);
		} while (r!=true);
	} 
	ubicarIA();
	
	for (int i=0;i<3;i++) {
		system("cls");
		cout<<"Iniciando juego";
		for (int j=0;j<3;j++) {
			cout<<".";
			Sleep(150);
		}
	}
	
	do {
		system("cls");
		if (turno==1) {
			imprimirTiros();
			imprimirTab();
			cout<<"Escriba las coordenadas de su tiro: ";
			cin>>tiro;
			tirar(tiro);
			turno=2;
		}
		else {
			if (mostrar=="on") {
				imprimirTiros();
				imprimirTab();
			}
			tirarIA();
			turno=1;
		}
		if (barcos1==22) { 
			turno=1;     
			ganador=true;
		}
		if (barcos2==22) {
			turno=2;
			ganador=true;
		}
		getche();
	}
	while (ganador!=true);
}

void config() {
	int opc,color;
	do {
		system("cls");
		cout<<"\tConfiguracion\n\n";
		cout<<"1.Mostrar tablero de la maquina ["<<mostrar<<"]\n";
		cout<<"2.Cambiar aspecto\n";
		cout<<"3.Volver al menu principal\n\n";
		cout<<"Digite una opcion: ";
		cin>>opc;
		system("cls");
		
		switch (opc) {
			
			case 1:
				if (mostrar=="off") {
					mostrar="on";
				}
				else {
					mostrar="off";
				}
			break;
				
			case 2:
				cout<<"1.Default\n";
				cout<<"2.Marino\n";
				cout<<"3.Naturaleza\n";
				cout<<"4.Industrial\n\n";
				cout<<"Seleccione un conjunto de colores: ";
				cin>>color;
				switch (color) {
					case 1:
						system("color 07");
					break;
					
					case 2:
						system("color F9");
					break;
					
					case 3:
						system("color 2A");
					break;
					
					case 4:
						system("color 8E");
					break;
					
					default: 
						cout<<"\nError, seleccione una opcion correcta.";
						getche();
				}
			case 3:
				return;
			break;
			
			default:
				cout<<cout<<"\nError, seleccione una opcion correcta.";
				getche();
		}
	} while (opc!=3);
}

main () {
	int opc;
	do {
		system("cls");
		cout<<"\tBATALLA NAVAL DE YIS\n\n";
		cout<<"1.Jugador contra jugador\n";
		cout<<"2.Jugar contra la IA\n";
		cout<<"3.Configuracion\n";
		cout<<"4.Instrucciones\n";
		cout<<"5.Creditos\n";
		cout<<"6.Salir\n\n";
		cout<<"Digite una opcion: ";
		cin>>opc;
		system("cls");
		switch (opc) {
			case 1:
				jcj();
			break;
			
			case 2:
				ia();
			break;
			
			case 3:
				config();
			break;
			
			case 4:
				cout<<"Instrucciones:\n\n";
				cout<<"Juegue al clasico batalla naval (battleship) contra la maquina o contra un amigo. Al inicio de la partida los jugadores son libres de ubicar sus embarcaciones donde lo deseen. Cada jugador dispone de dos tableros, uno para ubicar sus navios y otro para marcar las disparos donde supone deberan estar las embarcaciones enemigas, cada turno el jugador anunciara la casilla donde quiere disparar. Si acierta sobre un barco enemigo se marcara como daniado, si todas las casillas de un barco se encuentran daniadas este se hundira. El ganador sera quien logre hundir la flota enemiga al completo.\n?uena suerte!";
				getche();
			break;
			
			case 5:
				cout<<"Batalla naval en C++. Creador por Oscar Sandoval. Fundamentos de programacion, Universidad Minuto de Dios. 2017.";
				getche();
			break;
			
			case 6:
				for (int i=0;i<3;i++) {
					cout<<"Finalizando aplicacion";
					for(int j=0;j<4;j++) {
						Sleep(350);
						cout<<".";
					}
					system("cls");
				}
			break;
			
			default:
				cout<<"Error, ingreso una opcion incorrecta. Por favor intentelo nuevamente.";
				getche();
		}
	} while (opc!=6);
}
