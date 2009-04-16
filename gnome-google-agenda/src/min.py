try:
  from xml.etree import ElementTree # for Python 2.5 users
except ImportError:
  from elementtree import ElementTree
import gdata.calendar.service
import gdata.service
import atom.service
import gdata.calendar
import atom
import getopt
import sys
import string
import time

class CalendarExample:

  def __init__(self, email, password):
    """Creates a CalendarService and provides ClientLogin auth details to it.
    The email and password are required arguments for ClientLogin.  The 
    CalendarService automatically sets the service to be 'cl', as is 
    appropriate for calendar.  The 'source' defined below is an arbitrary 
    string, but should be used to reference your name or the name of your
    organization, the app name and version, with '-' between each of the three
    values.  The account_type is specified to authenticate either 
    Google Accounts or Google Apps accounts.  See gdata.service or 
    http://code.google.com/apis/accounts/AuthForInstalledApps.html for more
    info on ClientLogin.  NOTE: ClientLogin should only be used for installed 
    applications and not for multi-user web applications."""

    self.cal_client = gdata.calendar.service.CalendarService()
    self.cal_client.email = email
    self.cal_client.password = password
    self.cal_client.source = 'Google-Calendar_Python_Sample-1.0'
    self.cal_client.ProgrammaticLogin()

  def _PrintUserCalendars(self): 
    """Retrieves the list of calendars to which the authenticated user either
    owns or subscribes to.  This is the same list as is represented in the 
    Google Calendar GUI.  Although we are only printing the title of the 
    calendar in this case, other information, including the color of the
    calendar, the timezone, and more.  See CalendarListEntry for more details
    on available attributes."""

    feed = self.cal_client.GetAllCalendarsFeed()
    print 'Printing allcalendars: %s' % feed.title.text
    for i, a_calendar in zip(xrange(len(feed.entry)), feed.entry):
      print '\t%s. %s' % (i, a_calendar.title.text,)

  def Run(self):
    self._PrintUserCalendars()

def main():
  """Runs the CalendarExample application with the provided username and
  and password values.  Authentication credentials are required.  
  NOTE: It is recommended that you run this sample using a test account."""

  # parse command line options
  try:
    opts, args = getopt.getopt(sys.argv[1:], "", ["user=", "pw=", "delete="])
  except getopt.error, msg:
    print ('python calendarExample.py --user [username] --pw [password] ' +
        '--delete [true|false] ')
    sys.exit(2)

  user = ''
  pw = ''
  delete = 'false'

  # Process options
  for o, a in opts:
    if o == "--user":
      user = a
    elif o == "--pw":
      pw = a
    elif o == "--delete":
      delete = a

  if user == '' or pw == '':
    print ('python calendarExample.py --user [username] --pw [password] ' +
        '--delete [true|false] ')
    sys.exit(2)

  
  sample = CalendarExample(user, pw)
  sample.Run()

if __name__ == '__main__':
  main()
