#!/usr/bin/env python

import pygtk
import gtk
import gobject

from eventmanagement import EventTreeView

from serviceLayer.loginService import LoginService
from serviceLayer.addquickeventService import AddQuickEventService
from serviceLayer.getEventsService import GetEventsService
from serviceLayer.initdomain import InitDomain

import dialogs

ui = '''
<ui>
  <menubar>
    <menu action="File">
      <menuitem action="Connect"/>
      <menuitem action="Add Quick Event"/>
      <separator/>
      <menuitem action="Quit"/>
    </menu>
    <menu action="Help">
      <menuitem action="About"/>
    </menu>
  </menubar>
</ui>
'''

class MainWindow:
    
    def do_stuff(self, widget=None, event=None, data=None):
        self.set_statusbar("doing stuff")

    def show_about_dlg(self, widget=None, event=None, data=None):
        about_dlg = dialogs.About_dlg(self.w)
        about_dlg.run()

    def connect(self, widget=None, event=None, data=None):
        #login
        self.log.write('-- trying to connect')

        service = LoginService(self.initdomain)
        
        service.execute()
        r = service.get_result()

        if not r:
            self.log.write('-- cannot login - Username and password do not match. ')
        else:
            self.log.write('-- just logged in')    
        
            self.set_statusbar('Loading Timeline')

        #list events
        service = GetEventsService(self.initdomain)

        service.execute()
        r = service.get_result()

        tree_view_list =  self.e.order_events_by_date(r)
        self.e.load(tree_view_list)

        #self.e.load()
        self.clear_statusbar()

    def addQuickEvent(self, widget=None, event=None, data=None):
        dialogs.AddQuickEvent_window(self.w, self.initdomain)

    def delete_event(self, widget=None, event=None, data=None):
        gtk.main_quit()
        self.log.write('== end session')
        self.log.close()
        return False

    def set_title(self):
        self.w.set_title("google agenda")
        # TODO: fetch the username to compose the message
        # "agenda for viva.o.mauricio"        
        
    def set_statusbar(self, content=None):
        if content is not None:
            self.statusbar.push(0, content)

    def clear_statusbar(self):
        self.set_statusbar(" ") # TODO: this must be changed to statusbar.pop()

    def about_dialog(self, data = None):
        #about = dialog.AboutDialog(self.w)
        #about.response_is_cancel()
        pass

    def __init__(self):
    
        self.initdomain = InitDomain()
        self.e = EventTreeView()
        self.log = self.initdomain.get_log()
        self.log.new_line()
        self.log.write('== start session')
        # defining a new window
        self.w = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.w.set_size_request(200, 400)
        self.set_title()
        self.w.set_resizable(True)
        self.w.connect("delete_event", self.delete_event)
        
        vbox = gtk.VBox()

        self.treeview = self.e.get_widget()

        # create a UIManager instance
        uimanager = gtk.UIManager()

        # add the accelerator group to the toplevel window
        accelgroup = uimanager.get_accel_group()
        self.w.add_accel_group(accelgroup)

        # create an ActionGroup
        actiongroup = gtk.ActionGroup('menubar')
        self.actiongroup = actiongroup

        # create actions
        actiongroup.add_actions([('Connect', None, 'Connect', None, 'Fetch event', self.connect),
                                 ('Add Quick Event', None, 'Add Quick Event', None, 'Add Quick Event', self.addQuickEvent),
                                 ('Quit', gtk.STOCK_QUIT, 'Quit', None, 'Quit', self.delete_event),
                                 ('About', gtk.STOCK_ABOUT, 'About', None, 'About', self.show_about_dlg),
                                 ('File', None, '_File'),
                                 ('Help', None, '_Help')
                                 ])

        # actiongroup.add_toggle_actions([()])

        # add actiongroup to uimanager
        uimanager.insert_action_group(actiongroup, 0)

        # add a ui description
        uimanager.add_ui_from_string(ui)

        menubar = uimanager.get_widget('/menubar')
        statusbar = gtk.Statusbar()

        # add widgets         
        vbox.pack_start(menubar, False, True, 0)
        vbox.add(self.treeview)
        vbox.pack_end(statusbar, False, True, 0)
        self.w.add(vbox)

        
        self.statusbar = statusbar

        # draw widgets
        menubar.show()
        self.statusbar.show()
        self.treeview.show()
        vbox.show()
        self.w.show()

# calling the gtk event cicle
def main():
    gtk.main()
    return 0
