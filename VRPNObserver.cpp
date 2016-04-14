#include "VRPNObserver.h"

VRPNObserver::VRPNObserver(string name) : Observer(name)
{
    connection = vrpn_create_server_connection();
    tracker = new vrpn_Tracker_RazerHydra("Tracker1", connection);
    button = new vrpn_Button_Python("Button0", connection, 1);
}

VRPNObserver::~VRPNObserver(void)
{
}

Node* VRPNObserver::clone(string name) const
{
    return new VRPNObserver(name);
}

bool VRPNObserver::start()
{
    cout << "Start VRPNObserver" << endl;
    return true;
}

bool VRPNObserver::stop()
{
    cout << "Stop VRPNObserver" << endl;
    return true;
}

set<string> VRPNObserver::need() const
{
    set<string> needed;
    return needed;
}

bool VRPNObserver::observe(map<string,Group3D*> g3D,map<string,Group2D*> groups2D, map<string,Group1D*> groups1D, map<string,GroupSwitch*> groupsSwitch)
{
    button->mainloop();
    tracker->mainloop();
    connection->mainloop();
    return true;
}
