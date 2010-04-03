import ca.ubc.magic.osgibroker.OSGiBrokerClient;

//should be an interface callback
public class EventHandler {

	private OSGiBrokerClient client;
	
	public EventHandler(OSGiBrokerClient _client){
		this.client = _client;
	}

	public void doUpdate() {
		
		String output = client.getClientId()+" got a new event and should do an update";
		System.out.println(output);
	
	}
}
