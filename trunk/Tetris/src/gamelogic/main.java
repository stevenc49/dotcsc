package gamelogic;

import gamelogic.pieces.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;



public class main {

    public static void main(String args[]) throws IOException
	{
    	
		BufferedReader kbIn = new BufferedReader(new InputStreamReader (System.in));
		
		while(true)
		{
			System.out.println("1. Test CollisonDetection");
			System.out.println("2. Test CopyConstructor");
			System.out.println("3. Test PlacePieceOnBoard");
			System.out.println("4. Test MovingPiece");
			System.out.println("5. Test RotatingPieceOnBoard");
			System.out.println("6. Test PieceMinimizer");
			System.out.println("7. Test Rotater");
			System.out.println("Enter choice: ");

			String choice = kbIn.readLine();
			
			if(choice.equals("1"))
			{
				testCollisonDetector();
			}
			else if (choice.equals("2"))
			{
				testCopyConstructor();
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
			else if (choice.equals("6"))
			{
				testPieceMinimizer();
			}
			else if (choice.equals("7"))
			{
				testRotate();
			}
			
			System.out.println();
		}
	}

	private static void clearScreen()
	{
		for(int i=0; i<300; i++)
			System.out.println();		
	}

	private static void testCollisonDetector()
    {
    	Board playArea = new Board(4, 4);
    	playArea.fillGrid(0);
    	
    	Piece piece = new Zee();
    	piece.setTopLeftCorner_X(0);
    	piece.setTopLeftCorner_Y(0);
    	
    	playArea.placePieceOnBoard(piece, piece.getTopLeftCorner_X(), piece.getTopLeftCorner_Y());

    	playArea.printGrid();
    	
    	System.out.println();
    	
    	piece.move(playArea, Direction.down);
    	playArea.printGrid();
    	
    	System.out.println();
    	
    	piece.move(playArea, Direction.down);
    	playArea.printGrid();
    }
    
    private static void testCopyConstructor()
    {
    	Board originalBoard = new Board(5, 5);
    	originalBoard.fillGrid(0);
    	
    	Board copyBoard = new Board(originalBoard);
    	copyBoard.setSquare(1, 1, 2);
    	
    	System.out.println();
    	
    	originalBoard.printGrid();
    	copyBoard.printGrid();
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
		
		piece.rotate(playArea);
		playArea.printGrid();
		
		
    }
    
	private static void testPieceMinimizer()
	{
		Piece piece = new El();
		PieceMinimizer pieceMinimizer = new PieceMinimizer();
		
		piece.rotate();
		piece.printGrid();
		pieceMinimizer.minimize(piece);
		
		piece.rotate();
		piece.printGrid();
		pieceMinimizer.minimize(piece);
		
	}
	
	private static void testRotate()
	{
		Piece piece = new Zee();
		
		piece.rotate();
		piece.printGrid();
		
		System.out.println();
		
		piece.rotate();
		piece.printGrid();
		
		System.out.println();
		
		piece.rotate();
		piece.printGrid();
		
	}
}
