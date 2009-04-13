package gamelogic.pieces;
import gamelogic.Board;
import gamelogic.Piece;
import gamelogic.Square;
import gamelogic.exceptions.InvalidArraySizeException;

public class Zee extends Piece
{
    public Zee()
    {   
    	grid = new Square[][] {{new Square(0, 0, 1), new Square(1, 0, 1), new Square(2, 0, 0)},
    							{new Square(0, 1, 0), new Square(1, 1, 1), new Square(2, 1, 1)},
    							{new Square(0, 2, 0), new Square(1, 2, 0), new Square(2, 2, 0)}};
    }
}
