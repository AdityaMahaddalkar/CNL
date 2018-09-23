#include <bits/stdc++.h>
#include <pcap.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
using namespace std;

int main(){
	
	char errbuf[PCAP_ERRBUF_SIZE];
	string file = "combined.pcap";
	
	// Open file and store result in pointer in pcap_t
	
	pcap_t * pcap = pcap_open_offline(file.c_str(), errbuf);
	
	// Create a header and a data object
	
	struct pcap_pkthdr * header;
	
	// Create a character array using a u_char
	
	const u_char * data;
	
	cout << endl;
	
	// Loop through packets and print on the screen
	
	u_int packetCount = 0;
	while(int returnValue = pcap_next_ex(pcap, &header, &data) >= 0){
		
		// Make sure it is an ip packet
		struct ether_header *eth_header;
   		eth_header = (struct ether_header *) data;
    	if (ntohs(eth_header->ether_type) != ETHERTYPE_IP) {
        	printf("Not an IP packet. Skipping...\n\n");
        	
    	}
    	else{
    		cout << "It is an IP packet" << endl;
    	}
    	
    	// Pointers to start point of various headers
    	const u_char *ip_header;
    	const u_char *tcp_header;
    	const u_char *payload;
		
		// Header length in bytes
		int ethernet_header_length = 14; 
    	int ip_header_length;
    	int tcp_header_length;
    	int payload_length;
    	
    	// Find start of ip header
    	ip_header = data + ethernet_header_length;
    	
    	// Second half of first byte contains IHL
    	ip_header_length = ((*ip_header)& 0x0F)*4;
  		
  		cout << "\nIP header length : " << ip_header_length;
  		
  		// Protocol starts at 10th byte of IP header
  		u_char protocol = *(ip_header + 9);
  		
  		cout << endl << endl;
  		
  		// considering the number of protocol define the packet
		// distinguish packets into different types
  		if (protocol == IPPROTO_TCP){
  			cout << "\nIt is a TCP packet";
  		}	  	
  		
  		else if (protocol == IPPROTO_UDP){
  			cout << "\nIt is a UDP packet";
  		}
    	
    	// Flush 
    	
    	cout << endl;
		// Print packet number
		cout << "Packet # " << ++packetCount << endl;
		
		// Print packet size
		cout << "Packet size: " << header->len << endl;
		
		if (header->len != header->caplen){
			cout << "Warning! Capture size different than packet size";
		} 
		
		// Print epoch time
		cout << "Epoch time : " << header->ts.tv_sec << " : " << header->ts.tv_usec << " seconds" << endl;
		
		// Loop through packet and print it as hexadecimal representation of octets
		for (u_int i=0; (i < header->caplen); i++){
			if( (i%16) == 0) cout << endl << endl;
			
			// print each octet as hex
			cout << data[i];
			
			
		}
		cout << endl << endl;
	}
	
	return 0;
}
