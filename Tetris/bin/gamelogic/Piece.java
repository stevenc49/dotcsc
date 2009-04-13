package gamelogic;

import gamelogic.exceptions.InvalidArraySizeException;

public abstract class Piece
{
	protected Square [][] grid;
	protected int topLeftCorner_X;
	protected int topLeftCorner_Y;

	public void rotate()
	// precondition: piece must be 3x3, override it if piece is 4x4 or 2x2
	{
		if(grid.length!=3)
			try { throw new InvalidArraySizeException("The calling piece object must be 3x3 otherwise you need to override this method for your non-3x3 class"); }
				catch (InvalidArraySizeException e) { e.printStackTrace(); }
		
		// perhaps this may not be the most elegant way to rotate a piece
		// TODO: find an algorithm that will rotate a 3x3 array 90 degrees
		Square temp[][];
		temp = new Square[3][3];

		temp[2][0] = getGrid()[0][0];
		temp[2][1] = getGrid()[1][0];
		temp[2][2] = getGrid()[2][0];
		temp[1][2] = getGrid()[2][1];
		temp[0][2] = getGrid()[2][2];
		temp[0][1] = getGrid()[1][2];
		temp[0][0] = getGrid()[0][2];
		temp[1][0] = getGrid()[0][1];
		temp[1][1] = getGrid()[1][1];

		getGrid()[0][0] = temp[0][0];
		getGrid()[1][0] = temp[1][0];
		getGrid()[2][0] = temp[2][0];
		getGrid()[2][1] = temp[2][1];
		getGrid()[2][2] = temp[2][2];
		getGrid()[1][2] = temp[1][2];
		getGrid()[0][2] = temp[0][2];
		getGrid()[0][1] = temp[0][1];
		getGrid()[1][1] = temp[1][1];
	}

	public void move(Board board, Direction dir)
	{
		clearPreviousBoardPlacement(board);
		
		switch(dir)
		{
			case down:
				topLeftCorner_Y++;
				break;
			case right:
				topLeftCorner_X++;
				break;
			case left:
				topLeftCorner_X--;
				break;
		}
		
		board.placePieceOnBoard(this, topLeftCorner_X, topLeftCorner_Y);
	}
	
	public void printGrid()
	{
    	for (int i=0; i < getGrid().length ; i++)
    	{
 		   for (int j=0; j < getGrid()[i].length ; j++)
 		   {
 			   System.out.print(getGrid()[i][j].getColor());
 		   }
 		   System.out.println();
    	}
	}

	protected abstract Square[][] getGrid();

	//accessors
	public int getTopLeftCorner_X() {
		return topLeftCorner_X;
	}

	public void setTopLeftCorner_X(int topLeftCorner_X) {
		this.topLeftCorner_X = topLeftCorner_X;
	}

	public int getTopLeftCorner_Y() {
		return topLeftCorner_Y;
	}

	public void setTopLeftCorner_Y(int topLeftCorner_Y) {
		this.topLeftCorner_Y = topLeftCorner_Y;
	}
	
	//helper methods
	protected void clearPreviousBoardPlacement(Board board)
	{
		int offset_X = topLeftCorner_X;
		int offset_Y = topLeftCorner_Y;
		
    	for (int i=0 ; i < getGrid().length ; i++)
    	{
 		   for (int j=0 ; j < getGrid()[i].length ; j++)
 		   {
 			   board.setSquare(i+offset_X, j+offset_Y, 0);
 		   }
    	}
	}
}