from service import Service 

class LoginService(Service):
  
    def execute(self):
        self.result = self.calendar_services.login()  
