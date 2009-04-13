
public class Board {

	private int numRows, numCol;
	private Square [][] grid;

    public Board(int numRows, int numCol)
    {
    	this.numRows = numRows;
    	this.numCol = numCol;
    	
    	grid = new Square[numRows][numCol];
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

	public int getColorOnSquare(int x, int y)
	{
		return grid[y][x].getColor();
	}
	
	public void placePieceOnBoard(Piece piece)
	{
		int colorOfPiece = piece.getGrid()[1][1].getColor();
		
		setSquare(5, 1, colorOfPiece);
	}
	
	private void setSquare(int x, int y, int color)
	{
		grid[y][x].setColor(color);
	}
}