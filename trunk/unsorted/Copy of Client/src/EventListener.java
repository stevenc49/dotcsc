import java.io.IOException;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import ca.ubc.magic.osgibroker.OSGiBrokerException;
import ca.ubc.magic.osgibroker.workgroups.Subscriber;
import ca.ubc.magic.osgibroker.workgroups.TopicEvent;

import java.io.BufferedWriter;
import java.io.FileWriter;

public class EventListener extends HttpServlet
{
	private static final String HOST = "localhost:8080";
	private static final String TOPIC = "mc_image";
	
	public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException{
		
		response.getWriter().write("doGet invoked!");
		
	    BufferedWriter bufferedWriter = null;
	    bufferedWriter = new BufferedWriter(new FileWriter("c:\\get.txt"));
	    bufferedWriter.write("string");
	    bufferedWriter.newLine();
	    bufferedWriter.write("string");
	    bufferedWriter.close();
		
	}
	
	public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException{
		
		System.out.println("doing post");
		response.getWriter().write("doPost invoked!");
		
	    BufferedWriter bufferedWriter = null;
	    bufferedWriter = new BufferedWriter(new FileWriter("c:\\post.txt"));
		
		TopicEvent[] events;
		
		try {
			events = Subscriber.parseEvents(request.getInputStream());
	
			for(TopicEvent event: events)
			{
				System.out.println(event.getAttribute("status"));//invoke eventhandler
				bufferedWriter.write(event.getAttribute("status"));
			}
		    
			response.getWriter().write("doPost invoked");
		} catch (OSGiBrokerException e) {
			e.printStackTrace();
		}
		
		bufferedWriter.close();
	}
}
