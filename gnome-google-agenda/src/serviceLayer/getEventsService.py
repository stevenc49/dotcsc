from service import Service 

class GetEventsService(Service):
    
    def execute(self):
        self.result = self.calendar_services.get_events()
