import ca.ubc.magic.osgibroker.OSGiBrokerClient;
import ca.ubc.magic.osgibroker.OSGiBrokerException;
import ca.ubc.magic.osgibroker.OSGiBrokerService;
import ca.ubc.magic.osgibroker.workgroups.TopicEvent;

public class User2 {

	private static final String HOST = "localhost:8080";
	private static final String TOPIC = "mc_image";
	private static final String URL = "http://localhost:8800/EventListener/listen";
	
	public static void main(String[] args) {
		
		try {
			OSGiBrokerService service = new OSGiBrokerService (HOST);
			OSGiBrokerClient client = service.addClient("user2");
			
//			client.subscriber().subscribeHttp (TOPIC, false);
//			client.subscriber().unsubscribeHttp(TOPIC);
//			client.subscriber().subscribeHttp(TOPIC, false, URL);
			
			TopicEvent[] events;
			
			EventHandler handler = new EventHandler(client);
			
			while(true)
			{
				events = client.subscriber().getEvents(TOPIC, 1);

				for(TopicEvent event: events)
				{
					if( event.getAttribute("status").equals("update") )
						handler.doUpdate();
//						System.out.println("An event happened. Time to go fetch the latest image");//invoke eventhandler
				}
				
//				System.out.println("polled");
			}
			
		} catch (OSGiBrokerException e) {
			e.printStackTrace();
		}
	}
}
