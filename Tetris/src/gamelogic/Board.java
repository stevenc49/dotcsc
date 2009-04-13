package gamelogic;


public class Board {

	private int numRows, numCol;
	private Square [][] grid;

	public Board(int numRows, int numCol)
    {
    	this.numRows = numRows;
    	this.numCol = numCol;
    	
    	grid = new Square[numRows][numCol];
    }
    
    public Board(Board original)
    {
    	this(original.numRows, original.numCol);
    	
    	grid = original.grid;
    }

    public void fillGrid(int value)
    {
    	for (int i=0; i < grid.length ; i++)
 		   for (int j=0; j < grid[i].length ; j++)
 			   grid[i][j] = new Square(j,i,value);
    }
    
	public void printGrid()
	{
    	for (int i=0; i < grid.length ; i++)
    	{
 		   for (int j=0; j < grid[i].length ; j++)
 		   {
 			   System.out.print(grid[i][j].getColor());
 		   }
 		   System.out.println();
    	}
	}

	public void placePieceOnBoard(Piece piece, int offsetX, int offsetY)
	{
		int color;

    	for (int i=0; i < piece.getGrid().length ; i++)
    	{
 		   for (int j=0; j < piece.getGrid()[i].length ; j++)
 		   {
				color	= piece.getGrid()[j][i].getColor();
			
				setSquare(offsetX+i, offsetY+j, color);
 		   }
    	}
	}

	public void setSquare(int x, int y, int color)
	{
		grid[y][x].setColor(color);
	}
	
	private int getColorOnSquare(int x, int y)
	{
		return grid[y][x].getColor();
	}
	
    public int getNumRows() {
		return numRows;
	}

	public int getNumCol() {
		return numCol;
	}

	
}