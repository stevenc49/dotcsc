import java.applet.*;
import java.awt.*;
import java.awt.event.*;


public class main extends Applet implements Runnable, MouseListener, MouseMotionListener
{
	private Paddle p1;
	private Paddle p2;
	private Graphics graphics;
	
	Thread thread;
	
	private Font a_Font;

	Image coolImage;
	Cursor c;
	
	int mx, my;  // the mouse coordinates
	boolean isButtonPressed = false;

	
	public void init()
	{
		c = new Cursor (Cursor.CROSSHAIR_CURSOR);
		this.setCursor (c);
		
		p1 = new Paddle(11, 2);
		p2 = new Paddle(22, 1);
		
		setBackground (Color.black);

		
		a_Font = new Font("Helvetica", Font.BOLD, 24);
		setFont(a_Font);

		
		coolImage = getImage(getCodeBase(), "test.jpg");
		System.out.println(getCodeBase().toString());

		addMouseListener( this );
		addMouseMotionListener( this );

	}

	public void start()
	{
		thread = new Thread (this);
		thread.start ();
	}
	
	public void stop(){
	}
	
	public void run ()
	{
		System.out.println(p1.getX());
		
		while(true)
		{
			p1.increment();
			p2.increment();

			repaint();
			
			try
			{
				Thread.sleep (1000);
			}
			catch (InterruptedException ex)
			{
				// do nothing
			}
		}

	}
	
	public void paint (Graphics g)
	{
		boolean image = g.drawImage(coolImage,40,80,this);
		System.out.println(image);
		
		g.setColor (Color.green);
		
		g.drawString ("A: " + p1.getX(), 10, 40);
		g.drawString ("B: " + p2.getX(), 10, 60);
		
		g.drawOval(50, 50, 20, 20);
		g.fillOval(mx-10, my-10, 20, 20);
		//g.fillRect( mx-20, my-20, 40, 40 );
	}
	
	   public void mouseEntered( MouseEvent e ) {
		      // called when the pointer enters the applet's rectangular area
		   }
		   public void mouseExited( MouseEvent e ) {
		      // called when the pointer leaves the applet's rectangular area
		   }
		   public void mouseClicked( MouseEvent e ) {
		      // called after a press and release of a mouse button
		      // with no motion in between
		      // (If the user presses, drags, and then releases, there will be
		      // no click event generated.)
		   }
		   public void mousePressed( MouseEvent e ) {  // called after a button is pressed down
		      isButtonPressed = true;
		      setBackground( Color.gray );
		      repaint();
		      // "Consume" the event so it won't be processed in the
		      // default manner by the source which generated it.
		      e.consume();
		   }
		   public void mouseReleased( MouseEvent e ) {  // called after a button is released
		      isButtonPressed = false;
		      setBackground( Color.black );
		      repaint();
		      e.consume();
		   }
		   public void mouseMoved( MouseEvent e ) {  // called during motion when no buttons are down
		      mx = e.getX();
		      my = e.getY();
		      showStatus( "Mouse at (" + mx + "," + my + ")" );
		      repaint();
		      e.consume();
		   }
		   public void mouseDragged( MouseEvent e ) {  // called during motion with buttons down
		      mx = e.getX();
		      my = e.getY();
		      showStatus( "Mouse at (" + mx + "," + my + ")" );
		      repaint();
		      e.consume();
		   }

}


