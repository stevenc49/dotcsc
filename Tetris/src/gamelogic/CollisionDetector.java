package gamelogic;

public class CollisionDetector {

	private Board currentBoard;
	private Piece piece;

	public CollisionDetector(Board board, Piece piece)
	{
		this.currentBoard = board;
		this.piece = piece;
	}
	
	public boolean hit(Direction dir)
	{
		if ( hitBottom(dir) || hitLeftSide(dir) || hitRightSide(dir) )
			return true;
		
		return false;
	}
	
	private boolean hitBottom(Direction dir)
	{
		if ( piece.getTopLeftCorner_Y() + piece.grid.length >= currentBoard.getNumRows() && dir==Direction.down )
			return true;
		
		return false;
	}
	
	private boolean hitLeftSide(Direction dir)
	{
		if ( piece.getTopLeftCorner_X() <= 0 && dir==Direction.left )
			return true;
		
		return false;
	}
	
	private boolean hitRightSide(Direction dir)
	{
		if ( piece.getTopLeftCorner_X() + piece.grid.length >= currentBoard.getNumRows() && dir==Direction.right )
			return true;
		
		return false;
	}
}
