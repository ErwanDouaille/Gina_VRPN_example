#include "VRPNGenerator.h"

OrientedPoint3D* headOrientedPoint = new OrientedPoint3D(Point3D(.0,.0,.0), Point3D(.0,.0,.0), .0, .0);
OrientedPoint3D* rightHandOrientedPoint = new OrientedPoint3D(Point3D(.0,.0,.0), Point3D(.0,.0,.0), .0, .0);
OrientedPoint3D* leftHandOrientedPoint = new OrientedPoint3D(Point3D(.0,.0,.0), Point3D(.0,.0,.0), .0, .0);

void VRPN_CALLBACK handle_analog( void* userData, const vrpn_ANALOGCB a )
{
  int nbChannels = a.num_channel;
  cout << "Analog : ";
  for( int i=0; i < a.num_channel; i++ )
    cout << a.channel[i] << " ";
  cout << endl;
}

void VRPN_CALLBACK handle_button( void* userData, const vrpn_BUTTONCB b )
{
  cout << "Button '" << b.button << "': " << b.state << endl;
}

void VRPN_CALLBACK handle_tracker(void* userData, const vrpn_TRACKERCB t )
{
  if (t.sensor == 0)
    rightHandOrientedPoint = new OrientedPoint3D(Point3D((float)t.pos[0], (float)t.pos[1], (float)t.pos[2]), Orientation3D(0.0, 0.0, 0.0), 1.0, 0.0);
  if (t.sensor == 1)
    leftHandOrientedPoint = new OrientedPoint3D(Point3D((float)t.pos[0], (float)t.pos[1], (float)t.pos[2]), Orientation3D(0.0, 0.0, 0.0), 1.0, 0.0);
  cout << "Tracker '" << t.sensor << "' : " << t.pos[0] << "," <<  t.pos[1] << "," << t.pos[2] << endl;
}

VRPNGenerator::VRPNGenerator(string name) : Generator(name)
{
  this->vrpnAnalog = new vrpn_Analog_Remote("Tracker1@localhost");
  this->vrpnButton = new vrpn_Button_Remote("Tracker1@localhost");
  this->vrpnTracker = new vrpn_Tracker_Remote("Tracker1@localhost");

  this->vrpnAnalog->register_change_handler(0, handle_analog);
  this->vrpnButton->register_change_handler(0, handle_button);
  this->vrpnTracker->register_change_handler(0, handle_tracker);
}

VRPNGenerator::~VRPNGenerator(void)
{
}

Node* VRPNGenerator::clone(string cloneName) const
{
  // A VRPNGenerator cannot be cloned, it is better to return the current instance
  // Another VRPNGenerator can be created for openning another device or another file
  return (Node*)this;
}

bool VRPNGenerator::start()
{
  if(!_environment){
    cout << "HydraRazerVRPNGenerator Error : Parent environment has not be set." << endl;
    return false;
  }
  return true;
}

bool VRPNGenerator::stop()
{
  cout << "Stop HydraRazerVRPNGenerator" << endl;
  return true;
}

set<string> VRPNGenerator::produce() const
{
  set<string> produce;
  produce.insert(LG_ORIENTEDPOINT3D_LEFT_HAND);
  produce.insert(LG_ORIENTEDPOINT3D_RIGHT_HAND);

  produce.insert("LEFT_HAND");
  produce.insert("RIGHT_HAND");
  return produce;
}

bool VRPNGenerator::generate(map<string,Group3D*>& groups3D,map<string,Group2D*>& g2D,map<string,Group1D*>&,map<string,GroupSwitch*>&)
{
  //call all the mainloop
  this->vrpnAnalog->mainloop();
  this->vrpnButton->mainloop();
  this->vrpnTracker->mainloop();

  //update data from new ones
  updateData(_environment, groups3D, "user0", "HYDRARAZER_DATA", "left_hand", LG_ORIENTEDPOINT3D_LEFT_HAND,_timestamp, *leftHandOrientedPoint);
  updateData(_environment, groups3D, "user0", "HYDRARAZER_DATA", "right_hand", LG_ORIENTEDPOINT3D_RIGHT_HAND,_timestamp, *rightHandOrientedPoint);
  return true;
}
