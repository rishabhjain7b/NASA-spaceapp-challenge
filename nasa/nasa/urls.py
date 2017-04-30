from django.conf.urls import include, url
from django.contrib import admin

admin.autodiscover()

# url(r'^confirm/$', CartConfirmView, name='cart_confirm'),
#     url(r'^customize/(?P<val>[\w-]+)/$', customizeview, name='customize'),


from dashboard.views import dashboard,DashboardShow

urlpatterns = [
    # Examples:
    # url(r'^$', 'nasa.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),

    url(r'^admin/', include(admin.site.urls)),
    url(r'^$', dashboard, name='dashboard'),
    url(r'^show/$', DashboardShow, name='dashboard-show'),


]
