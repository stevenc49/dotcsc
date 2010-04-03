import java.util.HashMap;
import java.util.Map;

import ca.ubc.magic.osgibroker.OSGiBrokerException;
import ca.ubc.magic.osgibroker.workgroups.Publisher;

public class DummyFilter {

	private static final String BROKER_ADDRESS = "localhost:8080";
	private static final String TOPIC = "mc_image";
	private static final String FILTER_ID = "blur";
	
	public static void main(String[] args) {
		
		//call this in your code when a filter is invoked
		notifyBrokerOfUpdate(BROKER_ADDRESS, FILTER_ID);
		
	}

	private static void notifyBrokerOfUpdate(String broker_address, String filter_id) {
		try {
			Publisher pub  = new Publisher(broker_address, filter_id);
			
			Map <String, String> event = new HashMap <String, String> ();
			event.put ("status", "update");
			
			pub.sendEvent(TOPIC, event);
			
		} catch (OSGiBrokerException e) {
			e.printStackTrace();
		}
	}
}
