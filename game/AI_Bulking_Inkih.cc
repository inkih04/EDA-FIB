#include "Player.hh"
#include "Info.hh"
#include <climits>



/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Bulk_Inkih


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */

  typedef queue<pair<Pos, vector<Pos>>> ColaPosiciones;
  typedef vector<vector<bool>> MatrizVisitados;
  typedef vector<vector<int>> MatrizDistancia;

  //?Pre: Recibe una j y la posicion actual de pioneer
  //?Post: Retorna true si la posicion es adecuada para moverse y conquistar casillas
  bool posicion_adecuada(int j,const  Pos& posicion_actual) {
    Pos nueva_posicion = posicion_actual + Dir(j); 
    Cell celda = cell(nueva_posicion);
    return pos_ok(nueva_posicion) and celda.id == -1 and celda.owner != me() and celda.type != Rock;  
  }

  //?Pre: Le entra la id de un pioneer
  //?Post: Retorna la siguiente posicion a la que debe abanzar para explorar otra casilla que no le pertenezca
  Pos bfs (int id) {
    ColaPosiciones cola_posiciones;
    MatrizVisitados mat_visitados(40, vector<bool>(80, false));

    Pos posicion_original = unit(id).pos;
    cola_posiciones.push({posicion_original, {posicion_original}});
    mat_visitados[posicion_original.i][posicion_original.j] = true;

    while (!cola_posiciones.empty()) {
      Pos posicion_actual = cola_posiciones.front().first;
      vector<Pos> cadena_nodo = cola_posiciones.front().second;
      cola_posiciones.pop();

      if (pos_ok(posicion_actual) and cell(posicion_actual).owner != me() and cell(posicion_actual).type == Cave and cell(posicion_actual).id == -1) {
        //*Posicion encontrada
        return cadena_nodo[1];
      }

      for (int j = 0; j < 8; ++j) {
        Pos posicion_siguiente = posicion_actual + Dir(j);
        if (pos_ok(posicion_siguiente) and !mat_visitados[posicion_siguiente.i][posicion_siguiente.j]) {
          if(cell(posicion_siguiente).id == -1 and cell(posicion_siguiente).type != Rock) {
            mat_visitados[posicion_siguiente.i][posicion_siguiente.j] = true;
            vector<Pos> nuevo_path = cadena_nodo;
            nuevo_path.push_back(posicion_siguiente);
            cola_posiciones.push({posicion_siguiente, nuevo_path});
          }
        }
      }
    }
    return Pos(0, -1 ,1); //*Retorna algo random para que el compilador no llore.
  }


  //?Pre: Recibe un identificador como parmetro
  //?Post: Mueve el pioneer(id) en direccion a la proxima casilla que no le pertenezca
  void encontrar_casilla_proxima_pioneer(int id) {
    Pos posicion_nueva = bfs(id);
    Pos posicion_actual = unit(id).pos;
    bool trobat = false;
    int j = 0;
    while (! trobat and j < 8) {
      if(posicion_actual + Dir(j) == posicion_nueva) {
        command(id, Dir(j));
        trobat = true;
      }
      ++j;
    }
  }

  //?Pre: Recibe el identificador de un pioneer(id).
  //?Post: Retorna True si la amenaza del sol esta lo suficientemente lejos.
  bool esta_oscuro(int id) {
    Pos posicion_mia = unit(id).pos;
    if (posicion_mia.j < 21) return !daylight(posicion_mia) and !daylight(Pos(0, 0,1)); 
    return !daylight(posicion_mia) and !daylight(Pos(posicion_mia.i, posicion_mia.j - 20, 1));
  }

  //!Pendiente de algunas mejoras. 
  //?Pre:
  //?Post
  Pos buscar_las_gemas(int id) {
    ColaPosiciones cola_posiciones;
    MatrizVisitados mat_visitados(41, vector<bool>(81, false));

    Pos posicion_original = unit(id).pos;
    cola_posiciones.push({posicion_original, {posicion_original}});
    mat_visitados[posicion_original.i][posicion_original.j] = true;

    while (!cola_posiciones.empty()) {
      Pos posicion_actual = cola_posiciones.front().first;
      vector<Pos> cadena_nodo = cola_posiciones.front().second;
      cola_posiciones.pop();

      if (pos_ok(posicion_actual) and cell(posicion_actual).gem and cell(posicion_actual).type == Outside and cell(posicion_actual).id == -1) {
        //*Posicion encontrada
        return cadena_nodo[1];
      }
      for (int j = 0; j < 8; ++j) {
        Pos posicion_siguiente = posicion_actual + Dir(j);
        if (pos_ok(posicion_siguiente) and !mat_visitados[posicion_siguiente.i][posicion_siguiente.j]) {
          if(cell(posicion_siguiente).id == -1 and cell(posicion_siguiente).type == Outside) {
            mat_visitados[posicion_siguiente.i][posicion_siguiente.j] = true;
            vector<Pos> nuevo_path = cadena_nodo;
            nuevo_path.push_back(posicion_siguiente);
            cola_posiciones.push({posicion_siguiente, nuevo_path});
          }
        }
      }
    }
    return Pos(0, -1 ,1); //*Retorna algo random para que el compilador no llore.
  }


  //?Pre: Recibe la id de un pioneer
  //?Post: Se mueve una casilla en dirección a la proxima gema  
  void conseguir_gemas(int id) {
    Pos posicion_nueva = buscar_las_gemas(id);
    Pos posicion_actual = unit(id).pos;
    bool trobat = false;
    int j = 0;
    while (! trobat and j < 8) {
      if(posicion_actual + Dir(j) == posicion_nueva) {
        command(id, Dir(j));
        trobat = true;
      }
      ++j;
    }
  }

  bool necromonguers_lejos() {




  }

  int distancia_hasta_la_gema(int id) {
    ColaPosiciones cola_posiciones;
    MatrizVisitados mat_visitados(41, vector<bool>(81, false));
    MatrizDistancia mat_distancias(41, vector<int>(81, -1));
    Pos posicion_original = unit(id).pos;
    cola_posiciones.push({posicion_original, {posicion_original}});
    mat_visitados[posicion_original.i][posicion_original.j] = true;
    mat_distancias[posicion_original.i][posicion_original.j] = 0;

    while (!cola_posiciones.empty()) {
      Pos posicion_actual = cola_posiciones.front().first;
      vector<Pos> cadena_nodo = cola_posiciones.front().second;
      cola_posiciones.pop();

      if (pos_ok(posicion_actual) and cell(posicion_actual).gem and cell(posicion_actual).type == Outside and cell(posicion_actual).id == -1) {
        //*Posicion encontrada
        return mat_distancias[posicion_actual.i][posicion_actual.j];
      }
      for (int j = 0; j < 8; ++j) {
        Pos posicion_siguiente = posicion_actual + Dir(j);
        if (pos_ok(posicion_siguiente) and !mat_visitados[posicion_siguiente.i][posicion_siguiente.j]) {
          if(cell(posicion_siguiente).id == -1 and cell(posicion_siguiente).type == Outside) {
            mat_visitados[posicion_siguiente.i][posicion_siguiente.j] = true;
            mat_distancias[posicion_siguiente.i][posicion_siguiente.j] = mat_distancias[posicion_actual.i][posicion_actual.j] + 1;
            vector<Pos> nuevo_path = cadena_nodo;
            nuevo_path.push_back(posicion_siguiente);
            cola_posiciones.push({posicion_siguiente, nuevo_path});
          }
        }
      }
    }
    return -1; //*Retorna algo random para que el compilador no llore.
  }

  bool gema_cerca(int id) {
    return distancia_hasta_la_gema(id) < 5;
  }


  //?Pre:
  //?Post:
  void move_pioneers() {
    vector<int> v_pioneers = pioneers(me());
    for (unsigned int i = 0; i < v_pioneers.size(); ++i) {
      int id = v_pioneers[i];
      int j = 0;
      bool mover = false;
      Pos posicion_pioneer = unit(id).pos;
      if (cell(posicion_pioneer).type == Elevator and esta_oscuro(id) and posicion_pioneer.k == 0 and gema_cerca(id)) { //* Si estoy en un ascensor y oscuridad arriba subo.
        command(id, Up);  //!A lo mejor tendria que añadirle que no subiera si hay un Necromonger a menos de 6 casillas
        mover = true;
      }   
      else if (posicion_pioneer.k == 1) { //*Si estoy arriba intento conseguir el maximo numero de gemas posible
        //!Funciona pero de alguna manera tengo que hacer que suban menos pioneers y que solo vaya uno a por cada gema  
        //!Necesitaré unos furyans muy fuertes para soportar las perdidas de pioneers. Fuck Necromonguers
          conseguir_gemas(id); 
          mover = true; 
      }   
      while (!mover and j < 8) { //*Si estoy en la cueva intento moverme a la proxima posición adyacente que no sea mia.
        if (posicion_adecuada(j, posicion_pioneer)) {
          command(id, Dir(j));
          mover = true;
        }
        ++j;
      }
        //*Si se queda rodeado por casillas propias hace un bfs para encontrar el camino mas corto hacia una casilla que no
        //*sea propia.
        if (! mover) encontrar_casilla_proxima_pioneer(id);
    }
  }

  Pos posicion_enemigo(int id) {
    ColaPosiciones cola_posiciones;
    MatrizVisitados mat_visitados(40, vector<bool>(80, false));

    Pos posicion_original = unit(id).pos;
    cola_posiciones.push({posicion_original, {posicion_original}});
    mat_visitados[posicion_original.i][posicion_original.j] = true;

    while (!cola_posiciones.empty()) {
      Pos posicion_actual = cola_posiciones.front().first;
      vector<Pos> cadena_nodo = cola_posiciones.front().second;
      cola_posiciones.pop();
      int id2 = cell(posicion_actual).id;

      if (id2 != -1 and unit(id2).player != me() and unit(id2).type != Hellhound) {
        //*Posicion encontrada
        return cadena_nodo[1];
      }

      for (int j = 0; j < 8; ++j) {
        Pos posicion_siguiente = posicion_actual + Dir(j);
        if (pos_ok(posicion_siguiente) and !mat_visitados[posicion_siguiente.i][posicion_siguiente.j]) {
          if(cell(posicion_siguiente).type != Rock) {
            mat_visitados[posicion_siguiente.i][posicion_siguiente.j] = true;
            vector<Pos> nuevo_path = cadena_nodo;
            nuevo_path.push_back(posicion_siguiente);
            cola_posiciones.push({posicion_siguiente, nuevo_path});
          }
        }
      }
    }
    return Pos(0, -1 ,1); //*Retorna algo random para que el compilador no llore.
  }


  void encontrar_enemigos(int id) {
    Pos posicion_nueva = posicion_enemigo(id);
    Pos posicion_actual = unit(id).pos;
    bool trobat = false;
    int j = 0;
    while (!trobat and j < 8) {
      if(posicion_actual + Dir(j) == posicion_nueva) {
        command(id, Dir(j));
        trobat = true;
      }
      ++j;
    }
  }

  void move_furyans() {
    vector<int> vector_furyans = furyans(me());
    for (unsigned int i = 0; i < vector_furyans.size(); ++i) {
      int id = vector_furyans[i];
      encontrar_enemigos(id);
    }
  }

  virtual void play () {
    move_furyans();
    move_pioneers();
    
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);