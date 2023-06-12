# Proyecto_Unidad_2
 
 Proyecto evaluado unidad 2 Algoritmo

En este proyeto se nos pidio implementar una jerarquizacion de guardianes que deberan ser cargado atraves de un archivo externo.
Asi mismo se debe de crear un grafo que guarde la informacion de un archivo externo y se conecten correctamente.

Para iniciar todo esto, se creo una estructura capaz de almacenar los nombre, puntos de poder, villa y un vector de aprendices para los guardianes.
Para las villas se creo una estructura que almacena el nombre de la villa, un vector con sus conecciones y un puntuador que validara los combates.
Ademas se crea una estructura extra para poder almacenar el historial del guardian que usaremos, guardando el nombre de la villa y el rival con el que se entreno.

Para la jerarquizacion se creo una clase arbol la cual trae funciones que permite cargar un archivo de texto y se guarda su contenido en la estrcutura diseñada anteriormente al mismo tiempo se va agregando a un vector donde se almacena los guardianes ingresados.

En esta clase exiten 2 impresiones, una publica que simplemente llama la funcion privada printguardian, la cual lo ordena de manera jerarquizada para entregar una idea del arbol.
Existe una funcion que devuelve la raiz del arbol.

Existen 2 funciones que recorre el arbol para buscar a los guardianes almacenados en el, una busca por el vector donde se almacenan todos los guardianes y la otra busca a un guardian en una villa en especifico.

El arbol tambien cuenta con 2 funciones que devuelven un guardian que sera utilizado para recorrer las diferentes villas ubicada dentro del arbol.
En este caso el jugador puede elegir a algun guardian que existe en el arbol, de ser este el caso, se elimina del arbol dicho guardian haciendo un llamado de la funcion privada eliminateGuardian o puede crear un guardian el cual debe ser ubicado en alguna villa, en ambos casos, los puntos de poder decaen a 50.

Despues cuenta con la funcion "principal" la cual permitira viajar de villa a villa y poder realizar el entrenamiento correspondiente, en esta seccion se hace el llamado a 2 funciones privadas recommendedGuardian y UpdatePoint

Se convalida que la villa donde se encuntra en guardian tenga una coneccion al destino que se desea ingresar atraves de grafo, en caso de que si exita camino viajara a dicha villa y su poder aumentara en 1, se realizara un entrenamineto con los guardianes provenientes de la villa, si es el maestro con el que se enfrenta el poder aumetara en 2, si es con otro aprendiz, aumentara en 1, el usuario podra elegir con quien entrenar, o tambien puede seleccionarse de manera automatica a traves de la funcion recommendedGuardian, el cual entregara al guardian con menor punto de poder, esto se repetira hasta que se consiga como un maximo de 4 puntos, la cual sera convalidado y actualizado atraves de UpdatePoint, una vez alcanzado este limite no se podra volver a entrenar, no obstante, siempre se obtendra 1 punto de poder cada vez que se visite una villa, siempre que se entrene los datos seran guardados en una lista que contenga la estructura historial.

En la clase Grafo existe la funcion que almacena las villas y sus vectores, luego tiene 2 opciones de impresion una especifica y otra general, la general muestra todas las villas existentes y los posibles caminos que hay con el resto de villa, la otra funcion imprime una villa en especifico y muestra sus conecciones.
Tambien existe la funcion Alquimist la cual sirve para crear nuevos caminos entre villas a costa de puntos de poder.

En la funcion main
Se ingresara en el arbol y el grafo los datos de los archivos para despues empezar a travajar con ellos.

Se crea un switch que sera lo primero en aparecer para iniciar el juego, el cual servira para seleccionar o crear el guardian que usaremos en nuestro viaje.
Una vez seleccionado se iniciara el viaje haciendo llamado a las funciones previamente mencionadas la cual se repetira indefinidamente hasta que se llegue al destino final, que es la villa Tesla, este punto solo puede ser ingresado si el poder es como minimo 90.
Cada vez que se termina el entrenamiento, se mostrara los datos actualizados de nuestro guardian y se nos preguntara si deseamos ver nuestro historial, esta opcion puede ser elegida o no, depende del usuario.
Si se consigue un minimo de 60 puntos es posible usar la funcion Alquimist para crear caminos entre las villas a costa de nuestro poder.
Como mencione anteriormente, este bucle solo se acabara cuando lleguemos a la villa Tesla y nos enfrentemos a Stormheart.

video: https://youtu.be/8Xs8kXhuw7w