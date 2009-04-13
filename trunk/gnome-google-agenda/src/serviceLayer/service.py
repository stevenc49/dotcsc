import gdataCalendarServices
import gdataCalendarServices.calendarServices as gdata
from domain.account import account

class Service:
    ''' This is the abstract service. Every service from servicelayer
    must implement this to access the layer below'''

    def __init__(self, initdomain):
        self.calendar_services = initdomain.get_calendar_services()
        self.result = None

    def execute(self):
        pass

    def get_result(self):
        return self.result
