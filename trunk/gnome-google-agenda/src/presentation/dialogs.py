import pygtk
import gtk
import globalinformation as info

from eventHandlers.eventhandlers import AddQuickEvent_event

class ADialog:
    '''Abstract Dialog'''
    def __init__(self, parent):
        self.dlg = gtk.Dialog(title=None, parent=None, flags=0, buttons=None)
        self.dlg.add_button(gtk.STOCK_OK, gtk.RESPONSE_CLOSE)

    def run(self):
        resp = self.dlg.run()
        if resp == gtk.RESPONSE_CLOSE or resp == gtk.RESPONSE_CANCEL:
            self.dlg.destroy()

        
class Message_dlg(ADialog):
    '''Message Dialog to displau one message (msg)'''
    def __init__(self, parent, msg):
        self.dlg = gtk.MessageDialog(None, gtk.DIALOG_MODAL, gtk.MESSAGE_INFO, gtk.BUTTONS_NONE, msg)
        self.dlg.add_button(gtk.STOCK_OK, gtk.RESPONSE_CLOSE)

        
class About_dlg(ADialog):
    '''Just a normal About Dialog'''
    def __init__(self, parent):
        self.dlg = gtk.AboutDialog()
        
        self.dlg.set_program_name(info.__name__)
        self.dlg.set_name(info.__name__)
        self.dlg.set_version(info.__version__)
        self.dlg.set_license(info.__license__)
        self.dlg.set_authors(info.__authors__)
        self.dlg.set_logo(gtk.gdk.pixbuf_new_from_file('icons/icon.png'))
        
class AddEventWindow:
    '''abstract window to create a new event'''
    def __init__(self, parent):
        self.w = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.w.set_resizable(False)
        self.w.set_transient_for(parent)
        self.w.set_destroy_with_parent(True)
        
        
    def show(self):
        self.w.show()
        
    def destroy(self):
        self.w.hide()
        
class AddQuickEvent_window(AddEventWindow):
    '''window with a text entry'''

    def __init__(self, parent, event_tree_view_obj, liststore, domain):
        AddEventWindow.__init__(self, parent)
        self.w.set_title('New Quick Event')        
        vbox = gtk.VBox()
        label = gtk.Label()
        
        label.set_text('New Quick Event:')
        vbox.pack_start(label)
        textentry = gtk.Entry()
        textentry.set_max_length(500)
        button = gtk.Button("Go")

        vbox.add(textentry)
        vbox.add(button)
        
        self.w.add(vbox)

        button.show()
        label.show()
        vbox.show()
        textentry.show()
        self.show()

        # associate this window with an event handler
        AddQuickEvent_event(event_tree_view_obj, liststore, domain, textentry, button)
