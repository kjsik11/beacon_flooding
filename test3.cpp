#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <tins/tins.h>
#include <unistd.h>
using namespace Tins;
using namespace std;

int main(int argc,char* argv[]){

	FILE *fp;
	if((fp = fopen(argv[2],"r"))==NULL){
		printf("Error");
		exit(1);
	}
	list<string> ssidList;
	char buff[100];
	while(!feof(fp)){
		fgets(buff,100,fp);
        *(buff+(strlen(buff)-1))=0;
		ssidList.push_back(buff);
	}	fclose(fp);
	list<string> ::iterator it = ssidList.begin();
	while (true) {
    		RadioTap tap;

            Dot11::address_type ap        = "00:11:22:33:44:55";
    		Dot11::address_type broadcast = "ff:ff:ff:ff:ff:ff";
    		Dot11Beacon beacon(broadcast, ap);
    		beacon.addr4(ap);
    		beacon.ssid(*it);
    		beacon.ds_parameter_set(10);
    		beacon.supported_rates({ 1.0f, 5.5f, 11.0f });
    		tap.inner_pdu(beacon);

    		PacketSender sender(argv[1]);
    		sender.send(tap);
    		usleep(10000);

    		if (++it == ssidList.end())
      			it = ssidList.begin();
  	
	}
}	
