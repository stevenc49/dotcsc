import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;



public class main {

    public static void main(String args[]) throws IOException
	{
    	
		BufferedReader kbIn = new BufferedReader(new InputStreamReader (System.in));
		
		while(true)
		{
			System.out.println("1. Test GameCanvas");
			System.out.println("2. Test Rotate");
			System.out.println("3. Test PlacePieceOnBoard");
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
		Piece z = new Zee();
		
		z.printGrid();
		System.out.println();
		
		z.rotate();
		z.printGrid();
		System.out.println();
		
		z.rotate();
		z.printGrid();
		System.out.println();
		
		z.rotate();
		z.printGrid();
		System.out.println();
		
		z.rotate();
		z.printGrid();
		System.out.println();
		
		z.rotate();
		z.printGrid();
		System.out.println();
    }
    
    private static void testPlaceOnBoard()
    {
    	Board playArea = new Board(15, 10);
    	playArea.fillGrid(0);
    	
    	Piece z = new Zee();
    	
    	playArea.placePieceOnBoard(z);
    	
    	playArea.printGrid();
    }
}




