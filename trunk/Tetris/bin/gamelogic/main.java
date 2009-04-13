package gamelogic;

import gamelogic.pieces.Bar;
import gamelogic.pieces.Box;
import gamelogic.pieces.El;
import gamelogic.pieces.ReverseEl;
import gamelogic.pieces.ReverseZee;
import gamelogic.pieces.Tee;
import gamelogic.pieces.Zee;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;



public class main {

    public static void main(String args[]) throws IOException
	{
    	
		BufferedReader kbIn = new BufferedReader(new InputStreamReader (System.in));
		
		while(true)
		{
			System.out.println("1. Test GameCanvas");
			System.out.println("2. Test Rotate");
			System.out.println("3. Test PlacePieceOnBoard");
			System.out.println("4. Test MovingPiece");
			System.out.println("5. Test RotatingPiecOnBoard");
			System.out.println("Enter choice: ");

			String choice = kbIn.readLine();
			
			if(choice.equals("1"))
			{
				testCanvas();
			}
			else if (choice.equals("2"))
			{
				testRotate();
			}
			else if (choice.equals("3"))
			{
				testPlaceOnBoard();
			}
			else if (choice.equals("4"))
			{
				testMovingPiece();
			}
			else if (choice.equals("5"))
			{
				testRotatePieceOnBoard();
			}
			
			System.out.println();
		}
	}

	private static void clearScreen()
	{
		for(int i=0; i<300; i++)
			System.out.println();		
	}

	private static void testCanvas()
    {
    	Board playArea = new Board(15, 10);
    	playArea.fillGrid(0);
    	
    	playArea.printGrid();
    }
    
    private static void testRotate()
    {
		Piece piece = new Zee();
		
		piece.printGrid();
		System.out.println();
		
		piece.rotate();
		piece.printGrid();
		System.out.println();
		
		piece.rotate();
		piece.printGrid();
		System.out.println();
    }
    
    private static void testPlaceOnBoard()
    {
    	Board playArea = new Board(5, 5);
    	playArea.fillGrid(0);
    	
    	Piece piece = new Zee();
    	playArea.placePieceOnBoard(piece, 0, 0);
    	
    	playArea.printGrid();
    }
    
    private static void testMovingPiece()
    {
    	Board playArea = new Board(15, 10);
    	playArea.fillGrid(0);
    	
    	Piece z = new Box();
		z.setTopLeftCorner_X(4);
		z.setTopLeftCorner_Y(0);
    	
    	playArea.placePieceOnBoard(z, z.getTopLeftCorner_X(), z.getTopLeftCorner_Y());
    	playArea.printGrid();
    	
    	System.out.println();
    	
    	z.move(playArea, Direction.down);
    	playArea.printGrid();
    	
    	System.out.println();
    	
    	z.move(playArea, Direction.right);
    	playArea.printGrid();

    	System.out.println();
    	
    	z.move(playArea, Direction.left);
    	playArea.printGrid();
    	
    	System.out.println();
    	
    	z.move(playArea, Direction.left);
    	playArea.printGrid();
    }
    
    private static void testRotatePieceOnBoard()
    {
    	Board playArea = new Board(4, 4);
    	playArea.fillGrid(0);
    	
    	Piece piece = new Zee();
		piece.setTopLeftCorner_X(0);
		piece.setTopLeftCorner_Y(0);
    	
    	playArea.placePieceOnBoard(piece, piece.getTopLeftCorner_X(), piece.getTopLeftCorner_Y());
		playArea.printGrid();
		
		System.out.println();
		
		piece.rotate();
    	playArea.placePieceOnBoard(piece, piece.getTopLeftCorner_X(), piece.getTopLeftCorner_Y());
		playArea.printGrid();
    }
}




