import gdataCalendarServices
import gdataCalendarServices.calendarServices as gdata
from domain.account import account
from persistence.log import Log

class InitDomain:
    def __init__(self):
        self.account = account()
        self.account.load()
        self.gdata = gdata.get_new_instance(self.account)
        self.log = Log.get_instance()

    def get_account(self):
        return self.account

    def get_username(self):
        self.account.get_user()

    def get_calendar_services(self):
        return self.gdata
        
    def get_log(self):
        return self.log
        
