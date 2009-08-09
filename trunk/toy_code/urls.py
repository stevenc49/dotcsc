from django.conf.urls.defaults import *

# Uncomment the next two lines to enable the admin:
# from django.contrib import admin
# admin.autodiscover()

urlpatterns = patterns('',
    # Example:
    # (r'^wikicamp/', include('wikicamp.foo.urls')),

    # Uncomment the admin/doc line below and add 'django.contrib.admindocs' 
    # to INSTALLED_APPS to enable admin documentation:
    # (r'^admin/doc/', include('django.contrib.admindocs.urls')),

    # Uncomment the next line to enable the admin:
    # (r'^admin/(.*)', admin.site.root),
    (r'^wikicamp/(?P<page_name>[^/]*)/edit/$', 'wikicamp.wiki.views.edit_page'),
    (r'^wikicamp/(?P<page_name>[^/]*)/save/$', 'wikicamp.wiki.views.save_page'),
    (r'^wikicamp/(?P<page_name>[^/]*)/$', 'wikicamp.wiki.views.view_page')
)
