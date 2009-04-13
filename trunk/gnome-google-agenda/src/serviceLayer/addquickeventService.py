from service import Service 

class AddQuickEventService(Service):
    
    def execute(self, str):
        self.result = self.calendar_services.insert_quick_add_event(str)
