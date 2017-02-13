#include <iostream>
#include <unistd.h>
#include <fstream>
using namespace std;

struct setup{
  string interface = "eth0";
}; setup s;

class network_speeds{
  public:
    int network_speed(void){
        ifstream net_work_monitor(string("/sys/class/net/"  + s.interface + "/"));
        if(net_work_monitor.good() == 1){
             ifstream network_speed_check;
             network_speed_check.open("/sys/class/net/" + s.interface + "/statistics/rx_bytes");
             string output;
             if (network_speed_check.is_open()) {
                while (!network_speed_check.eof()) {
                  network_speed_check >> output;
              }
            }
            net_work_monitor.close();
            network_speed_check.close();
            return stoi(output)/1024;
        }
        return 0;
    }
};

int main() {
    network_speeds ns;
    while(1){
       cout << string(500, '\n') << endl; // lol endl
       cout << "Using: " << s.interface <<  " Interface" << endl;
       cout <<  ns.network_speed() << "MBPS checking again in 5 seconds" << endl;
       sleep(5);
    }
  return 0;
}
