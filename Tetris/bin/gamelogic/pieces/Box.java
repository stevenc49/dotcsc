package gamelogic.pieces;
import gamelogic.Piece;
import gamelogic.Square;

public class Box extends Piece
{
    public Box()
    {   
    	grid = new Square[][] {{new Square(0, 0, 1), new Square(1, 0, 1)},
    							{new Square(0, 1, 1), new Square(1, 1, 1)}};
    }

	public void rotate()
	{
	}
    
	public Square[][] getGrid() {
		return grid;
	}
}
