package gamelogic;

import java.util.ArrayList;

import com.sun.xml.internal.bind.v2.schemagen.xmlschema.List;

public class PieceMinimizer {

	ArrayList<Integer> emptyRows;
	ArrayList<Integer> emptyCols;
	
	public PieceMinimizer()
	{
		emptyRows = new ArrayList<Integer>();
		emptyCols = new ArrayList<Integer>();
	}
	
	public void minimize(Piece piece)
	{
		emptyRows = getListOfEmptyRows(piece);
		emptyCols = getListOfEmptyCols(piece);

		int minimized_length = piece.getRowSize() - emptyCols.size();
		int minimized_height = piece.getColSize() - emptyRows.size();
		
		Square[][] minimizedGrid = new Square[minimized_height][minimized_length];
		
		for(int i=0; i<emptyRows.size(); i++)
		{
			for(int j=0; j<emptyCols.size(); j++)
			{
				minimizedGrid[i][j].setColor(0);
//				if( emptyRows.contains(i) && emptyCols.contains(j))
//				{
//					int color = piece.getGrid()[i][j].getColor();
//					//System.out.println(i);
//					minimizedGrid[i][j].setColor(0);
//				}
			}
		}
		
		//print grid
    	for (int i=0; i < minimizedGrid.length ; i++)
    	{
 		   for (int j=0; j < minimizedGrid[i].length ; j++)
 		   {
 			   System.out.print(minimizedGrid[i][j].getColor());
 		   }
 		   System.out.println();
    	}
		
    	System.out.println(emptyRows.toString());
    	System.out.println(emptyCols.toString());
	}
	
	private ArrayList<Integer> getListOfEmptyRows(Piece piece)
	{
		emptyRows.clear();
		
    	for (int i=0 ; i < piece.getGrid().length ; i++)
    	{
    		boolean rowIsEmpty = true;
    		
			for (int j=0 ; j < piece.getGrid()[i].length ; j++)
			{
			   if( piece.getGrid()[i][j].getColor() == 1)
				   rowIsEmpty = false;
			}
 		   
 		    if(rowIsEmpty)
 		    	emptyRows.add(i);
    	}
    	
    	return emptyRows;
	}
	
	private ArrayList<Integer> getListOfEmptyCols(Piece piece)
	{
		emptyCols.clear();
    	
    	for (int i=0 ; i < piece.getGrid().length ; i++)
    	{
    		boolean colIsEmpty = true;
    		
			for (int j=0 ; j < piece.getGrid()[i].length ; j++)
			{
			   if( piece.grid[j][i].getColor() == 1)
				   colIsEmpty = false;
			}
 		   
 		    if(colIsEmpty)
 		    	emptyCols.add(i);
    	}
    	
    	return emptyCols;
	}
}
