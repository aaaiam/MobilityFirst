#ifndef __HOP_PROTOCOL_H__
#define __HOP_PROTOCOL_H__

//functions for handling HOP packets and tables

#include "mf_header.h"
#include "hop_repositories.h"
#include "ns3/object.h"
#include "ns3/packet.h"
#include "ns3/node.h"
#include "ns3/socket.h"
#include "ns3/event-garbage-collector.h"
#include "ns3/timer.h"
#include "ns3/output-stream-wrapper.h"
#include "ns3/traced-callback.h"
#include "ns3/ipv4.h"
#include "ns3/ipv4-routing-protocol.h"
#include "ns3/ipv4-static-routing.h"
#include "ns3/ipv4-interface.h"
#include "ns3/ipv4-l3-protocol.h"
#include <set>
#include <vector>



namespace ns3 {

using namespace mf;

class HOPProtocol
{

	public:
		HOPProtocol ();
		~HOPProtocol () {}
		Ptr<Packet> FromFile (Ipv4Address m_mainAddress, Ipv4Address sender, Ipv4Address receiver); //reads in from a file and creates data packets
		void RcvdDataPkt (mf::MessageHeader data_pkt, Ipv4Address m_mainAddress);// receives data packets
		void ToFile (int pkt_count, Ipv4Address sender); // writes data in the file
		CSYNCTuple SendCSYNCACK (mf::MessageHeader csync_pkt, Ipv4Address m_mainAddress);// creates CSYNC ACK packet
		// processes CSYNC ACK packets and returns a vector data packets and the corresponding CSYNC for it
		std::vector< Ptr<Packet> > ProcessCSYNCACK (mf::MessageHeader csync_ack_pkt, Ipv4Address m_mainAddress);
		
		
	private:
		FILE *fp_1;
		FILE *fp_2;
		FILE *fp_3;
		uint32_t chkID;

		Ptr<Packet> SendCSYNC (int size, uint32_t seq_no, Ipv4Address m_mainAddress, Ipv4Address sender, Ipv4Address receiver);// creates CSYNC packet
		BitmapTuple* GetBitmap (uint32_t &id, Ipv4Address source);// returns a Bitmap given the chunck ID
		std::vector< Ptr<Packet> > GetDataPkts (uint32_t chunck_id, Ipv4Address source);// returns a Data Packets given the chunck ID
		int GetPktCount (uint32_t chunck_id, Ipv4Address source);// gives number of packet received
		void EraseBitmapTuple (uint32_t &id, Ipv4Address source);// erase Bitmap tuple given the chunck ID
		mf::MessageHeader pkt_array[CHK_PKT_COUNT];
		//Ipv4Address destination_addr;
		//Ipv4Address source_addr;
		Ptr<Packet> csync_packet;
		std::vector<Ipv4Address> resume;
		uint32_t total_chunck;		
		
	protected:
		DataSet m_dataSet; //Data Table
		BitmapSet m_bitmapSet; //Bitmap Table
		PktCountSet m_PktCountSet; //Packet Count Table
};

} 

#endif

