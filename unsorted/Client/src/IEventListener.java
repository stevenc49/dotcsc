import ca.ubc.magic.osgibroker.OSGiBrokerClient;
import ca.ubc.magic.osgibroker.OSGiBrokerException;
import ca.ubc.magic.osgibroker.OSGiBrokerService;
import ca.ubc.magic.osgibroker.workgroups.TopicEvent;

public class IEventListener implements Runnable {

	private static final String BROKER_ADDRESS = "localhost:8080";
	private static final String TOPIC = "mc_image";
	private static final String userID = "";
	
	OSGiBrokerService service = new OSGiBrokerService (BROKER_ADDRESS);
	
	
	OSGiBrokerClient client = service.addClient("user1");
	
	public void run() {
		
		TopicEvent[] events;
		EventHandler handler = new EventHandler(client);
		
		while(true)
		{
			try {
				events = client.subscriber().getEvents(TOPIC, 1);
	
	
				for(TopicEvent event: events)
				{
					if( event.getAttribute("status").equals("update") )
						handler.doUpdate();
				}
			} catch (OSGiBrokerException e) {
				e.printStackTrace();
			}
		}
	}
}
