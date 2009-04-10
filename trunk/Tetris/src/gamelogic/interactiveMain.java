package gamelogic;

import gamelogic.pieces.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class interactiveMain {

    public static void main(String args[]) throws IOException
	{
		BufferedReader kbIn = new BufferedReader(new InputStreamReader (System.in));
		
    	Board playArea = new Board(10, 10);
    	playArea.fillGrid(0);
    	
    	Piece piece = new Zee();
    	piece.setTopLeftCorner_X(4);
    	piece.setTopLeftCorner_Y(0);
		
    	playArea.placePieceOnBoard(piece, piece.getTopLeftCorner_X(), piece.getTopLeftCorner_Y());
		playArea.printGrid();
    	
		while(true)
		{
			String choice = kbIn.readLine();
	    	
			if(choice.equals("a"))
			{
				piece.move(playArea, Direction.left);
				playArea.printGrid();
			}
			else if (choice.equals("s"))
			{
				piece.move(playArea, Direction.down);
				playArea.printGrid();
			}
			else if (choice.equals("d"))
			{
				piece.move(playArea, Direction.right);
				playArea.printGrid();
			}
			else if (choice.equals("w"))
			{
				piece.move(playArea, Direction.up);
				playArea.printGrid();
			}
			else if (choice.equals("/"))
			{
				piece.rotate(playArea);
				playArea.printGrid();
			}
		}
	}
}
