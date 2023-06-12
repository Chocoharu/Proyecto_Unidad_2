#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
#include <list>																											//Declaracion de las bibliotecas a utilizar

using namespace std;

struct City {													// Creacion de estructura que tiene como parametro el nombre de la villa, todas las posibles conecciones que tenga y un puntuador.															
	string Village;
	vector<string> ConectV;
	int puntos=0;
	
	City(const string& Village, const string& ConectV)			// Construcctor de la estructura
        : Village(Village) {
        istringstream iss(ConectV);
        string city;
        while (getline(iss, city, ',')) {
            this->ConectV.push_back(city);
        }
    }
};
class Graph																			//Creacion de la clase grafo
{																					
	public:																			//Creacion de mapa que simplificara la relacion de las villas y sus conecciones
		map<string, vector<string>> adjacencyList;
		void addCity(const string& village, const vector<string>& ConectV) {		//Agreacion  de la estructura City al mapa
	        adjacencyList[village] = ConectV;
	    }
	    void printGraph() {															//Impresion del mapa donde se muestra las villas existentes y sus conecciones
	        for (const auto& pair : adjacencyList) {
	            cout << pair.first << ": ";
	            for (const string& connectedCity : pair.second) {
	                cout << connectedCity << ", ";
	            }
	            cout << endl;
	        }
	    }
	    void showVillage(const string& village)										//Impresion de una villa en especifico y sus conecciones
	    {
	    	if(adjacencyList.find(village)!=adjacencyList.end())
	    	{
	    		const vector<string>showVillage = adjacencyList.at(village);
	    		for(const string& Village : showVillage)
	    		{
	    			cout<<Village<<", ";
				}
				cout<<endl;
			}
			else 
			{
				cout<<"Esta villa no tiene conecciones"<<endl;
			}
		}
		void Alquimist(const string& Origen, const string& Destino) {				// Creacion de nuevos caminos entre villas
	        adjacencyList[Origen].push_back(Destino);
	        adjacencyList[Destino].push_back(Origen);
	        cout << "Camino generado entre " << Origen << " a " << Destino << endl;
	    }
};

struct Guardian {						//Creacion de estructura Guardian, donde se declaran sus parametros, incluyendo un vector para guardar a los aprendices si es el caso.
    string Name;
    int PowerLevel;
    string MainMaster;
    string Village;
    vector<Guardian*> aprendices;
};	
struct Historial {		//Estrcutura que almacenara el nombre de la villa y el rival con el que entrenaste
	string Village;
	string rival;
};
class GuardiansTree {																																	//Creacion de clase arbol que jerarquizara a los guardianes
public:
    GuardiansTree() : root(nullptr) {}

    void insertGuardian(const std::string& name, const std::string& powerLevel, const std::string& mainMaster, const std::string& village) {			//Funcion que agrega los guardianes al arbol
        Guardian* guardian = new Guardian;
        guardian->Name = name;
        guardian->PowerLevel = stoi(powerLevel);
        guardian->MainMaster = mainMaster;
        guardian->Village = village;
        guardians.push_back(guardian);
	
        if (root == nullptr) {																															//Creacion de la raiz
            root = guardian;
        }
        else {
            Guardian* master = findGuardian(mainMaster);																								//Se agregan los siguientes guardianes al arbol
            if(master != nullptr) {
                master->aprendices.push_back(guardian);																									//Se impecciona si el guardian tiene algun maestro y se agrega a su vector de aprendices
            }
        }
    }
    void loadGuardiansFromFile(const std::string& filename) {																							//Carga de archivo .txt con la informacion de los guardianes
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }
        std::string line;
        std::getline(file, line);
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name, mainMaster, village;
            std::string powerLevel;
            std::getline(iss, name, ',');
            std::getline(iss, powerLevel , ',');
            std::getline(iss, mainMaster, ',');
            std::getline(iss, village);
            insertGuardian(name, powerLevel, mainMaster, village);
        }
        file.close();
    }
    void printGuardians() {																																//Impresion de los guardianes
        printGuardian(root, 0);
    }
    Guardian* getRoot(){																																//Obtencion de la raiz del arbol
        return root;
    }
    Guardian* findGuardianFromVillage(Guardian* guardian, const std::string& village) {																	//Funcion que busca a un guardian en una billa en especifico
        if (guardian != nullptr) {
            if (strcmp(guardian->Village.c_str(),village.c_str()) == 0) {
                return guardian;
            }
            for (Guardian* aprendiz : guardian->aprendices) {
                return findGuardianFromVillage(aprendiz, village);
            }
        }
        return nullptr;
    }
    Guardian* createApprentice(const string& name, const string& village) {																				//Creacion de un nuebo guardian
	    Guardian* aprentice = new Guardian;																												//Se le asigna el nivel a 50, se le agrega un nombre y una villa, y dependiendo de la villa donde se encuentre
	    aprentice->Name = name;																															//Tendra a un maestro
	    aprentice->PowerLevel = 50;
	    aprentice->Village = village;
	
	    Guardian* mainMaster = findGuardianFromVillage(root, village);
	    if (mainMaster != nullptr) {
	        aprentice->MainMaster = mainMaster->Name;
	        mainMaster->aprendices.push_back(aprentice);
	    }
	    else {
	        aprentice->MainMaster = "";																													//De no encontrar a un maestro, se quedara en blanco
	    }
	
	    guardians.push_back(aprentice);
	    return aprentice;
	}
	Guardian* selectAprentice() {																														//Funcion que selecciona a un guardian que no sea la rais y lo retorna con sus puntos al mini (50)
	    cout << "Selecciona a algun guardian: ";
	    string name;
	    cin >> name;
	
	    Guardian* aprentice = findGuardian(name);
	    if(aprentice==root)
	    {
	    	cout<< "Accion no permitida";
		}
		else {
		    if (aprentice != nullptr) {
		        eliminateAprentice(aprentice);																											//Una vez encontrado es eliminado del arbol
		        aprentice->PowerLevel = 50;
		        return aprentice;
		    } else {
		        cout << "Guardian not found." << endl;
		        return nullptr;
		    }
		}
	}
	void travelToVillage(Guardian* aprentice, const string& destination, Graph& graph, list<Historial>& lista, vector<City>& Villa)														//Funcion para viajar por la diferentes villa e iniciar el entrenamiento
	{
		int exit=0, aux;
		bool combate = true;
	    string currentVillage = aprentice->Village;
	    vector<string> connectedV = graph.adjacencyList[currentVillage];
	    City* city;
	
	    if (find(connectedV.begin(), connectedV.end(), destination) != connectedV.end())
		{																																												//Se convalida que el grafo recibido de los parametros cuente con una villa conectada que 
	        aprentice->Village = destination;																																			//Coincida con el destino  seleccionado, de no ser el caso, no se ejetuca la funcion
	        aprentice->PowerLevel+=1;
	        PointUpdate(Villa,destination, 1);
	        for(auto villas : Villa)																																					//Se convalida que la villa visitada tenga sus puntos menor a 4, de caso contrario, ya no puede seguir
			{																																											//Entrenando.
				if(destination == villas.Village && villas.puntos>=4)
				{
					combate=false;
				}
			}
		    Guardian* mainMaster = findGuardianFromVillage(root, destination);
		    cout << "El aprendiz ha viajado a " << destination << endl;
		    
		    if(combate)																																									//Bucle del combate
	        {
	        	do
	        	{
		        	Guardian* trainingGuardian = nullptr;
			        vector<Guardian*> availableGuardians;	
					for (Guardian* guardian : guardians) {																																//Se busca a todos los guardianes presente en la villa
					    if (guardian->Village == destination)
						{
					        availableGuardians.push_back(guardian);
					    }
					}
			        while (trainingGuardian == nullptr)
					{
						int menu = 0;
					  	cout << "Guardianes disponibles en " << destination << ": ";																									//Se imprime a todos los guardianes seleccionados
					    for (Guardian* Aprentice : availableGuardians) {
					    	if(Aprentice!=aprentice)
					        cout << Aprentice->Name << "(" << Aprentice->PowerLevel << "), ";
					    }
					    cout << endl;
						cout << "1) Seleccionar a un guardian con quien entrenar" << endl << "2) Guardian recomendado" << endl;															//Seleccion de rival
						cin >> menu;
						string trainingGuardianName;
						switch(menu)
						{
							case 1: cout << "Escriba el nombre: ";																														//Seleccion manual
									cin >> trainingGuardianName;
									trainingGuardian = findGuardian(trainingGuardianName);
									break;
									
							case 2: trainingGuardian = recommendedGuardian(availableGuardians, aprentice);																				//Seleccion automatica que entrega al guardian con menor poder, ignorando al jugador
									break;				
						}
						if (trainingGuardian == nullptr) { cout << "Guardián no encontrado. Inténtalo de nuevo." << endl; } 
						else
						{
							if(Dado())
							{
								if(trainingGuardian==mainMaster ){ aprentice->PowerLevel+=2; PointUpdate(Villa,destination, 2); }															//Una vez realizado el entrenamieno se aumentara los puntos correspondientes
								else { 	aprentice->PowerLevel+=1; PointUpdate(Villa,destination, 1); }
							}

							Historial h1 {destination, trainingGuardian->Name};
							lista.push_back(h1);				 																														//Y se agregara a una lista como registro de combate
						}
						cout << "Continuar entrenando?" << endl << "1) Si" << endl << "2) No" << endl;
						cin >> aux;																																						//Termino o continuacion del bucle
						switch (aux)	
						{
						case 1: for(auto villas : Villa)																																//Verifica si alcanzao la cantidad maxima de puntos que se puede obtener en dicha villa
								{
									if(destination == villas.Village && villas.puntos>=4)
									{
										cout << "Alcanzo el puntaje maximo en entrenamiento" << endl;
										exit = 1;
									}
								}
								break;
						case 2: exit = 1;
								break;		
						} 
					}
					if(aprentice->PowerLevel>100)																																		//Validacion de valor maximo
					{
						aprentice->PowerLevel=100;
					}
				}while(exit!=1);
			}			
		}
		else { cout << "No hay una conexión directa desde " << currentVillage << " a " << destination << endl; }
	}

private:
    std::vector<Guardian*> guardians;																																	
    Guardian* root;

    Guardian* findGuardian(const std::string& name) {																																	//	Funcion que busca a un guardian dentro del vector en donde son almacenados													
        for (Guardian* guardian : guardians) {
            if (guardian->Name == name) {
                return guardian;
            }
        }
        return nullptr;
    }
    void printGuardian(Guardian* guardian, int indent) {																																//Impresion de los guardianes
        if (guardian != nullptr) {
            std::cout << std::string(indent, ' ') << "- " << guardian->Name << " (Power Level: " << guardian->PowerLevel << ", Village: " << guardian->Village << ")" << std::endl;
            for (Guardian* aprendiz : guardian->aprendices) {
                printGuardian(aprendiz, indent + 4);
            }
        }
    }
    void eliminateAprentice(Guardian* aprentice)																																		//Funcion que elimina a un guardian del arbol
	{
		Guardian* Maestro = nullptr;
	    for (Guardian* guardian : guardians) {
	        auto search = find(guardian->aprendices.begin(), guardian->aprendices.end(), aprentice);																					//Se busca en el vector de guardianes el guardian seleccionado
	        if (search != guardian->aprendices.end()) 
			{
				for(Guardian* aprendiz : guardian->aprendices)																															//Sus aprendices son almacenado en una copia
				{
					Guardian* copia = new Guardian();
					copia->Name = aprendiz->Name;
			        copia->PowerLevel = aprendiz->PowerLevel;
			        copia->MainMaster = aprendiz->MainMaster;
			        copia->Village = aprendiz->Village;
					Maestro->aprendices.push_back(copia);
				}
	            guardian->aprendices.erase(search);																																		//Finalmente es eliminado
	            break;
	   		}
	   		Maestro = guardian;
	    }
	}
	void PointUpdate(vector<City>& Villa, const string& village, const int& punto)																										//Funcion que actualiza el puntaje de las vilas
	{
		for(auto& villa : Villa)
	    {
	        if(village==villa.Village)
	        {
	        	villa.puntos+=punto;
			}
		}
	}
	Guardian* recommendedGuardian(vector<Guardian*>& guardians, Guardian* player)																										//Funcion que busa y regresa al guardian con menor poder evitando que se el
	{																																													// el jugador de ser asi.	
		Guardian* currentguardian = nullptr;
		int max = 100;
		for(auto& guardian : guardians)
		{
			if(guardian->PowerLevel < max && guardian!= player)
			{
				currentguardian = guardian;
				max = guardian->PowerLevel;
			}
		}
		return currentguardian;
	}	
	bool Dado()
	{
		int dado = rand()%6+1;
		if(dado%2==0)
		{
			cout << "Entrenamiento ganado" << endl;
			return true;
		}
		else 
		{ 
		cout << "Entrenamiento perdido" << endl;
			return false;
		}
	}
};

int main(int argc, char** argv) {																										//Inicio del main
	Graph cityGraph;
	GuardiansTree tree;																													//Declaracion de las variables a utilizar
	vector<City> Villas;
	Guardian* Boss = tree.getRoot();
	Guardian* NewAprentice  = new Guardian;
	Guardian* SelectedAprentice = new Guardian;
	int player, exit=0;
	string villa, Nombre, destination;
	list<Historial> historial;
		
    std::ifstream file2("Citys.txt");																									//Carga del archivo .txt que guarda las villas y sus conecciones
    if (!file2) {
        std::cerr << "Failed to open file: " << std::endl;
        return 1;
    }
    std::string line2;
	std::getline(file2, line2);
    while (std::getline(file2, line2)) {
        std::istringstream iss(line2);
        std::string village, conectV;
        std::getline(iss, village, ',');
        std::getline(iss, conectV , ',');
        if (cityGraph.adjacencyList.find(village) == cityGraph.adjacencyList.end()) {
            cityGraph.addCity(village, {conectV});																						//Se agrega los datos del archivo al grafo de las villas		
        } else {
            cityGraph.adjacencyList[village].push_back(conectV);
        }
    }
    file2.close();
    
    tree.loadGuardiansFromFile("Guardians.txt");																						//Activacion de la funcion que carga los guardianes
    
    cout<<"The Gurdian Journey"<<endl;
    cout<<"Inicio"<<endl<<"1) Crear guardian"<<endl<<"2) Seleccionar guardian ya existente"<<endl;										//Seleccion del guardian con el que se iniciara la aventura
    cin>>player;
    cout << "--------------------------------------------------------" << endl;
    switch(player)
    {
    	case 1:	cout << "Ingrese nombre: ";																								
    			cin>>Nombre;
    			cin.ignore();
    			cityGraph.printGraph();																									//Se imprime las posibles villas en donde se puede crear al guardian
    			cout << "Ingrese villa origen: ";
    			getline(cin, villa);
				NewAprentice = tree.createApprentice(Nombre, villa);
    			cout << NewAprentice->Name << endl;
				cout << NewAprentice->PowerLevel << endl;
				cout << NewAprentice->MainMaster<< endl;
				cout << NewAprentice->Village << endl;
				break;
		case 2: tree.printGuardians();
				NewAprentice = tree.selectAprentice();																					//Se imprime los posibles guardianes que puedes seleccionar
				cout << NewAprentice->Name << endl;
				cout << NewAprentice->PowerLevel << endl;
				cout << NewAprentice->MainMaster<< endl;
				cout << NewAprentice->Village << endl;
				break;		
	}
	cout << "--------------------------------------------------------" << endl;															//Inicio del viaje (bucle)
	cout << "La aventura comienza, es momento de empezar a viajar"<<endl;
	do
	{
		int lista = 0, camino = 0, intercambio = 0;
		string newcamino;
		
		if(NewAprentice->PowerLevel>=60)																								//Al contra con un minimo de poder es posible usar la funcion alquimia y asi crear nuevos caminos entre villas
		{
			cout << "---------------------------------------------------------------------------------------------------" << endl;
			cout << "Ha desbloqueado la funcion de alquimia, puede crear camino entre aldeas a costa de puntos de poder" << endl;
			cout << "Desea realizar el intercambio?" << endl <<"1)Si" << endl << "2)No" << endl;
			cin >> camino;
			switch(camino)
			{
				case 1: cout << "Ingrese el destino: ";																					//Seleccion de si ejecutar la funcion o no
						cin.ignore();
						getline(cin, newcamino);
						cityGraph.Alquimist(NewAprentice->Village, newcamino);
						intercambio = rand()%3+2;
						cout << "Usted a perdido " << intercambio << " puntos" << endl;
						NewAprentice->PowerLevel-=intercambio;
						break;
				case 2: cin.ignore();
						break;
			}
			cout << "---------------------------------------------------------------------------------------------------" << endl;
		}
		
		cout << "Cual es tu destino?"<<endl;																							//Seleccion de villa destino
		cityGraph.showVillage(NewAprentice->Village);
		getline(cin, destination);
		
		if(NewAprentice->PowerLevel<90&&destination == "Tesla")																			//Si se selecciona Tesla como destino y no cumple con el minimo de poder no puede biajar hasta alla
		{
			cin.ignore();
			cout << "Necesita como mino 90 puntos de poder para enfrentar a Stormheart" << endl;
		}
		else if(NewAprentice->PowerLevel>=90&&destination == "Tesla")																	//Si cumple con el puntaje minimo se dirige a telsa y lucha contra el ultimo maestro acabando con el ciclo
		{
			exit=1;
			cout << "--------------------------------------------------------" << endl;
			cout << "Estadisticas" << endl << NewAprentice->Name << endl << NewAprentice->PowerLevel << endl;
			cout << "--------------------------------------------------------" << endl;
			
			tree.travelToVillage(NewAprentice, destination, cityGraph, historial,Villas);
		}
		else																															//Si viaja a cualquier otro lugar que no sea Tesla, puede hacerce con total libertad para entrenar
		{
			tree.travelToVillage(NewAprentice, destination, cityGraph, historial,Villas);
			
			cout << "--------------------------------------------------------" << endl;
			cout << "Estadisticas actualizadas" << endl << NewAprentice->Name << endl << NewAprentice->PowerLevel << endl;				//Cada vez que se termine el entrenamiento se mostrara las estadisticas actualizadas del jugador
			cout << "--------------------------------------------------------" << endl;													//En el caso de Tesla se mostrara antes del combate
			
			cout << "Desea ver el historial hasta el momento?" << endl << "1) Si" << endl << "2) No" << endl;							//Seleccion de ver el historial de combate o no
			cin  >> lista;
			cin.ignore();
			if(lista==1)																										
			{
				for(auto& combate : historial)
			    {
			    	cout << "En " << combate.Village << " se combatio con " << combate.rival << endl;									//Se imprime la lista mostrando el recorrido y el combate realizado por el jugador
				}
			}
			cout << "--------------------------------------------------------" << endl;
		}
	}while(exit!=1);																													//Fin bucle

	cout << "Fin del viaje" << endl;

    return 0;																															//Fin codigo
}
