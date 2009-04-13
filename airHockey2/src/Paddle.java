
public class Paddle
{
	private int x;
	private int x_speed;
	
	public Paddle(int startX, int xSpeed) {
		x = startX;
		x_speed = xSpeed;
	}

	public int getX_speed() {
		return x_speed;
	}
	
	public void setX_speed(int x_speed) {
		this.x_speed = x_speed;
	}

	public int getX() {
		return x;
	}
	
	public void setX(int i) {
		this.x = i;
	}

	public void increment(){
		x+=x_speed;
	}

}
