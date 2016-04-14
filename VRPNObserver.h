#ifndef VRPNOBSERVER_H
#define VRPNOBSERVER_H

#include "LgObserver.h"
#include "vrpn_Connection.h"
#include "vrpn_Button.h"
#include "vrpn_Tracker_RazerHydra.h"

using namespace lg;

class VRPNObserver : public Observer
{
private:
    vrpn_Connection *connection;
    vrpn_Tracker *tracker;
    vrpn_Button *button;

public:
    VRPNObserver(string);
    ~VRPNObserver(void);

    Node* clone(string name) const;
    bool start();
    bool stop();
    set<string> need() const;
    bool observe(map<string,Group3D*> groups3D,map<string,Group2D*> groups2D, map<string,Group1D*> groups1D, map<string,GroupSwitch*> groupsSwitch);
};

#endif // VRPNOBSERVER_H
