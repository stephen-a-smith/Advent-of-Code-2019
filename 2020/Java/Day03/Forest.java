package Day03;

import java.util.ArrayList;

public class Forest {
  private Tile[][] map;

  public Forest(ArrayList<String> input){
    map = new Tile[input.size()][]; // initalize number of rows

    for(int i = 0; i < input.size(); i++){
      map[i] = new Tile[input.get(i).length()];// initalize number of columns
      for(int j = 0; j < map[i].length; j++){
        switch(input.get(i).charAt(j)){
          // Switch Expression requires Java 14+
          case '.' -> map[i][j] = Tile.EMPTY;
          case '#' -> map[i][j] = Tile.TREE;
        }
      }
    }
  }

  public int treeCount(int dx, int dy){
    int count = 0;
    int x = 0;
    int y = 0;
    while(y < map.length){
      if(map[y][x] == Tile.TREE)
        count++;
      x += dx;
      x %= map[y].length; //Wrap X 

      y += dy;
    }

    return count;
  }
}
