package gamelogic.pieces;

import gamelogic.Piece;
import gamelogic.Square;

public class Bar extends Piece
{
    public Bar()
    {   
    	grid = new Square[][] {{new Square(0, 0, 0), new Square(1, 0, 0), new Square(2, 0, 0), new Square(3, 0, 0)}, 
								{new Square(0, 1, 1), new Square(1, 1, 1), new Square(2, 1, 1), new Square(3, 1, 1)},
								{new Square(0, 2, 0), new Square(1, 2, 0), new Square(2, 2, 0), new Square(3, 2, 0)},
								{new Square(0, 3, 0), new Square(1, 3, 0), new Square(2, 3, 0), new Square(3, 3, 0)}};
    }
    
	public void rotate()
	{
		Square temp[][];
		temp = new Square[4][4];
		
    	for (int i=0; i < grid.length ; i++)
    	{
 		   for (int j=0; j < grid.length ; j++)
 		   {
 			   temp[j][i] = grid[i][j];
 		   }
    	}
    	
    	for (int i=0; i < temp.length ; i++)
    	{
 		   for (int j=0; j < temp.length ; j++)
 		   {
 			   grid[i][j] = temp[i][j];
 		   }
    	}
	}
    
	public Square[][] getGrid() {
		return grid;
	}
}
