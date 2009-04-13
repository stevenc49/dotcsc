
public class Zee extends Piece {

	private Square [][] grid;
	private int topLeftCornerInGameCanvas_X;
	private int topLeftCornerInGameCanvas_Y;
	
    public Zee()
    //constructor
    {
    	grid = new Square[][] {{new Square(0, 0, 0), new Square(1, 0, 0), new Square(2, 0, 0)},
    							{new Square(0, 1, 1), new Square(1, 1, 1), new Square(2, 1, 0)},
    							{new Square(0, 2, 0), new Square(1, 2, 1), new Square(2, 2, 1)}};
    }
	
	public void rotate() {

		// perhaps this may not be the most elegant way to rotate a piece
		// TODO: find an algorithm that will do this and replace this
		Square temp[][];
		temp = new Square[3][3];

		temp[2][0] = grid[0][0];
		temp[2][1] = grid[1][0];
		temp[2][2] = grid[2][0];
		temp[1][2] = grid[2][1];
		temp[0][2] = grid[2][2];
		temp[0][1] = grid[1][2];
		temp[0][0] = grid[0][2];
		temp[1][0] = grid[0][1];
		temp[1][1] = grid[1][1];

		grid[0][0] = temp[0][0];
		grid[1][0] = temp[1][0];
		grid[2][0] = temp[2][0];
		grid[2][1] = temp[2][1];
		grid[2][2] = temp[2][2];
		grid[1][2] = temp[1][2];
		grid[0][2] = temp[0][2];
		grid[0][1] = temp[0][1];
		grid[1][1] = temp[1][1];
		
	}
    
	public void move() {
		
	}
	
	public void printGrid() {
		
    	for (int i=0; i < grid.length ; i++)
    	{
 		   for (int j=0; j < grid[i].length ; j++)
 		   {
 			   System.out.print(grid[i][j].getColor());
 		   }
 		   System.out.println();
    	}
	}

	public Square[][] getGrid() {
		return grid;
	}

	public void setGrid(Square[][] grid) {
		this.grid = grid;
	}

	public int getTopLeftCorner_X() {
		return topLeftCornerInGameCanvas_X;
	}

	public void setTopLeftCorner_X(int topLeftCorner_X) {
		this.topLeftCornerInGameCanvas_X = topLeftCorner_X;
	}

	public int getTopLeftCorner_Y() {
		return topLeftCornerInGameCanvas_Y;
	}

	public void setTopLeftCorner_Y(int topLeftCorner_Y) {
		this.topLeftCornerInGameCanvas_Y = topLeftCorner_Y;
	}

	private void setSquare(int x, int y, int color)
	{
		grid[x][y].setColor(color);
	}
}
