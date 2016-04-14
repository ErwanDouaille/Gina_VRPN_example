#include <iostream>
#include <signal.h>

#include "LgEnvironment.h"
#include "VRPNGenerator.h"
#include "VRPNObserver.h"

using namespace std;
using namespace lg;

bool finish = false;

void killHandler (int param)
{
    finish = true;
}

int main(int argc, char *argv[])
{
#ifdef SIGBREAK
    signal (SIGBREAK, killHandler);
#endif
    signal (SIGINT, killHandler);
    signal (SIGABRT, killHandler);
    signal (SIGTERM, killHandler);

    // Environment declaration
    Environment* environment = new Environment();
    environment->enableDataCopy(false);

    // HERE, declare your generators/processors/observers and add it to the environment
    VRPNGenerator *vrpn = new VRPNGenerator("VRPN_hydra_razer");
    if(environment->registerNode(vrpn))
        cerr << "Register VRPN hydraOK" << endl;
    else
        cout << environment->getLastError().c_str() << endl;

    VRPNObserver *vrpnServer = new VRPNObserver("VRPN_hydra_razer_Server");
    if(environment->registerNode(vrpnServer))
        cerr << "Register VRPN hydraOK" << endl;
    else
        cout << environment->getLastError().c_str() << endl;

    // Check if your generators/processors/observers are commpatible
    if(!environment->checkCompatibility()){
        cerr << "Nodes are not compatible." << endl;
        return 2;
    }

    // Check if you started the environment
    if(!environment->start()){
        cerr << "Environnement not started." << endl;
        return 2;
    }

    while(!finish)
        environment->update();

    environment->stop();

    delete environment;
    delete vrpn;
    delete vrpnServer;

    return 0;
}
