#include "Player.hh"
#include "Info.hh"
#include <climits>



/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME inkih_old


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
    struct Posicion_util
    {
      Pos posicion;
      vector<Pos> path; //*Almacena el camino hasta este punto
      Posicion_util(Pos _posicion, vector<Pos> v) : posicion(_posicion), path(v){}
    };
    
    typedef vector<vector<bool>> MatrizVisitados;
    typedef vector<vector<int>> MatrizDistancias;
    typedef queue<Posicion_util> ColaDePosiciones;

  //?Pre: Lee una unas cordenadas de un matriz y la propia matriz de vsisitados
  //?Post: Devuelve true si la cordenada es valida y no ha estado visitada
  bool posicion_aceptable(int ii, int jj, int kk) {
    return pos_ok(Pos(ii,jj,kk)) and cell(ii, jj, kk).type == Cave and cell(ii, jj, kk).id == -1;
  }



  bool posicion_aceptable_furyan(int ii, int jj, int kk) {
    return pos_ok(Pos(ii,jj,kk)) and cell(ii, jj, kk).type != Rock and cell(ii, jj, kk).owner != me();


  }

  //?Pre: Le entra un id de un pioneer
  //?Post: Devuelve la siguiente posicion a la que deve ir el pioneer para llegar a una casilla que no sea suya
  Pos bfs_inmersivo_pioneer(int id) {
    MatrizVisitados mat_visitados(40, vector<bool>(80, false));
    //MatrizDistancias mat_distancias(40, vector<int>(80, INT_MAX));
    ColaDePosiciones cola_pendientes;
    Pos posicion_original = unit(id).pos;
    mat_visitados[posicion_original.i][posicion_original.j] = true;
    cola_pendientes.push(Posicion_util(posicion_original, {posicion_original}));

    while(!cola_pendientes.empty()) {
      Posicion_util posicion_actual = cola_pendientes.front();
      cola_pendientes.pop();

      int ii = posicion_actual.posicion.i;
      int jj = posicion_actual.posicion.j;
      int kk = posicion_actual.posicion.k;

      mat_visitados[posicion_actual.posicion.i][posicion_actual.posicion.j] = true;  //?Marco el punto como visitado
      if (cell(ii, jj, kk).owner != me()) {
        //* Si se cumple esta condición habré encontrado el siguiente sitio que no me pertenece a mi.
        return posicion_actual.path[1]; //!Devuelve la siguiente casilla a la que se debe mover
      }

      if(posicion_aceptable(ii, jj - 1, kk) and !mat_visitados[ii][jj - 1]){
        vector<Pos> new_path = posicion_actual.path;       //!El camino se actualiza con el nuevo punto
        Pos posicion_siguiente = Pos(ii, jj - 1, kk);      //!Creo la nueva posicion
        new_path.push_back(posicion_siguiente);
        cola_pendientes.push(Posicion_util(posicion_siguiente, new_path));  //!La meto en la cola
      }  
      if(posicion_aceptable(ii + 1, jj, kk) and !mat_visitados[ii + 1][jj]){
        vector<Pos> new_path = posicion_actual.path; 
        Pos posicion_siguiente = Pos(ii + 1, jj, kk);
        new_path.push_back(posicion_siguiente);
        cola_pendientes.push(Posicion_util(posicion_siguiente, new_path));

      }   
      if(posicion_aceptable(ii, jj + 1, kk) and !mat_visitados[ii][jj+ 1]){
        vector<Pos> new_path = posicion_actual.path; 
        Pos posicion_siguiente = Pos(ii, jj+1, kk);
        new_path.push_back(posicion_siguiente);
        cola_pendientes.push(Posicion_util(posicion_siguiente, new_path));

      } 
      if(posicion_aceptable(ii - 1, jj, kk) and !mat_visitados[ii - 1][jj]){
        vector<Pos> new_path = posicion_actual.path; 
        Pos posicion_siguiente = Pos(ii - 1, jj, kk);
        new_path.push_back(posicion_siguiente);
        cola_pendientes.push(Posicion_util(posicion_siguiente, new_path));

      }  
      if(posicion_aceptable(ii + 1, jj + 1, kk) and !mat_visitados[ii + 1][jj + 1]){
        vector<Pos> new_path = posicion_actual.path; 
        Pos posicion_siguiente = Pos(ii + 1,jj + 1, kk);
        new_path.push_back(posicion_siguiente);
        cola_pendientes.push(Posicion_util(posicion_siguiente, new_path));

      }  
      if(posicion_aceptable(ii - 1, jj + 1, kk) and !mat_visitados[ii - 1][jj + 1]){
        vector<Pos> new_path = posicion_actual.path; 
        Pos posicion_siguiente = Pos(ii - 1, jj + 1, kk);
        new_path.push_back(posicion_siguiente);
        cola_pendientes.push(Posicion_util(posicion_siguiente, new_path));

      }
      if(posicion_aceptable(ii + 1, jj - 1, kk) and !mat_visitados[ii + 1][jj - 1]){
        vector<Pos> new_path = posicion_actual.path; 
        Pos posicion_siguiente = Pos(ii + 1, jj - 1, kk);
        new_path.push_back(posicion_siguiente);
        cola_pendientes.push(Posicion_util(posicion_siguiente, new_path));

      }  
      if(posicion_aceptable(ii - 1, jj - 1, kk) and !mat_visitados[ii - 1][jj - 1] ) {
        vector<Pos> new_path = posicion_actual.path; 
        Pos posicion_siguiente = Pos(ii - 1, jj - 1, kk); 
        new_path.push_back(posicion_siguiente);
        cola_pendientes.push(Posicion_util(posicion_siguiente, new_path));
      }  
    }
    return Pos(0, -1, 1); //!No quedan posiciones libres
  }



  Pos bfs_inmersivo_furyan(int id) {
    MatrizVisitados mat_visitados(40, vector<bool>(80, false));
    //MatrizDistancias mat_distancias(40, vector<int>(80, INT_MAX));
    ColaDePosiciones cola_pendientes;
    Pos posicion_original = unit(id).pos;
    mat_visitados[posicion_original.i][posicion_original.j] = true;
    cola_pendientes.push(Posicion_util(posicion_original, {posicion_original}));

    while(!cola_pendientes.empty()) {
      Posicion_util posicion_actual = cola_pendientes.front();
      cola_pendientes.pop();

      int ii = posicion_actual.posicion.i;
      int jj = posicion_actual.posicion.j;
      int kk = posicion_actual.posicion.k;

      int id2 = cell(posicion_actual.posicion).id;
      mat_visitados[posicion_actual.posicion.i][posicion_actual.posicion.j] = true;  //?Marco el punto como visitado
      if (id2 != -1 and unit(id2).player != me()) {
        //* Si se cumple esta condición habré encontrado el siguiente sitio que no me pertenece a mi.
        /*cerr << "aaaa" << posicion_actual.path.size() << endl;
        for ( unsigned int i = 0; i < posicion_actual.path.size(); ++i) {
          cerr << posicion_actual.path[i].i << " " << posicion_actual.path[i].j << endl; 
        } 
        */
        return posicion_actual.path[1]; //!Devuelve la siguiente casilla a la que se debe mover
      }

      if(posicion_aceptable_furyan(ii, jj - 1, kk) and !mat_visitados[ii][jj - 1]){
        vector<Pos> new_path = posicion_actual.path;       //!El camino se actualiza con el nuevo punto
        Pos posicion_siguiente = Pos(ii, jj - 1, kk);      //!Creo la nueva posicion
        new_path.push_back(posicion_siguiente);
        cola_pendientes.push(Posicion_util(posicion_siguiente, new_path));  //!La meto en la cola
      }  
      if(posicion_aceptable_furyan(ii + 1, jj, kk) and !mat_visitados[ii + 1][jj]){
        vector<Pos> new_path = posicion_actual.path; 
        Pos posicion_siguiente = Pos(ii + 1, jj, kk);
        new_path.push_back(posicion_siguiente);
        cola_pendientes.push(Posicion_util(posicion_siguiente, new_path));

      }   
      if(posicion_aceptable_furyan(ii, jj + 1, kk) and !mat_visitados[ii][jj+ 1]){
        vector<Pos> new_path = posicion_actual.path; 
        Pos posicion_siguiente = Pos(ii, jj+1, kk);
        new_path.push_back(posicion_siguiente);
        cola_pendientes.push(Posicion_util(posicion_siguiente, new_path));

      } 
      if(posicion_aceptable_furyan(ii - 1, jj, kk) and !mat_visitados[ii - 1][jj]){
        vector<Pos> new_path = posicion_actual.path; 
        Pos posicion_siguiente = Pos(ii - 1, jj, kk);
        new_path.push_back(posicion_siguiente);
        cola_pendientes.push(Posicion_util(posicion_siguiente, new_path));

      }  
      if(posicion_aceptable_furyan(ii + 1, jj + 1, kk) and !mat_visitados[ii + 1][jj + 1]){
        vector<Pos> new_path = posicion_actual.path; 
        Pos posicion_siguiente = Pos(ii + 1,jj + 1, kk);
        new_path.push_back(posicion_siguiente);
        cola_pendientes.push(Posicion_util(posicion_siguiente, new_path));

      }  
      if(posicion_aceptable_furyan(ii - 1, jj + 1, kk) and !mat_visitados[ii - 1][jj + 1]){
        vector<Pos> new_path = posicion_actual.path; 
        Pos posicion_siguiente = Pos(ii - 1, jj + 1, kk);
        new_path.push_back(posicion_siguiente);
        cola_pendientes.push(Posicion_util(posicion_siguiente, new_path));

      }
      if(posicion_aceptable_furyan(ii + 1, jj - 1, kk) and !mat_visitados[ii + 1][jj - 1]){
        vector<Pos> new_path = posicion_actual.path; 
        Pos posicion_siguiente = Pos(ii + 1, jj - 1, kk);
        new_path.push_back(posicion_siguiente);
        cola_pendientes.push(Posicion_util(posicion_siguiente, new_path));

      }  
      if(posicion_aceptable_furyan(ii - 1, jj - 1, kk) and !mat_visitados[ii - 1][jj - 1] ) {
        vector<Pos> new_path = posicion_actual.path; 
        Pos posicion_siguiente = Pos(ii - 1, jj - 1, kk); 
        new_path.push_back(posicion_siguiente);
        cola_pendientes.push(Posicion_util(posicion_siguiente, new_path));
      }  
    }
    return Pos(0, -1, 1); //!No quedan posiciones libres
  }
  
  
  //?pre: Recibe un id, y el modo 0 -> pioneer; 1 -> furyan
  //?post: Mueve es pioneer en dirección a la siguiente casilla que no sea suya
  void bfs(int id, int modo) {
    Pos posicion_actual = unit(id).pos;
    Pos posicion_nueva;
    if (modo == 0 ) posicion_nueva = bfs_inmersivo_pioneer(id);
    else  posicion_nueva = bfs_inmersivo_furyan(id);
    //*Conseguir que se mueva en la dirreccion que toca.
    int ii = posicion_actual.i;
    int jj = posicion_actual.j;
    int kk = posicion_actual.k;
    //cerr << "Posicion actual " << posicion_actual.i << " " << posicion_actual.j << endl;
    //cerr << posicion_nueva.i << " " << posicion_nueva.j << endl; 
    if(Pos(ii,jj - 1,kk) == posicion_nueva) {
      command(id, Left); //?Probar a ir a la izquierda
    }  
    else if(Pos(ii + 1,jj,kk) == posicion_nueva) {
      command(id, Bottom); //?Pruebo abajo
    }   
    else if(Pos(ii,jj + 1,kk) == posicion_nueva) {
      command(id, Right); //?Pruebo derecha
    } 
    else if(Pos(ii - 1,jj,kk) == posicion_nueva) {
      command(id, Top); //?Pruebo arriba
    }  
    else if(Pos(ii + 1,jj + 1,kk) == posicion_nueva) {
      command(id, BR);
    }  
    else if(Pos(ii -1,jj + 1,kk) == posicion_nueva) {
      command(id, RT);
    }
    else if(Pos(ii + 1, jj - 1,kk) == posicion_nueva){
      command(id, LB);
    }  
    else if(Pos(ii - 1,jj - 1,kk) == posicion_nueva) { 
      command(id, TL);
    } 
    //else cerr << "Problema" << endl;
  }



  //?Pre:
  //?Post:
  void move_pioneers() {
    vector<int> vector_pioneers = pioneers(me()); //*Lo hago cada ronda por si me matan alguno
    for (unsigned int i = 0; i < vector_pioneers.size(); ++i) {
        int id = vector_pioneers[i];
        Pos posicion_next = unit(id).pos;
        int ii = posicion_next.i;
        int jj = posicion_next.j;
        int kk = posicion_next.k;
        if(posicion_aceptable(ii,jj - 1,kk) and cell(ii, jj-1, kk).owner != me()) {
          command(vector_pioneers[i], Left); //?Probar a ir a la izquierda
        }  
        else if(posicion_aceptable(ii + 1,jj,kk) and cell(ii+1, jj, kk).owner != me()) {
          command(vector_pioneers[i], Bottom); //?Pruebo abajo
        }   
        else if(posicion_aceptable(ii,jj + 1,kk) and cell(ii, jj +1, kk).owner != me()) {
          command(vector_pioneers[i], Right); //?Pruebo derecha
        } 
        else if(posicion_aceptable(ii - 1,jj,kk) and cell(ii-1, jj, kk).owner != me()) {
          command(vector_pioneers[i], Top); //?Pruebo arriba
        }  
        else if(posicion_aceptable(ii + 1,jj + 1,kk) and cell(ii + 1, jj + 1, kk).owner != me()) {
          command(vector_pioneers[i], BR);
        }  
        else if(posicion_aceptable(ii -1,jj + 1,kk) and cell(ii - 1, jj + 1, kk).owner != me()) {
          command(vector_pioneers[i], RT);
        }
        else if(posicion_aceptable(ii + 1, jj - 1,kk)and cell(ii + 1, jj - 1, kk).owner != me()){
          command(vector_pioneers[i], LB);
        }  
        else if(posicion_aceptable(ii - 1,jj - 1,kk) and cell(ii - 1, jj - 1, kk).owner != me()) { 
          command(vector_pioneers[i], TL);
        }  
        else {
          //!Que hacer cuando quedan encerrados por casillas de su color  llamar a una funcion que haga un bfs
          //! para guiarlos a la casilla que no me pertenezca a mi mas cercana
         bfs(id, 0);
        }  
    }
  }

  //!Errores para mover furyans
  void move_furyans() {
    vector<int> id = furyans(me());
    for (unsigned int i = 0; i < id.size(); ++i) bfs(id[i], 1);
  }
  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    move_pioneers();
    move_furyans();
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);